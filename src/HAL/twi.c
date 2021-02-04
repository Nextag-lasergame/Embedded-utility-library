/*
 * Copyright (c) 2020 Tim Herreijgers
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated
 * documentation files (the "Software"), to deal in the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial
 * portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO
 * THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include "EUL/HAL/twi.h"
#include "twi_internal.h"
#include <avr/io.h>
#include <avr/interrupt.h>

#ifndef F_CPU
#warning F_CPU is not defined, defining F_CPU as 1000000L
#define F_CPU 1000000L
#endif

#define TWI_BUFFER_SIZE 8

#define READ 0x01
#define WRITE 0x00

static void (*onReceiveCallback)(uint8_t*, uint8_t) = 0x00;
static void (*onRequestCallback)(void) = 0x00;
static volatile uint8_t twiState;

static volatile uint8_t rxBuffer[TWI_BUFFER_SIZE];
static volatile uint8_t rxBufferIndex;

static volatile uint8_t txBuffer[TWI_BUFFER_SIZE];
static volatile uint8_t txBufferIndex;
static uint8_t txBufferLastIndex;
static uint8_t txSlaveAddress;
static uint8_t requestAmount;

static void twi_sendStartBit();
static void twi_sendSlaveAddress(uint8_t address, uint8_t rw);
static void twi_writeByte(uint8_t byte);
static void twi_reply(uint8_t ack);
static void twi_releaseBus(void);
static void twi_sendStopBit();

void twi_begin()
{
    //Set the presacaler to 1
    TWI_STATUS_REGISTER &= ~(_BV(TWPS0) | _BV(TWPS1));
    //Set the value of the TWI Bit rate register
    TWI_BIT_RATE_REGISTER = (((F_CPU / TWI_FREQ) - 16) / 2);

    // Enable the TWI and enables Acknowledge bit
    TWI_CONTROL_REGISTER = _BV(TWEA) | _BV(TWEN) | _BV(TWIE);

    //Set up external interrupts
    sei();
    twiState = TWI_READY;
}

void twi_setAddress(uint8_t address)
{
    // Sets the slave address
    TWI_ADDRESS_REGISTER = (address << 1);
}

extern void twi_sendTo(uint8_t address, uint8_t* data, uint8_t amount)
{
    while(twiState == TWI_MTX);

    if(amount > TWI_BUFFER_SIZE)
        return;

    txBufferLastIndex = amount - 1;
    txBufferIndex = 0;

    for(uint8_t i = 0; i < amount; i++)
    {
        txBuffer[i] = data[i];
    }

    twiState = TWI_MTX;
    txSlaveAddress = address;
    twi_sendStartBit();
}

void twi_requestFrom(uint8_t address, uint8_t amount)
{
    while(twiState == TWI_MRX);

    twiState = TWI_MRX;
    txSlaveAddress = address;
    requestAmount = amount;
    twi_sendStartBit();
}

void twi_onReceive(void (*callback)(uint8_t*, uint8_t))
{
    onReceiveCallback = callback;
}

void twi_onRequest(void (*callback)(void))
{
    onRequestCallback = callback;
}

void twi_requestReply(uint8_t *data, uint8_t amount)
{
    if(amount > TWI_BUFFER_SIZE)
        return;

    txBufferLastIndex = amount - 1;
    txBufferIndex = 0;

    for(uint8_t i = 0; i < amount; i++)
    {
        txBuffer[i] = data[i];
    }
}

static void twi_sendStartBit()
{
    TWI_CONTROL_REGISTER = _BV(TWSTA) | _BV(TWINT) | _BV(TWEN) | _BV(TWIE);
}

static void twi_sendSlaveAddress(uint8_t address, uint8_t rw)
{
    TWI_DATA_REGISTER = (address << 1) | (rw ? 0x01 : 0x00);
    TWI_CONTROL_REGISTER = _BV(TWEA) | _BV(TWINT) | _BV(TWEN) | _BV(TWIE);
}

static void twi_reply(uint8_t ack)
{
    if(ack)
    {
        TWI_CONTROL_REGISTER = _BV(TWINT) | _BV(TWEA) | _BV(TWEN) | _BV(TWIE);
    }
    else
    {
        TWI_CONTROL_REGISTER = _BV(TWINT) | _BV(TWEA) | _BV(TWIE);
    }
}

static void twi_releaseBus(void)
{
    TWCR = _BV(TWEN) | _BV(TWIE) | _BV(TWEA) | _BV(TWINT);
    twiState = TWI_READY;
}

static void twi_writeByte(uint8_t byte)
{
    TWI_DATA_REGISTER = byte;
    TWI_CONTROL_REGISTER = _BV(TWINT) | _BV(TWEA) | _BV(TWEN) | _BV(TWIE);
}

static void twi_sendStopBit()
{
    TWI_CONTROL_REGISTER = _BV(TWINT) | _BV(TWEN) | _BV(TWSTO);
}

ISR(TWI_vect)
        {
                switch(TWI_STATUS_REGISTER & TWI_STATUS_REGISTER_STATUS_MASK)
                {
                    case TW_START:
                    case TW_REP_START:
                        if(twiState == TWI_MTX)
                            twi_sendSlaveAddress(txSlaveAddress, WRITE);
                    if(twiState == TWI_MRX)
                        twi_sendSlaveAddress(txSlaveAddress, READ);
                    break;
                    case TW_MT_SLA_ACK:
                    case TW_MT_DATA_ACK:
                        if(txBufferIndex <= txBufferLastIndex)
                        {
                            twi_writeByte(txBuffer[txBufferIndex++]);
                        }
                        else
                        {
                            twi_sendStopBit();
                            twiState = TWI_READY;
                        }
                    break;
                    case TW_MT_SLA_NACK:
                    case TW_MT_DATA_NACK:
                        twi_sendStopBit();
                    twiState = TWI_READY;
                    break;


                    case TW_MR_SLA_ACK:
                        rxBufferIndex = 0;
                    twi_reply(1);
                    break;
                    case TW_MR_DATA_ACK:
                        if(rxBufferIndex + 1 >= TWI_BUFFER_SIZE)
                        {
                            twi_sendStopBit();
                            twiState = TWI_READY;
                            break;
                        }

                    rxBuffer[rxBufferIndex++] = TWI_DATA_REGISTER;

                    if(rxBufferIndex >= requestAmount)
                    {
                        if(onReceiveCallback != 0x00)
                        {
                            onReceiveCallback(rxBuffer, rxBufferIndex);
                        }
                        twi_sendStopBit();
                        twiState = TWI_READY;
                        break;
                    }
                    twi_reply(1);
                    break;
                    case TW_MR_DATA_NACK:
                    case TW_MR_SLA_NACK:
                        twi_sendStopBit();
                    twiState = TWI_READY;
                    break;

                    case TW_SR_SLA_ACK:
                    case TW_SR_GCALL_ACK:
                    case TW_SR_ARB_LOST_SLA_ACK:
                    case TW_SR_ARB_LOST_GCALL_ACK:
                        twiState = TWI_SRX;
                    rxBufferIndex = 0;
                    twi_reply(1);
                    break;
                    case TW_SR_DATA_ACK:
                    case TW_SR_GCALL_DATA_ACK:
                        if(rxBufferIndex + 1 >= TWI_BUFFER_SIZE)
                        {
                            twi_reply(0);
                            break;
                        }

                    rxBuffer[rxBufferIndex++] = TWI_DATA_REGISTER;
                    twi_reply(1);
                    break;
                    case TW_MT_ARB_LOST:
                    case TW_SR_STOP:
                        twi_releaseBus();
                    if(onReceiveCallback != 0x00)
                    {
                        onReceiveCallback(rxBuffer, rxBufferIndex);
                    }
                    break;
                    case TW_SR_DATA_NACK:
                    case TW_SR_GCALL_DATA_NACK:
                        twi_reply(0);
                    break;


                    case TW_ST_SLA_ACK:
                        txBufferIndex = 0;
                    txBufferLastIndex = 0;
                    if(onRequestCallback != 0x00)
                    {
                        onRequestCallback();
                    }
                    case TW_ST_DATA_ACK:
                        if(txBufferIndex <= txBufferLastIndex)
                        {
                            twi_writeByte(txBuffer[txBufferIndex++]);
                        }

                    break;
                    case TW_ST_LAST_DATA:
                    case TW_ST_DATA_NACK:
                        twi_releaseBus();
                    break;
                }
        }
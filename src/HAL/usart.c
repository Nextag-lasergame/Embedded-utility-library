//
// Created by Tim on 16/06/2020.
//

#include "EUL/HAL/usart.h"
#include "usart_internal.h"
#include <avr/interrupt.h>
#include <string.h>
#include <math.h>

#ifndef F_CPU
#warning F_CPU is not defined, defining F_CPU as 1000000L
#define F_CPU 1000000L
#endif

static uint8_t txBuffer[USART_BUFFER_SIZE];
static uint8_t txBufferHead = 0;
static uint8_t txBufferTail = 0;

static uint8_t rxBuffer[USART_BUFFER_SIZE];
static uint8_t rxBufferHead = 0;
static uint8_t rxBufferTail = 0;

static bool usart_addToTxBuffer(const char *msg);
static void usart_addToRxBuffer(uint8_t c);
static void usart_startTransmission();
static void usart_flush();

static usartFrameFormat_t usartFrameFormat = {
    USART_DATA_BITS_8, USART_PARITY_BIT_NONE, USART_STOP_BITS_1
};

void usart_setFrameFormat(usartFrameFormat_t frameFormat)
{
    if(frameFormat.databits >= 0 && frameFormat.databits < 4 && frameFormat.parityBit >= 0 && frameFormat.parityBit < 4
        && frameFormat.stopBits >= 0 && frameFormat.stopBits < 2)
    {
        usartFrameFormat = frameFormat;
    }
}

void usart_begin(uint32_t baud)
{
    cli();
    uint32_t calculatedBaudRate = (uint32_t) round(F_CPU/16.0/baud-1);
//    uint32_t  calculatedBaudRate = 8;

    // Set baud rate
    USART_BAUD_RATE_REGISTER_H = (uint8_t) (calculatedBaudRate>>8);
    USART_BAUD_RATE_REGISTER_L = (uint8_t) calculatedBaudRate;

    // Enable receiver and transmitter with interrupts
    USART_CONTROL_STATUS_REGISTER_B = _BV(USART_RX_ENABLE) | _BV(USART_TX_ENABLE)
            | _BV(USART_TX_INTERRUPT_ENABLE) | _BV(USART_RX_INTERRUPT_ENABLE);

    //Sets up the frameformat
   USART_CONTROL_STATUS_REGISTER_C = (usartFrameFormat.databits << USART_DATA_BITS_OFFSET) |
           (usartFrameFormat.stopBits << USART_STOP_BITS_OFFSET) |
           (usartFrameFormat.parityBit << USART_PARITY_BITS_OFFSET);
    sei();
}

void usart_end()
{
    USART_CONTROL_STATUS_REGISTER_B = 0;
    usart_flush();
}

int usart_available()
{
    return rxBufferHead - rxBufferTail;
}

bool usart_print(const char *msg)
{
    if(!usart_addToTxBuffer(msg))
        return false;

    usart_startTransmission();
    return true;
}

bool usart_println(const char *msg)
{
    if(strlen(msg) + 1 > USART_BUFFER_SIZE - (txBufferHead - txBufferTail))
        return false;

    if(!usart_addToTxBuffer(msg))
        return false;

    if(!usart_addToTxBuffer("\n"))
        return false;

    usart_startTransmission();
    return true;
}

void usart_write(uint8_t byte)
{
    // Wait for the transmit buffer to be empty
    while(!(USART_CONTROL_STATUS_REGISTER_A & _BV(USART_DATA_REGISTER_EMPTY)));

    //Put the data in de buffer and send it
    USART_DATA_REGISTER = byte;
}

uint8_t usart_read()
{
    if(!usart_available())
        return 0x00;

    return rxBuffer[rxBufferTail++ % USART_BUFFER_SIZE];
}

static bool usart_addToTxBuffer(const char *msg)
{
    size_t length = strlen(msg);

    if(txBufferHead + length > USART_BUFFER_INDEX_MAX_VALUE)
    {
        txBufferTail = txBufferTail % USART_BUFFER_SIZE;
        txBufferHead = (txBufferHead % USART_BUFFER_SIZE < txBufferTail ? USART_BUFFER_SIZE : 0) + txBufferHead % USART_BUFFER_SIZE;
    }

    if(length > 32 || (txBufferHead + length) - txBufferTail > USART_BUFFER_SIZE)
        return false;

    for(size_t i = 0; i < length; i++)
    {
        txBuffer[txBufferHead++ % USART_BUFFER_SIZE] = msg[i];
    }
    return true;
}

static void usart_addToRxBuffer(uint8_t c)
{
    if(rxBufferHead + 1 > USART_BUFFER_INDEX_MAX_VALUE)
    {
        rxBufferTail = rxBufferTail % USART_BUFFER_SIZE;
        rxBufferHead = (rxBufferHead % USART_BUFFER_SIZE < rxBufferTail ? USART_BUFFER_SIZE : 0) + rxBufferHead % USART_BUFFER_SIZE;
    }

    if((rxBufferHead + 1) - rxBufferTail > USART_BUFFER_SIZE)
        return;

    rxBuffer[rxBufferHead++ % USART_BUFFER_SIZE] = c;
}

static void usart_startTransmission()
{
    usart_write(txBuffer[txBufferTail++ % USART_BUFFER_SIZE]);
}

static void usart_flush()
{
    uint8_t dummy;
    while(USART_CONTROL_STATUS_REGISTER_A & _BV(USART_RECEIVE_COMPLETE))
    {
        dummy = USART_DATA_REGISTER;
    }
}

ISR(USART_TX_vect)
{
    if(txBufferTail + 1 <= txBufferHead)
    {
        usart_write(txBuffer[txBufferTail++  % USART_BUFFER_SIZE]);
    }
}

ISR(USART_RX_vect)
{
    uint8_t data = USART_DATA_REGISTER;
    usart_addToRxBuffer(data);
}
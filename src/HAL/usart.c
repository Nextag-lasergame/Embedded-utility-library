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

#include "EUL/HAL/usart.h"
#include <avr/interrupt.h>
#include <string.h>
#include <math.h>
#include "EUL/HAL/digital_io.h"

#if defined(USART_COUNT) && USART_COUNT > 0

#if USART_COUNT > 1
#define USART_TRANSMIT_VECTOR USART0_TX_vect
#define USART_RECEIVE_VECTOR USART0_RX_vect
#else
#define USART_TRANSMIT_VECTOR USART_TX_vect
#define USART_RECEIVE_VECTOR USART_RX_vect
#endif

#ifndef F_CPU
#warning F_CPU is not defined, defining F_CPU as 1000000L
#define F_CPU 1000000L
#endif

#define USART_BUFFER_INDEX_MAX_VALUE 255

static bool usart_addToTxBuffer(struct Usart *usart, const char *msg);
static void usart_addToRxBuffer(struct Usart *usart, uint8_t c);
static void usart_startTransmission(struct Usart *usart);
static void usart_flush(struct Usart *usart);

void usart_setFrameFormat(struct Usart *usart, UsartFrameFormat_t frameFormat)
{
    if(frameFormat.databits >= 0 && frameFormat.databits < 4 && frameFormat.parityBit >= 0 && frameFormat.parityBit < 4
        && frameFormat.stopBits >= 0 && frameFormat.stopBits < 2)
    {
        usart->frameFormat = frameFormat;
    }
}

void usart_begin(struct Usart *usart, uint32_t baud)
{
    usart->rxBufferHead = 0;
    usart->rxBufferTail = 0;
    usart->txBufferHead = 0;
    usart->txBufferTail = 0;

    cli();
    uint32_t calculatedBaudRate = (uint32_t) round(F_CPU/16.0/baud-1);

    // Set baud rate
    *usart->registerBaudRateHigh = (uint8_t) (calculatedBaudRate>>8);
    *usart->registerBaudRateLow = (uint8_t) calculatedBaudRate;

    // Enable receiver and transmitter with interrupts
    *usart->registerControlB = _BV(RXEN0) | _BV(TXEN0) | _BV(TXCIE0) | _BV(RXCIE0);

    //Sets up the frameformat
    *usart->registerControlC = (usart->frameFormat.databits << 1) |
           (usart->frameFormat.stopBits << 2) |
           (usart->frameFormat.parityBit << 4);
    sei();
}

void usart_end(struct Usart *usart)
{
    *(usart->registerControlB) = 0;
    usart_flush(usart);
}

int usart_available(struct Usart *usart)
{
    return usart->rxBufferHead - usart->rxBufferTail;
}

bool usart_print(struct Usart *usart, const char *msg)
{
    if(!usart_addToTxBuffer(usart, msg))
        return false;

    usart_startTransmission(usart);
    return true;
}

bool usart_println(struct Usart *usart, const char *msg)
{
    if(strlen(msg) + 1 > USART_BUFFER_SIZE - (usart->txBufferHead - usart->txBufferTail))
        return false;

    if(!usart_addToTxBuffer(usart, msg))
        return false;

    if(!usart_addToTxBuffer(usart, "\n"))
        return false;

    usart_startTransmission(usart);
    return true;
}

void usart_write(struct Usart *usart, uint8_t byte)
{
    // Wait for the transmit buffer to be empty
    while(!(*usart->registerControlA & _BV(UDRE0)));

    //Put the data in de buffer and send it
    *usart->registerData = byte;
}

uint8_t usart_read(struct Usart *usart)
{
    if(!usart_available(usart))
        return 0x00;

    return usart->rxBuffer[usart->rxBufferTail++ % USART_BUFFER_SIZE];
}

static bool usart_addToTxBuffer(struct Usart *usart, const char *msg)
{
    size_t length = strlen(msg);

    if(usart->txBufferHead + length > USART_BUFFER_INDEX_MAX_VALUE)
    {
        usart->txBufferTail = usart->txBufferTail % USART_BUFFER_SIZE;
        usart->txBufferHead = (usart->txBufferHead % USART_BUFFER_SIZE < usart->txBufferTail ? USART_BUFFER_SIZE : 0) + usart->txBufferHead % USART_BUFFER_SIZE;
    }

    if(length > 32 || (usart->txBufferHead + length) - usart->txBufferTail > USART_BUFFER_SIZE)
        return false;

    for(size_t i = 0; i < length; i++)
    {
        usart->txBuffer[usart->txBufferHead++ % USART_BUFFER_SIZE] = msg[i];
    }
    return true;
}

static void usart_addToRxBuffer(struct Usart *usart, uint8_t c)
{
    if(usart->rxBufferHead + 1 > USART_BUFFER_INDEX_MAX_VALUE)
    {
        usart->rxBufferTail = usart->rxBufferTail % USART_BUFFER_SIZE;
        usart->rxBufferHead = (usart->rxBufferHead % USART_BUFFER_SIZE < usart->rxBufferTail ? USART_BUFFER_SIZE : 0) + usart->rxBufferHead % USART_BUFFER_SIZE;
    }

    if((usart->rxBufferHead + 1) - usart->rxBufferTail > USART_BUFFER_SIZE)
        return;

    usart->rxBuffer[usart->rxBufferHead++ % USART_BUFFER_SIZE] = c;
}

static void usart_startTransmission(struct Usart *usart)
{
    usart_write(usart, usart->txBuffer[usart->txBufferTail++ % USART_BUFFER_SIZE]);
}

static void usart_flush(struct Usart *usart)
{
    uint8_t dummy;
    while(*(usart->registerControlA) & _BV(RXC0))
    {
        dummy = *(usart->registerData);
    }
}

static struct Usart usart0NoPointer = {
        &UBRR0L,
        &UBRR0H,
        &UCSR0A,
        &UCSR0B,
        &UCSR0C,
        &UDR0,
        {
                USART_DATA_BITS_8, USART_PARITY_BIT_NONE, USART_STOP_BITS_1
        },
        0,
        0,
        0,
        0
};

struct Usart *usart0 = &usart0NoPointer;

ISR(USART_TRANSMIT_VECTOR)
{
    if(usart0->txBufferTail + 1 <= usart0->txBufferHead)
    {
        usart_write(usart0, usart0->txBuffer[usart0->txBufferTail++  % USART_BUFFER_SIZE]);
    }
}

ISR(USART_RECEIVE_VECTOR)
{
    uint8_t data = *usart0->registerData;
    usart_addToRxBuffer(usart0, data);
}

#if USART_COUNT > 1

static struct Usart usart1NoPointer = {
        &UBRR1L,
        &UBRR1H,
        &UCSR1A,
        &UCSR1B,
        &UCSR1C,
        &UDR1,
        {
                USART_DATA_BITS_8, USART_PARITY_BIT_NONE, USART_STOP_BITS_1
        },
        0,
        0,
        0,
        0
};

struct Usart *usart1 = &usart1NoPointer;

ISR(USART1_TX_vect)
{
    if(usart1->txBufferTail + 1 <= usart1->txBufferHead)
    {
        usart_write(usart1, usart1->txBuffer[usart1->txBufferTail++  % USART_BUFFER_SIZE]);
    }
}

ISR(USART1_RX_vect)
{
    uint8_t data = *usart1->registerData;
    usart_addToRxBuffer(usart1, data);
}

#if USART_COUNT > 2

static struct Usart usart2NoPointer = {
        &UBRR2L,
        &UBRR2H,
        &UCSR2A,
        &UCSR2B,
        &UCSR2C,
        &UDR2,
        {
                USART_DATA_BITS_8, USART_PARITY_BIT_NONE, USART_STOP_BITS_1
        },
        0,
        0,
        0,
        0
};

struct Usart *usart2 = &usart2NoPointer;

ISR(USART2_TX_vect)
{
    if(usart2->txBufferTail + 1 <= usart2->txBufferHead)
    {
        usart_write(usart2, usart2->txBuffer[usart2->txBufferTail++  % USART_BUFFER_SIZE]);
    }
}

ISR(USART2_RX_vect)
{
    uint8_t data = *usart2->registerData;
    usart_addToRxBuffer(usart2, data);
}

#if USART_COUNT > 3

static struct Usart usart3NoPointer = {
        &UBRR3L,
        &UBRR3H,
        &UCSR3A,
        &UCSR3B,
        &UCSR3C,
        &UDR3,
        {
                USART_DATA_BITS_8, USART_PARITY_BIT_NONE, USART_STOP_BITS_1
        },
        0,
        0,
        0,
        0
};

struct Usart *usart3 = &usart3NoPointer;

ISR(USART3_TX_vect)
{
    if(usart3->txBufferTail + 1 <= usart3->txBufferHead)
    {
        usart_write(usart3, usart3->txBuffer[usart3->txBufferTail++  % USART_BUFFER_SIZE]);
    }
}

ISR(USART3_RX_vect)
{
    uint8_t data = *usart3->registerData;
    usart_addToRxBuffer(usart3, data);
}

#endif // USART_COUNT > 3
#endif // USART_COUNT > 2
#endif // USART_COUNT > 1
#endif // defined(USART_COUNT) && USART_COUNT > 0
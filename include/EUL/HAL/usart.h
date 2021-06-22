/*
 * Copyright (c) 2020-2021 Tim Herreijgers
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

#ifndef EMBEDDED_UTILITY_LIBRARY_USART_H
#define EMBEDDED_UTILITY_LIBRARY_USART_H

#ifdef __cplusplus
extern "C" {
#endif

#include <inttypes.h>
#include <stdbool.h>
#include "EUL/platform/platform.h"

#include "EUL/HAL/digital_io.h"

#if defined(USART_COUNT) && USART_COUNT > 0

#ifndef USART_BUFFER_SIZE
#define USART_BUFFER_SIZE 32
#warning USART_BUFFER_SIZE not defined, defining it to be 32
#endif

#define USART_DATA_BITS_5 0
#define USART_DATA_BITS_6 1
#define USART_DATA_BITS_7 2
#define USART_DATA_BITS_8 3
#define USART_PARITY_BIT_NONE 0
#define USART_PARITY_BIT_ODD 2
#define USART_PARITY_BIT_EVEN 1
#define USART_STOP_BITS_1 0
#define USART_STOP_BITS_2 1

//TODO: Add event based reading of the usart port

typedef struct
{
    uint8_t databits;
    uint8_t parityBit;
    uint8_t stopBits;
} UsartFrameFormat_t;

struct Usart
{
    volatile uint8_t *registerBaudRateLow;
    volatile uint8_t *registerBaudRateHigh;
    volatile uint8_t *registerControlA;
    volatile uint8_t *registerControlB;
    volatile uint8_t *registerControlC;
    volatile uint8_t *registerData;
    UsartFrameFormat_t frameFormat;

    uint16_t txBufferHead;
    uint16_t txBufferTail;

    uint16_t rxBufferHead;
    uint16_t rxBufferTail;

    bool rs485FlowControlEnabled;

    uint8_t txBuffer[USART_BUFFER_SIZE];
    uint8_t rxBuffer[USART_BUFFER_SIZE];
    Pin_t rs485FlowControlPin;
};

void usart_setFrameFormat(struct Usart *usart, UsartFrameFormat_t frameFormat);
void usart_begin(struct Usart *usart, uint32_t baud);
void usart_end(struct Usart *usart);
int usart_available(struct Usart *usart);
bool usart_print(struct Usart *usart, const char *msg);
bool usart_println(struct Usart *usart, const char *msg);
void usart_write(struct Usart *usart, uint8_t byte);
uint8_t usart_read(struct Usart *usart);
void usart_enableRS485FlowControl(struct Usart *usart, Pin_t pin);
void usart_disableRs485FlowControl(struct Usart *usart);

extern struct Usart *usart0;

#if USART_COUNT > 1
extern struct Usart *usart1;
#if USART_COUNT > 2
extern struct Usart *usart2;
#if USART_COUNT > 3
extern struct Usart *usart3;
#endif // USART_COUNT > 3
#endif // USART_COUNT > 2
#endif // USART_COUNT > 1

#endif // defined(USART_COUNT) && USART_COUNT > 0

#ifdef __cplusplus
}
#endif

#endif //EMBEDDED_UTILITY_LIBRARY_USART_H

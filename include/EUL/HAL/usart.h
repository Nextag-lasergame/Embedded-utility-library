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

#ifndef EMBEDDED_UTILITY_LIBRARY_USART_H
#define EMBEDDED_UTILITY_LIBRARY_USART_H

#include <inttypes.h>
#include <stdbool.h>

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

void usart_setFrameFormat(UsartFrameFormat_t frameFormat);
void usart_begin(uint32_t baud);
void usart_end();
int usart_available();
bool usart_print(const char *msg);
bool usart_println(const char *msg);
void usart_write(uint8_t byte);
uint8_t usart_read();

#endif //EMBEDDED_UTILITY_LIBRARY_USART_H

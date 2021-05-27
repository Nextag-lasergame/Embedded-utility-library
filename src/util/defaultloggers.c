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

#ifndef NATIVE_BUILD

#include "EUL/util/defaultloggers.h"
#include "EUL/HAL/usart.h"

#define F_CPU 16000000L
#include <util/delay.h>
#include <avr/io.h>

void usartLogger9600Init();
void usartLogger115200Init();
void usartLoggerLog(const char * msg);

Logger_t usartLogger9600 = { usartLogger9600Init, usartLoggerLog };
Logger_t usartLogger115200 = { usartLogger115200Init, usartLoggerLog };

void usartLogger9600Init()
{
    usart_begin(usart0, 9600);
}

void usartLogger115200Init()
{
    usart_begin(usart0, 115200);
}

void usartLoggerLog(const char * msg)
{
    while(!usart_println(usart0, msg));
}

#endif
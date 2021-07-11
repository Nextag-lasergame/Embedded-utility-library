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

//TODO: Add checks for F_CPU and shizzle

#ifndef EMBEDDED_UTILITY_LIBRARY_IR_REMOTE_H
#define EMBEDDED_UTILITY_LIBRARY_IR_REMOTE_H

#if 0

#ifdef __cplusplus
extern "C" {
#endif

#include "EUL/HAL/timer.h"
#include "EUL/HAL/digital_io.h"

void ir_init(Timer_t timer, Pin_t pin);
void ir_stop();
void ir_sendSamsungRaw(uint32_t data);

bool ir_available();
uint32_t ir_read();

#ifdef __cplusplus
}
#endif

#endif

#endif //EMBEDDED_UTILITY_LIBRARY_IR_REMOTE_H

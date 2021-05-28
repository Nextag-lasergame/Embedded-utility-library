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

#ifndef EMBEDDED_UTILITY_LIBRARY_TIMER_H
#define EMBEDDED_UTILITY_LIBRARY_TIMER_H

#ifdef __cplusplus
extern "C" {
#endif

#include <inttypes.h>
#include "stdbool.h"

typedef uint8_t Timer_t;

typedef enum
{
    NORMAL,
    FAST_PWM,
    PHASE_CORRECT_PWM,
    CTC
} TimerMode_t;

typedef enum
{
    PRESCALER_0,
    PRESCALER_1,
    PRESCALER_8,
    PRESCALER_64,
    PRESCALER_128,
    PRESCALER_256,
    PRESCALER_512,
    PRESCALER_1024
} TimerPrescaler_t;

bool timer_setMode(Timer_t timer, uint8_t mode);
bool timer_setPrescaler(Timer_t timer, TimerPrescaler_t prescaler);
bool timer_setMaxCompA(Timer_t timer, uint16_t max);
bool timer_setMaxCompB(Timer_t timer, uint16_t max);
bool timer_enableInterruptCompA(Timer_t timer, bool enabled);
bool timer_enableInterruptCompB(Timer_t timer, bool enabled);
bool timer_enableInterruptOverflow(Timer_t timer, bool enabled);
bool timer_setCompAVectCallback(Timer_t timer, void (*callback));
bool timer_setCompBVectCallback(Timer_t timer, void (*callback));
bool timer_setOverflowVectCallback(Timer_t timer, void (*callback));

#ifdef __cplusplus
}
#endif

#endif //EMBEDDED_UTILITY_LIBRARY_TIMER_H

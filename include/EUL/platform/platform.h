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

#ifndef EMBEDDED_UTILITY_LIBRARY_PLATFORM_H
#define EMBEDDED_UTILITY_LIBRARY_PLATFORM_H

#ifdef __cplusplus
extern "C" {
#endif

#define PIN_SHIFT(x) ((uint64_t) x << (uint64_t) 48)
#define DDR_SHIFT(x) ((uint64_t) x << (uint64_t) 32)
#define PORT_SHIFT(x) ((uint64_t) x << (uint64_t) 16)
#define BIT_SHIFT(x) ((uint64_t) x)

#define TIMER_CONTROLA_SHIFT(x) ((uint64_t) x << 56);
#define TIMER_CONTROLB_SHIFT(x) ((uint64_t) x << 48);
#define TIMER_OUTPUTA_SHIFT(x) ((uint64_t) x << 40);
#define TIMER_INTERRUPT_SHIFT(x) ((uint64_t) x << 32);
#define TIMER_PRESCALERS(x) ((uint64_t) x << 2)
#define TIMER_FLAGS(x) ((uint64_t) x)

#define TIMER_CONTROLA_SHIFT(x) ((uint64_t) x << 56);
#define TIMER_OUTPUTA_SHIFT(x) ((uint64_t) x << 48);
#define TIMER_INTERRUPT_SHIFT(x) ((uint64_t) x << 32);
#define TIMER_PRESCALERS(x) ((uint64_t) x << 8)
#define TIMER_FLAGS(x) ((uint64_t) x)

#define TIMER_PRESCALER_1_OFFSET (3 * 8)
#define TIMER_PRESCALER_8_OFFSET (3 * 7)
#define TIMER_PRESCALER_32_OFFSET (3 * 6)
#define TIMER_PRESCALER_64_OFFSET (3 * 5)
#define TIMER_PRESCALER_128_OFFSET (3 * 4)
#define TIMER_PRESCALER_256_OFFSET (3 * 3)
#define TIMER_PRESCALER_1024_OFFSET (3 * 2)
#define TIMER_PRESCALER_EXTERNAL_RISING_OFFSET (3 * 1)
#define TIMER_PRESCALER_EXTERNAL_FALLING_OFFSET (3 * 0)

#define TIMER_PRESCALER_1(x) ((uint64_t) x << TIMER_PRESCALER_1_OFFSET)
#define TIMER_PRESCALER_8(x) ((uint64_t) x << TIMER_PRESCALER_8_OFFSET)
#define TIMER_PRESCALER_32(x) ((uint64_t) x << TIMER_PRESCALER_32_OFFSET)
#define TIMER_PRESCALER_64(x) ((uint64_t) x << TIMER_PRESCALER_64_OFFSET)
#define TIMER_PRESCALER_128(x) ((uint64_t) x << TIMER_PRESCALER_128_OFFSET)
#define TIMER_PRESCALER_256(x) ((uint64_t) x << TIMER_PRESCALER_256_OFFSET)
#define TIMER_PRESCALER_1024(x) ((uint64_t) x << TIMER_PRESCALER_1024_OFFSET)
#define TIMER_PRESCALER_EXTERNAL_RISING(x) ((uint64_t) x << TIMER_PRESCALER_EXTERNAL_RISING_OFFSET)
#define TIMER_PRESCALER_EXTERNAL_FALLING(x) ((uint64_t) x << TIMER_PRESCALER_EXTERNAL_FALLING_OFFSET)

#define TIMER_FLAG_PWM_ENABLED ((uint64_t) 1 << 0)
#define TIMER_FLAG_PWM_DISABLED ((uint64_t) 0 << 0)
#define TIMER_FLAG_8_BITS ((uint64_t) 0 << 1)
#define TIMER_FLAG_16_BITS ((uint64_t) 1 << 1)

#ifdef __AVR_ATmega328P__
#include "atmega/atmega328p.h"
#endif

#ifdef __AVR_ATmega2560__
#include "atmega/atmega2560.h"
#endif

#if __AVR_ATtiny45__
#include "attiny/attiny45.h"
#endif

#ifdef __cplusplus
}
#endif

#endif //EMBEDDED_UTILITY_LIBRARY_PLATFORM_H

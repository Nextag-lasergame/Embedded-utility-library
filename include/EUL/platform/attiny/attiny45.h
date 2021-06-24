
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

#ifndef EMBEDDED_UTILITY_LIBRARY_ATTINY45_H
#define EMBEDDED_UTILITY_LIBRARY_ATTINY45_H

#include "../platform_macros.h"

#define DIO_PB0 {PIN_SHIFT(0x36) | DDR_SHIFT(0x37) | PORT_SHIFT(0x38) | BIT_SHIFT(0x00) }
#define DIO_PB1 {PIN_SHIFT(0x36) | DDR_SHIFT(0x37) | PORT_SHIFT(0x38) | BIT_SHIFT(0x01) }
#define DIO_PB2 {PIN_SHIFT(0x36) | DDR_SHIFT(0x37) | PORT_SHIFT(0x38) | BIT_SHIFT(0x02) }
#define DIO_PB3 {PIN_SHIFT(0x36) | DDR_SHIFT(0x37) | PORT_SHIFT(0x38) | BIT_SHIFT(0x03) }
#define DIO_PB4 {PIN_SHIFT(0x36) | DDR_SHIFT(0x37) | PORT_SHIFT(0x38) | BIT_SHIFT(0x04) }
#define DIO_PB5 {PIN_SHIFT(0x36) | DDR_SHIFT(0x37) | PORT_SHIFT(0x38) | BIT_SHIFT(0x05) }

#define TIMER_0 TIMER_FLAGS(TIMER_FLAG_8_BITS | TIMER_FLAG_PWM_ENABLED) | \
                TIMER_PRESCALERS((TIMER_PRESCALER_1(0b001) | TIMER_PRESCALER_8(0b010) | \
                                 TIMER_PRESCALER_64(0b011) | TIMER_PRESCALER_256(0b100) | \
                                 TIMER_PRESCALER_1024(0b101), TIMER_PRESCALER_EXTERNAL_FALLING (0b110) | \
                                 TIMER_PRESCALER_EXTERNAL_RISING(0b111))) | \
                TIMER_INTERRUPT_SHIFT(0x059) | \
                TIMER_OUTPUTA_SHIFT(0x39) | \
                TIMER_CONTROLA_SHIFT(0x3A) | \
                TIMER_CONTROLB_SHIFT(0x53)

#define TIMER_OUTPUT_REGISTER_DIFFERENCE -1

#define USART_COUNT 0
#define TIMER_COUNT 1

#endif //EMBEDDED_UTILITY_LIBRARY_ATTINY45_H

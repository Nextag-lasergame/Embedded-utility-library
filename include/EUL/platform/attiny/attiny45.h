
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

#ifdef __cplusplus
extern "C" {
#endif

#include "../platform_macros.h"
#include "EUL/HAL/timer.h"

#pragma region Peripheral counts

#define USART_COUNT 0
#define TIMER_COUNT 1

#pragma endregion
#pragma region DIO

#define DIO_PB0 {PIN_SHIFT(0x36) | DDR_SHIFT(0x37) | PORT_SHIFT(0x38) | BIT_SHIFT(0x00) }
#define DIO_PB1 {PIN_SHIFT(0x36) | DDR_SHIFT(0x37) | PORT_SHIFT(0x38) | BIT_SHIFT(0x01) }
#define DIO_PB2 {PIN_SHIFT(0x36) | DDR_SHIFT(0x37) | PORT_SHIFT(0x38) | BIT_SHIFT(0x02) }
#define DIO_PB3 {PIN_SHIFT(0x36) | DDR_SHIFT(0x37) | PORT_SHIFT(0x38) | BIT_SHIFT(0x03) }
#define DIO_PB4 {PIN_SHIFT(0x36) | DDR_SHIFT(0x37) | PORT_SHIFT(0x38) | BIT_SHIFT(0x04) }
#define DIO_PB5 {PIN_SHIFT(0x36) | DDR_SHIFT(0x37) | PORT_SHIFT(0x38) | BIT_SHIFT(0x05) }

#pragma endregion

#pragma region ADC

// Only use the first 2 bits, for now
typedef enum
{
    VCC = 0,
    AREF = 1,
    INTERNAL_1_1V = 2
} AdcReference_t;

//Only use MUX[4:0]
typedef enum
{
    ADC0,
    ADC1,
    ADC2,
    ADC3,
    ADC2_ADC2_1x,
    ADC2_ADC2_20x,
    ADC2_ADC3_1x,
    ADC2_ADC3_20x,
    ADC0_ADC0_1x,
    ADC0_ADC0_20x,
    ADC0_ADC1_1x,
    ADC0_ADC1_20x,
    Vbg,
    GND,
    ADC4 = 0b1111
} AdcChannel_t;

#pragma endregion

extern Timer_t *timer0;

#ifdef __cplusplus
}
#endif

#endif //EMBEDDED_UTILITY_LIBRARY_ATTINY45_H

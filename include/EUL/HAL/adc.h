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
#ifndef EMBEDDED_UTILITY_LIBRARY_ADC_H
#define EMBEDDED_UTILITY_LIBRARY_ADC_H

#include <inttypes.h>

#include "EUL/platform/platform.h"

typedef enum
{
    PRESCALER_2 = 1,
    PRESCALER_4 = 2,
    PRESCALER_8 = 3,
    PRESCALER_16 = 4,
    PRESCALER_32 = 5,
    PRESCALER_64 = 6,
    PRESCALER_128 = 7
} AdcPrescaler_t;

typedef enum
{
    FREE_RUNNING = 0,
    ANALOG_COMPARETOR = 1,
    EXTERNAL_INTERRUPT_REQUEST_0 = 2,
    TIMER_0_COMPARE_MATCH_A = 3,
    TIMER_0_OVERFLOW = 4
} AdcFreeRunningSource_t;

typedef void (*AdcCallback_t)(AdcChannel_t, uint16_t);

void adc_init();
void adc_deinit();
void adc_setReference(AdcReference_t source);
void adc_setPrescaler(AdcPrescaler_t prescaler);
void adc_setCallback(AdcCallback_t callback);
void adc_setAutoTriggerSource(AdcFreeRunningSource_t source);
void adc_startSingleConversion(AdcChannel_t channel);
void adc_startAutoTriggerConversion(AdcChannel_t channel);
void adc_stopAutoTriggerConversion();
uint16_t adc_startConversionBlocking(AdcChannel_t channel);

#endif
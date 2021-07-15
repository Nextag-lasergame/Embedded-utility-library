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

#ifndef UNIT_TEST

#include "EUL/EUL.h"
#include "EUL/HAL/adc.h"

void callback()
{
    dio_setOutput(DIO_PB3, !dio_getInput(DIO_PB3));
}

void adcCallback(uint16_t value)
{
    timer_setCompA(timer0, value * 255 / 1024);
}

int main()
{
    dio_setDirection(DIO_PB3, true);

    Timer_t *timer = timer0;
    timer_initCtc(timer, PRESCALER_1024);
    timer_setCompA(timer, 1);
    timer_setCallback(timer, ON_MATCH_COMP_A, callback);
    
    adc_enable();
    adc_setPrescaler(ADC_PRESCALER_2);
    adc_setReference(VCC);
    adc_setCallback(adcCallback);
    adc_startAutoTriggerConversion(ADC1);

    for(;;)
    {
        // uint32_t val = adc_startConversionBlocking(ADC1);
        // uint8_t timer_interval = val * 255 / 1024;
        // timer_setCompA(timer, timer_interval);
        // counter++;
        // timer_setCompA(timer, (uint8_t) (counter % 256));
    }
}

#endif
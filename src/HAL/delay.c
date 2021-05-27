//
// Created by timti on 25/05/2021.
//
#ifndef NATIVE_BUILD
#include "EUL/HAL/delay.h"
#include "util/delay.h"

void delay_ms(double ms)
{
    _delay_ms(ms);
}
#endif
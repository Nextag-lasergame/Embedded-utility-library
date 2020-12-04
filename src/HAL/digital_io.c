//
// Created by tim on 26.11.20.
//

#include <avr/io.h>
#include "EUL/HAL/digital_io.h"

#define GET_PIN(x) ((x & 0xFF000000) >> 24)
#define GET_DDR(x) ((x & 0x00FF0000) >> 16)
#define GET_PORT(x) ((x & 0x0000FF00) >> 8)
#define GET_BIT(x) (x & 0x000000FF)

void dio_setDirection(uint32_t pin, bool output)
{
    if(output)
        _SFR_IO8(GET_DDR(pin)) |= _BV(GET_BIT(pin));
    else
        _SFR_IO8(GET_DDR(pin)) &= ~_BV(GET_BIT(pin));
}

void dio_setOutput(uint32_t pin, bool output)
{
    if(output)
        _SFR_IO8(GET_PORT(pin)) |= _BV(GET_BIT(pin));
    else
        _SFR_IO8(GET_PORT(pin)) &= ~_BV(GET_BIT(pin));
}

bool dio_getInput(uint32_t pin)
{
    return (_SFR_IO8(GET_PIN(pin)) & _BV(GET_BIT(pin)));
}


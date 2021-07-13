#include "EUL/HAL/adc.h"
#include "avr/io.h"

void adc_init()
{
    ADCSRA |= _BV(ADEN);
}
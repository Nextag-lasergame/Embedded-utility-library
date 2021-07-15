#include "EUL/HAL/adc.h"
#include "avr/io.h"
#include "avr/interrupt.h"

static AdcCallback_t s_callback = 0x00;

void adc_enable()
{
    cli();
    ADCSRA |= _BV(ADEN) | _BV(ADIE);
    sei();
}

void adc_disable()
{
    cli();
    ADCSRA &= ~(_BV(ADEN) | _BV(ADIE));
    sei();
}

void adc_setReference(AdcReference_t source)
{
    #ifdef REFS2
    ADMUX &= ~(_BV(REFS2) | _BV(REFS1) | _BV(REFS0));
    #else
    ADMUX &= ~(_BV(REFS1) | _BV(REFS0));
    #endif
    ADMUX |= source << REFS0;
}

void adc_setPrescaler(AdcPrescaler_t prescaler)
{
    ADCSRA &= ~(_BV(ADPS2) | _BV(ADPS1) | _BV(ADPS0));
    ADCSRA |= prescaler << ADPS0;
}

void adc_setCallback(AdcCallback_t callback)
{
    s_callback = callback;
}

void adc_setAutoTriggerSource(AdcFreeRunningSource_t source)
{
    ADCSRB &= ~(_BV(ADTS2) | _BV(ADTS1) | _BV(ADTS0));
    ADCSRB |= source << ADTS0;
}

void adc_startSingleConversion(AdcChannel_t channel)
{
    #ifdef MUX4
    ADMUX &= ~(_BV(MUX4) | _BV(MUX3) | _BV(MUX2) | _BV(MUX1) | _BV(MUX0));
    #else
    ADMUX &= ~( _BV(MUX3) | _BV(MUX2) | _BV(MUX1) | _BV(MUX0));
    #endif
    ADMUX |= channel << MUX0;
    ADCSRA |= _BV(ADSC);
}

void adc_startAutoTriggerConversion(AdcChannel_t channel)
{
    ADCSRA |= _BV(ADATE);
    // We can do two things, we can either copy the code from single conversion or just call the function ;)
    adc_startSingleConversion(channel);
}

void adc_stopAutoTriggerConversion()
{
    ADCSRA &= ~(_BV(ADEN) | _BV(ADATE));
}

uint16_t adc_startConversionBlocking(AdcChannel_t channel)
{
    #ifdef MUX4
    ADMUX &= ~(_BV(MUX4) | _BV(MUX3) | _BV(MUX2) | _BV(MUX1) | _BV(MUX0));
    #else
    ADMUX &= ~( _BV(MUX3) | _BV(MUX2) | _BV(MUX1) | _BV(MUX0));
    #endif
    ADMUX |= channel << MUX0;

    ADCSRA |= _BV(ADSC);
    while(ADCSRA & _BV(ADSC));
    ADCSRA |= _BV(ADIF);
    return ADC;
}

ISR(ADC_vect)
{
    if(s_callback != 0x00)
    {
        s_callback(ADC);
    }
    ADCSRA |= _BV(ADIF);
}
#include "EUL/HAL/timer.h"
#include "EUL/platform/platform.h"

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdlib.h>

bool timer_initCtc(Timer_t *timer, enum TimerPrescaler prescaler)
{
    uint8_t offset = prescaler * 3;
    uint8_t prescalerValue = ((timer->prescalers & ((uint32_t) 0b111 << offset)) >> offset); 
    if (prescalerValue == 0)
        return false;

    cli();
    _MMIO_BYTE(timer->registerInterruptMask) = _BV(OCIE0A) | _BV(OCIE0B) | _BV(TOIE0);
    _MMIO_BYTE(timer->registerControlA) = (1 << WGM01); // Set mode to CTC
    _MMIO_BYTE(timer->registerControlB) = (prescalerValue & 0b001 << CS00) | (((prescalerValue & 0b010) >> 1) << CS01) | (((prescalerValue & 0b100) >> 2) << CS02); //
    sei();

    return true;
}

void timer_stop(Timer_t *timer)
{
    _MMIO_BYTE(timer->registerControlB) &= ~(_BV(CS00) | _BV(CS01) | _BV(CS02));
}

// TODO: Differentiate between 16 and 8 bit timers. 
void timer_setCompA(Timer_t *timer, uint16_t compA)
{    
    cli();
    // OCR0A = (uint8_t) compA;
    _MMIO_BYTE(timer->registerOutputA) = (uint8_t) compA;
    // TCCR0B |= _BV(FOC0A);
    _MMIO_BYTE(timer->registerControlB) |= _BV(FOC0A);
    sei();
}

// TODO: Differentiate between 16 and 8 bit timers. 
void timer_setCompB(Timer_t *timer, uint16_t compB)
{    
    OCR0B = (uint8_t) compB;
    TCCR0B |= _BV(FOC0B);
}

bool timer_setCallback(Timer_t *timer, enum TimerCallback callback, void (*callbackFunction)())
{
    if(!(callback >= 0 && callback < 3))
        return false;

    timer->callbacks[callback] = callbackFunction;
    return true;
}

bool timer_clearCallback(Timer_t *timer, enum TimerCallback callback)
{
    if(!(callback > 0 && callback < 3))
        return false;

    timer->callbacks[callback] = 0x00;
    return true;
}

ISR(TIMER0_COMPA_vect)
{
    if(timer0->callbacks[ON_MATCH_COMP_A] != 0x00)
        timer0->callbacks[ON_MATCH_COMP_A]();
}

ISR(TIMER0_COMPB_vect)
{
    if(timer0->callbacks[ON_MATCH_COMP_B] != 0x00)
        timer0->callbacks[ON_MATCH_COMP_B]();
}

ISR(TIMER0_OVF_vect)
{
    if(timer0->callbacks[ON_OVERFLOW] != 0x00)
        timer0->callbacks[ON_OVERFLOW]();
}
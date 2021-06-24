#include "EUL/HAL/timer.h"
#include "EUL/platform/platform.h"

#include <avr/io.h>
#include <avr/interrupt.h>

struct Timer
{
    union
    {
        uint64_t value;
        struct
        {
            uint32_t flagsAndPrescalers;
            uint8_t registerInterruptMask;
            uint8_t registerOutputA;
            uint8_t registerControlB;
            uint8_t registerControlA;
        };
    }; 

    void (* callbacks[3])();
};

Timer_t *timer_create(uint64_t intTimer)
{
    Timer_t *timer = (Timer_t *) malloc(sizeof(Timer_t));
    timer->value = intTimer;
    for(uint8_t i = 0; i < 3; i++)
        timer->callbacks[i] = 0x00;

    cli();
    _MMIO_BYTE(timer->registerInterruptMask) |= _BV(OCIE0A) | _BV(OCIE0B) | _BV(TOIE0);
    sei();

    return timer;
}

bool timer_delete(Timer_t *timer)
{
    free(timer);
    return true;
}

bool timer_initCtc(Timer_t *timer, enum TimerPrescaler prescaler)
{
    uint8_t prescalerValue = (timer->flagsAndPrescalers & (0b111 << prescaler * 3 + 2)) >> prescaler * 3 + 2;
    if (prescalerValue == 0)
        return false;

    _MMIO_BYTE(timer->registerControlA) |= (1 << WGM01); // Set mode to CTC
    _MMIO_BYTE(timer->registerControlB) |= (prescaler & 0b001 << CS00) | (prescaler & 0b010 << CS01) | (prescaler & 0b100 << CS02);

    return true;
}

void timer_stop(Timer_t *timer)
{
    _MMIO_BYTE(timer->registerControlB) &= ~(_BV(CS00) | _BV(CS01) | _BV(CS02));
}

// TODO: Differentiate between 16 and 8 bit timers. 
void timer_setCompA(Timer_t *timer, uint16_t compA)
{    
    _MMIO_BYTE(timer->registerOutputA) = (uint8_t) compA;
}

// TODO: Differentiate between 16 and 8 bit timers. 
void timer_setCompB(Timer_t *timer, uint16_t compB)
{    
    _MMIO_BYTE(timer->registerOutputA + TIMER_OUTPUT_REGISTER_DIFFERENCE) = (uint8_t) compB;
}

bool timer_setCallback(Timer_t *timer, enum TimerCallback callback, void (*callbackFunction))
{
    if(!(callback > 0 && callback < 3))
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
    
}

ISR(TIMER0_COMPB_vect)
{
    
}

ISR(TIMER0_OVF_vect)
{
    
}
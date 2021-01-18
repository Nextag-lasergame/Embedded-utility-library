//
// Created by timti on 14/01/2021.
//

#include <avr/io.h>
#include <avr/interrupt.h>

#ifdef __AVR_ATmega328P__

#include "timer.c"
#define TIMER_COUNT 3

static void set8BitMode(TimerData_t *timer, TimerMode_t mode);
static void set8BitPrescaler(TimerData_t *timer, TimerPrescaler_t prescaler);
static void set8BitMaxOutputCompareA(TimerData_t *timer, uint16_t value);
static void set8BitMaxOutputCompareB(TimerData_t *timer, uint16_t value);
static void enable8BInterruptOutputCompareA(TimerData_t *timer, bool enabled);
static void enable8BInterruptOutputCompareB(TimerData_t *timer, bool enabled);
static void enable8BInterruptOverflow(TimerData_t *timer, bool enabled);

static TimerData_t timers[] = {
        {TIMER_BITS_8, 0x6E44, set8BitMode, set8BitPrescaler, set8BitMaxOutputCompareA, set8BitMaxOutputCompareB,
                enable8BInterruptOutputCompareA,enable8BInterruptOutputCompareB, enable8BInterruptOverflow,
                {0x00, 0x00, 0x00},
                {0, 1, 2, 3, -1, 4, -1, 5}},
        {TIMER_BITS_16, 0x0000, set8BitMode, set8BitPrescaler, set8BitMaxOutputCompareA, set8BitMaxOutputCompareB,
                enable8BInterruptOutputCompareA,enable8BInterruptOutputCompareB, enable8BInterruptOverflow,
                {0x00, 0x00, 0x00},
                {-1, -1, -1, -1, -1, -1, -1, -1}},
        {TIMER_BITS_8, 0x70B0, set8BitMode, set8BitPrescaler, set8BitMaxOutputCompareA, set8BitMaxOutputCompareB,
                enable8BInterruptOutputCompareA,enable8BInterruptOutputCompareB, enable8BInterruptOverflow,
                {0x00, 0x00, 0x00},
                {0, 1, 2, 3, 4, 5, 6, 7}}
};

static void set8BitMode(TimerData_t *timer, TimerMode_t mode)
{
    uint8_t controlRegisterA = GET_CONTROL_REGISTER_START(timer->registers);
    uint8_t controlRegisterB = GET_CONTROL_REGISTER_START(timer->registers) + 1;
    _SFR_MEM8(controlRegisterA) &= ~(_BV(WGM00) | _BV(WGM01));
    _SFR_MEM8(controlRegisterB) &= ~_BV(WGM02);

    switch (mode) {
        case NORMAL:
            break;
        case FAST_PWM:
            break;
        case PHASE_CORRECT_PWM:
            break;
        case CTC:
            _SFR_MEM8(controlRegisterA) |= _BV(WGM01);
            break;
    }
}

static void set8BitPrescaler(TimerData_t *timer, TimerPrescaler_t prescaler)
{
    uint8_t controlRegisterB = GET_CONTROL_REGISTER_START(timer->registers) + 1;
    _SFR_MEM8(controlRegisterB) &= ~(_BV(CS00) | _BV(CS01) | _BV(CS02));
    _SFR_MEM8(controlRegisterB) |= timer->prescalerValues[prescaler];

}

static void set8BitMaxOutputCompareA(TimerData_t *timer, uint16_t value)
{
    _SFR_MEM8(GET_CONTROL_REGISTER_START(timer->registers) + 3) = value;
}

static void set8BitMaxOutputCompareB(TimerData_t *timer, uint16_t value)
{
    _SFR_MEM8(GET_CONTROL_REGISTER_START(timer->registers) + 4) = value;
}

static void enable8BInterruptOutputCompareA(TimerData_t *timer, bool enabled)
{
    cli();
    if(enabled)
        _SFR_MEM8(GET_INTERRUPT_REGISTER_START(timer->registers)) |= _BV(OCIE0A);
    else
        _SFR_MEM8(GET_INTERRUPT_REGISTER_START(timer->registers)) &= ~_BV(OCIE0A);
    sei();
}

static void enable8BInterruptOutputCompareB(TimerData_t *timer, bool enabled)
{
    cli();
    if(enabled)
        _SFR_MEM8(GET_CONTROL_REGISTER_START(timer->registers)) |= _BV(OCIE0B);
    else
        _SFR_MEM8(GET_CONTROL_REGISTER_START(timer->registers)) &= ~_BV(OCIE0B);
    sei();
}

static void enable8BInterruptOverflow(TimerData_t *timer, bool enabled)
{
    cli();
    if(enabled)
        _SFR_IO8(GET_INTERRUPT_REGISTER_START(timer->registers)) |= _BV(TOV0);
    else
        _SFR_IO8(GET_INTERRUPT_REGISTER_START(timer->registers)) &= ~_BV(TOV0);
    sei();
}

ISR(TIMER0_COMPA_vect)
        {
                if(timers[0].callbacks[TIMER_CALLBACK_COMP_A] != 0x00)
                timers[0].callbacks[TIMER_CALLBACK_COMP_A]();
        }
ISR(TIMER0_COMPB_vect)
        {
                if(timers[0].callbacks[TIMER_CALLBACK_COMP_B] != 0x00)
                timers[0].callbacks[TIMER_CALLBACK_COMP_B]();
        }
ISR(TIMER0_OVF_vect)
        {
                if(timers[0].callbacks[TIMER_CALLBACK_OVERFLOW] != 0x00)
                timers[0].callbacks[TIMER_CALLBACK_OVERFLOW]();
        }

ISR(TIMER1_COMPA_vect)
        {
                if(timers[1].callbacks[TIMER_CALLBACK_COMP_A] != 0x00)
                timers[1].callbacks[TIMER_CALLBACK_COMP_A]();
        }
ISR(TIMER1_COMPB_vect)
        {
                if(timers[1].callbacks[TIMER_CALLBACK_COMP_B] != 0x00)
                timers[1].callbacks[TIMER_CALLBACK_COMP_B]();
        }
ISR(TIMER1_OVF_vect)
        {
                if(timers[1].callbacks[TIMER_CALLBACK_OVERFLOW] != 0x00)
                timers[1].callbacks[TIMER_CALLBACK_OVERFLOW]();
        }

ISR(TIMER2_COMPA_vect)
        {
                if(timers[2].callbacks[TIMER_CALLBACK_COMP_A] != 0x00)
                timers[2].callbacks[TIMER_CALLBACK_COMP_A]();
        }
ISR(TIMER2_COMPB_vect)
        {
                if(timers[2].callbacks[TIMER_CALLBACK_COMP_B] != 0x00)
                timers[2].callbacks[TIMER_CALLBACK_COMP_B]();
        }
ISR(TIMER2_OVF_vect)
        {
                if(timers[2].callbacks[TIMER_CALLBACK_OVERFLOW] != 0x00)
                timers[2].callbacks[TIMER_CALLBACK_OVERFLOW]();
        }

bool timer_setMode(Timer_t timer, uint8_t mode)
{
    CHECK_VALID_TIMER(timer)
    timers[timer].setMode(&timers[timer], mode);
    return true;
}

bool timer_setPrescaler(Timer_t timer, TimerPrescaler_t prescaler)
{
    CHECK_VALID_TIMER(timer)
    if(timers[timer].prescalerValues[prescaler] == -1)
        return false;

    timers[timer].setPrescaler(&timers[timer], prescaler);
    return true;
}

bool timer_setMaxCompA(Timer_t timer, uint16_t max)
{
    CHECK_VALID_TIMER(timer)
    timers[timer].setMaxOutputCompareA(&timers[timer], max);
    return true;
}

bool timer_enableInterruptCompA(Timer_t timer, bool enabled)
{
    CHECK_VALID_TIMER(timer)
    timers[timer].enableInterruptOutputCompareA(&timers[timer], enabled);
    return true;
}

bool timer_setCompAVectCallback(Timer_t timer, void (*callback))
{
    CHECK_VALID_TIMER(timer)
    timers[timer].callbacks[TIMER_CALLBACK_COMP_A] = callback;
    return true;
}

#endif


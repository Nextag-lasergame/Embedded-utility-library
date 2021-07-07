#include "EUL/platform/platform.h"
#include "avr/io.h"
#include "internal/timer_internal.h"

// #define TIMER_0 TIMER_FLAGS(TIMER_FLAG_8_BITS | TIMER_FLAG_PWM_ENABLED) | \
//                 TIMER_PRESCALERS((TIMER_PRESCALER_1(0b001) | TIMER_PRESCALER_8(0b010) | \
//                                  TIMER_PRESCALER_64(0b011) | TIMER_PRESCALER_256(0b100) | \
//                                  TIMER_PRESCALER_1024(0b101), TIMER_PRESCALER_EXTERNAL_FALLING (0b110) | \
//                                  TIMER_PRESCALER_EXTERNAL_RISING(0b111))) | \
//                 TIMER_INTERRUPT_SHIFT(0x59) | \
//                 TIMER_OUTPUTA_SHIFT(0x49) | \
//                 TIMER_CONTROLA_SHIFT(0x4A) | \
//                 TIMER_CONTROLB_SHIFT(0x53)

static Timer_t timer0NoPtr =
{
    TIMER_FLAGS(TIMER_FLAG_8_BITS | TIMER_FLAG_PWM_ENABLED),
    (TIMER_PRESCALER_1(0b001) | TIMER_PRESCALER_8(0b010) | 
                                 TIMER_PRESCALER_64(0b011) | TIMER_PRESCALER_256(0b100) | 
                                 TIMER_PRESCALER_1024(0b101) | TIMER_PRESCALER_EXTERNAL_FALLING (0b110) | 
                                 TIMER_PRESCALER_EXTERNAL_RISING(0b111)),
    &TIMSK,
    &OCR0A,
    &OCR0B,
    &TCCR0B,
    &TCCR0A,
    {
        0x00,
        0x00,
        0x00
    }
};

Timer_t *timer0 = &timer0NoPtr;
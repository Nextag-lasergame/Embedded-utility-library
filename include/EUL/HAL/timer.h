//
// Created by timti on 07/01/2021.
//

#ifndef EMBEDDED_UTILITY_LIBRARY_TIMER_H
#define EMBEDDED_UTILITY_LIBRARY_TIMER_H

#include <inttypes.h>
#include "stdbool.h"

typedef uint8_t Timer_t;

typedef enum {
    NORMAL,
    FAST_PWM,
    PHASE_CORRECT_PWM,
    CTC
}TimerMode_t;

typedef enum
{
    PRESCALER_0,
    PRESCALER_1,
    PRESCALER_8,
    PRESCALER_64,
    PRESCALER_128,
    PRESCALER_256,
    PRESCALER_512,
    PRESCALER_1024
} TimerPrescaler_t;

bool timer_setMode(Timer_t timer, uint8_t mode);
bool timer_setPrescaler(Timer_t timer, TimerPrescaler_t prescaler);
bool timer_setMaxCompA(Timer_t timer, uint16_t max);
bool timer_setMaxCompB(Timer_t timer, uint16_t max);
bool timer_enableInterruptCompA(Timer_t timer, bool enabled);
bool timer_enableInterruptCompB(Timer_t timer, bool enabled);
bool timer_enableInterruptOverflow(Timer_t timer, bool enabled);
bool timer_setCompAVectCallback(Timer_t timer, void (*callback));
bool timer_setCompBVectCallback(Timer_t timer, void (*callback));
bool timer_setOverflowVectCallback(Timer_t timer, void (*callback));
#endif //EMBEDDED_UTILITY_LIBRARY_TIMER_H

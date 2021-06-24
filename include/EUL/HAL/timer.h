#ifndef EMBEDDED_UTILITY_LIBRARY_TIMER_H
#define EMBEDDED_UTILITY_LIBRARY_TIMER_H

#include "stdbool.h"
#include "inttypes.h"

typedef struct Timer Timer_t;

enum TimerPrescaler
{
    PRESCALER_1, PRESCALER_8, PRESCALER_32, PRESCALER_64, PRESCALER_128, PRESCALER_256, PRESCALER_1024, EXTERNAL_RISING_EDGE, EXTERNAL_FALLING_EDGE
};

enum TimerCallback
{
    ON_MATCH_COMP_A, ON_MATCH_COMP_B, ON_OVERFLOW
};

Timer_t *timer_create(uint64_t timer);
bool timer_delete(Timer_t *timer);

bool timer_initCtc(Timer_t *timer, enum TimerPrescaler);
void timer_stop(Timer_t *timer);
void timer_setCompA(Timer_t *timer, uint16_t compA);
void timer_setCompB(Timer_t *timer, uint16_t compB);
bool timer_setCallback(Timer_t *timer, enum TimerCallback callback, void (*callbackFunction));
bool timer_clearCallback(Timer_t *timer, enum TimerCallback callback);

#endif
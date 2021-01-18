//
// Created by timti on 07/01/2021.
//

/*
 * TODO: Er is een verschil tussen de prescaler waardes van timer 1 en 2. Dit is fucking kut en moet je oplossen...
 */

#include "EUL/HAL/timer.h"

#define TIMER_BITS_8 0
#define TIMER_BITS_16 1

#define TIMER_CALLBACK_COMP_A 0
#define TIMER_CALLBACK_COMP_B 1
#define TIMER_CALLBACK_OVERFLOW 2

#define GET_CONTROL_REGISTER_START(x) (x & 0xFF)
#define GET_INTERRUPT_REGISTER_START(x) (x >> 8)
#define CHECK_VALID_TIMER(timer) if(timer >= sizeof(timers) / sizeof(TimerData_t)) return false;

/*
 * Building or the register integer:
 * The lsb points to the memory address of the first control register. The other control registers, counter register and compare registers follow sequentially.
 * The last byte points to the Timer Interrupt Register
 */
typedef struct TimerData
{
    uint8_t bitCount;
    uint16_t registers;
    void (*setMode)(struct TimerData *timer, TimerMode_t mode);
    void (*setPrescaler)(struct TimerData *timer, TimerPrescaler_t prescaler);
    void (*setMaxOutputCompareA)(struct TimerData *timer, uint16_t value);
    void (*setMaxOutputCompareB)(struct TimerData *timer, uint16_t value);
    void (*enableInterruptOutputCompareA)(struct TimerData *timer, bool enabled);
    void (*enableInterruptOutputCompareB)(struct TimerData *timer, bool enabled);
    void (*enableInterruptOverflow)(struct TimerData *timer, bool enabled);
    void (*callbacks[3])();
    int8_t prescalerValues[8];
} TimerData_t;
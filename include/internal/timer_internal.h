#ifndef _TIMER_INTERNAL_H_
#define _TIMER_INTERNAL_H_

#include "inttypes.h"

struct Timer
{
    uint8_t flags;
    uint32_t prescalers;
    uint8_t registerInterruptMask;
    uint8_t registerOutputA;
    uint8_t registerOutputB;
    uint8_t registerControlB;
    uint8_t registerControlA;

    void (* callbacks[3])();
};
#endif
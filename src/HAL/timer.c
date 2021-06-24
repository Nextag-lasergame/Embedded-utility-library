#include "EUL/HAL/timer.h"

#include "inttypes.h"
#include <avr/io.h>

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
            uint8_t registerControlA;
        };
    };  
};
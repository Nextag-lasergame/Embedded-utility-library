//
// Created by tim on 26.11.20.
//

#ifndef EMBEDDED_UTILITY_LIBRARY_DIGITAL_IO_H
#define EMBEDDED_UTILITY_LIBRARY_DIGITAL_IO_H

#include <inttypes.h>
#include "stdbool.h"

typedef struct
{
    union
    {
        uint32_t value;
        struct
        {
            uint8_t bit;
            uint8_t portRegister;
            uint8_t ddrRegister;
            uint8_t pinRegister;
        };
    };
} Pin_t;

#ifdef __AVR_ATmega328P__
#include "digital_io/atmega328p.h"
#endif

extern void dio_setDirection(Pin_t pin, bool output);
extern void dio_setOutput(Pin_t pin, bool high);
extern bool dio_getInput(Pin_t pin);

#endif //EMBEDDED_UTILITY_LIBRARY_DIGITAL_IO_H

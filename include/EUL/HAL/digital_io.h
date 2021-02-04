/*
 * Copyright (c) 2020 Tim Herreijgers
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated
 * documentation files (the "Software"), to deal in the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial
 * portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO
 * THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

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

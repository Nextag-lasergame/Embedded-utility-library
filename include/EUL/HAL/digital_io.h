//
// Created by tim on 26.11.20.
//

#ifndef EMBEDDED_UTILITY_LIBRARY_DIGITAL_IO_H
#define EMBEDDED_UTILITY_LIBRARY_DIGITAL_IO_H

#include <inttypes.h>
#include "stdbool.h"

#ifdef __AVR_ATmega328P__
#include "digital_io/atmega328p.h"
#endif

#define DIO_DIRECTION_OUTPUT 1
#define DIO_DIRECTION_INPUT 0
#define DIO_OUTPUT_HIGH 1
#define DIO_OUTPUT_LOW 0

extern void dio_setDirection(uint32_t pin, uint8_t direction);
extern void dio_setOutput(uint32_t pin, uint8_t output);
extern bool dio_getInput(uint32_t pin);

#endif //EMBEDDED_UTILITY_LIBRARY_DIGITAL_IO_H

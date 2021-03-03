//
// Created by timti on 03/03/2021.
//

#ifndef EMBEDDED_UTILITY_LIBRARY_PLATFORM_H
#define EMBEDDED_UTILITY_LIBRARY_PLATFORM_H

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __AVR_ATmega328P__
#include "atmega//atmega328p.h"
#endif

#ifdef __AVR_ATmega2560__
#include "atmega//atmega2560.h"
#endif

#ifdef __cplusplus
}
#endif

#endif //EMBEDDED_UTILITY_LIBRARY_PLATFORM_H

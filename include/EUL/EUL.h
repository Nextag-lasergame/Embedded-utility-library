//
// Created by tim on 04.12.20.
//

#ifndef EMBEDDED_UTILITY_LIBRARY_EUL_H
#define EMBEDDED_UTILITY_LIBRARY_EUL_H

#ifdef __cplusplus
extern "C" {
#endif

#ifndef NATIVE_BUILD

#include "EUL/platform/platform.h"

#include "EUL/HAL/delay.h"
#include "EUL/HAL/digital_io.h"
#include "EUL/HAL/timer.h"
#include "EUL/HAL/twi.h"
#include "EUL/HAL/usart.h"

#include "EUL/util/loglevels.h"

#endif

#include "EUL/util/linked_list.h"
#include "EUL/util/state_machine.h"

#ifdef __cplusplus
}
#endif

#endif //EMBEDDED_UTILITY_LIBRARY_EUL_H

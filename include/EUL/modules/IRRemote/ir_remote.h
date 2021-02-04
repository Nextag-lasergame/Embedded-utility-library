//
// Created by timti on 18/01/2021.
//

//TODO: Add checks for F_CPU and shizzle

#ifndef EMBEDDED_UTILITY_LIBRARY_IR_REMOTE_H
#define EMBEDDED_UTILITY_LIBRARY_IR_REMOTE_H

#include "EUL/HAL/timer.h"
#include "EUL/HAL/digital_io.h"

void ir_init(Timer_t timer, Pin_t pin);
void ir_stop();
void ir_sendSamsungRaw(uint32_t data);

bool ir_available();
uint32_t ir_read();


#endif //EMBEDDED_UTILITY_LIBRARY_IR_REMOTE_H

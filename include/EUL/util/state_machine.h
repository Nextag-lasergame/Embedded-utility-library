//
// Created by timti on 27/05/2021.
//

#ifndef EMBEDDED_UTILITY_LIBRARY_STATE_MACHINE_H
#define EMBEDDED_UTILITY_LIBRARY_STATE_MACHINE_H

#include "inttypes.h"

enum errorCodes
{
    UNKNOWN_TRANSITION = 0
};


struct state
{
    uint8_t stateCode;
    uint8_t (* stateFunction)();
};

struct transition {
    struct state src_state;
    uint8_t   ret_code;
    struct state dst_state;
};

void sm_init(struct transition *transitionTable, uint8_t transitionsTableSize, struct state *startState, struct state endState, void (*errorFunc)(enum errorCodes));
void sm_start();

#endif //EMBEDDED_UTILITY_LIBRARY_STATE_MACHINE_H

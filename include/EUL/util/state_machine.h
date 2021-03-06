/*
 * Copyright (c) 2020-2021 Tim Herreijgers
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

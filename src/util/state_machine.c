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

#include "EUL/util/state_machine.h"

static struct transition *transitionTable = 0x00;
static uint8_t transitionsTableSize;
static uint8_t endStateCode;
static struct state *currentState;
static void (*errorFunc)(enum errorCodes);

static struct state *lookupNextState(uint8_t code);

void sm_init(struct transition *transitionTable_, uint8_t transitionsTableSize_, struct state *startState, struct state endState, void (*errorFunc_)(enum errorCodes))
{
    transitionTable = transitionTable_;
    transitionsTableSize = transitionsTableSize_;
    endStateCode = endState.stateCode;
    currentState = startState;
    errorFunc = errorFunc_;
}

void sm_start()
{
    if(transitionTable == 0x00)
        return;

    while(1)
    {
        uint8_t returnCode = currentState->stateFunction();

        if(currentState->stateCode == endStateCode)
            return;

        struct state *nextState = lookupNextState(returnCode);
        if (nextState == 0x00)
        {
            errorFunc(UNKNOWN_TRANSITION);
            return;
        }

        currentState = nextState;
    }
}

static struct state *lookupNextState(uint8_t code)
{
    for(uint8_t i = 0; i < transitionsTableSize; i++)
    {
        struct transition *trans = &(transitionTable[i]);
        if (trans->src_state.stateCode == currentState->stateCode && trans->ret_code == code)
            return &trans->dst_state;
    }
    return 0x00;
}

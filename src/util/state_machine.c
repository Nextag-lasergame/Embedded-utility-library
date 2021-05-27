//
// Created by timti on 27/05/2021.
//

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

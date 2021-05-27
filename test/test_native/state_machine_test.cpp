//
// Created by timti on 27/05/2021.
//

#include <iostream>
#include <unity.h>
#include "state_machine_test.h"
#include "EUL/EUL.h"

void smTestStartBeforeInit();
void smTestStateMachineTransitionHappening();
void smTestErrorMessage();

void stateMachineTest()
{
    RUN_TEST(smTestStartBeforeInit);
    RUN_TEST(smTestStateMachineTransitionHappening);
    RUN_TEST(smTestErrorMessage);
}

static uint8_t count = 0;
static std::string order = "";

static uint8_t startState()
{
    count++;
    order.append("0");
    return 0;
}

static uint8_t middleState()
{
    count++;
    order.append("1");
    if(count == 2)
        return 1;

    return 0;
}

static uint8_t throwErrorState()
{
    return 100;
}

static uint8_t endState()
{
    order.append("2");
    count++;
    return 0;
}

static void error(enum errorCodes)
{
    count = 100;
}

void smTestStartBeforeInit()
{
    sm_start();
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(0, count, "Some states have executed");
}

void smTestStateMachineTransitionHappening()
{
    struct state states[] =
            {
                    {0, startState},
                    {1, middleState},
                    {2, endState}
            };

    struct transition transitions[] =
            {
                    {states[0], 0, states[1]},
                    {states[1], 0, states[2]},
                    {states[1], 1, states[0]}
            };

    sm_init(transitions, 3, &(states[0]), states[2], error);
    sm_start();

    TEST_ASSERT_EQUAL_UINT8_MESSAGE(5, count, "Count is not equal to 5, meaning that the state "
                                              "machine didn't execute the states properly");
    TEST_ASSERT_EQUAL_STRING_MESSAGE("01012", order.c_str(), "Executed order doesn't match what it is supposed to");

}

void smTestErrorMessage()
{
    struct state states[] =
            {
                    {0, startState},
                    {1, throwErrorState},
                    {2, endState}
            };

    struct transition transitions[] =
            {
                    {states[0], 0, states[1]},
                    {states[1], 0, states[2]},
                    {states[1], 1, states[0]}
            };

    sm_init(transitions, 3, &(states[0]), states[2], error);
    sm_start();

    TEST_ASSERT_EQUAL_UINT8_MESSAGE(100, count, "Error has not been thrown in the state machine");
}
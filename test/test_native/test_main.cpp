#include <unity.h>

#include "linked_list_test.h"
#include "state_machine_test.h"

int main()
{
    UNITY_BEGIN();
    linkedListTest();
    stateMachineTest();
    UNITY_END();
}

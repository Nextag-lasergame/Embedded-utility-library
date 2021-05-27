#define F_CPU 16000000L

#include <unity.h>
#include "linked_list_test.h"
#include "EUL/EUL.h"

int main()
{
    UNITY_BEGIN();
    linked_list_test();
    UNITY_END();
}

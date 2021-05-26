#define F_CPU 16000000L

#include <unity.h>
#include "EUL/EUL.h"

void test()
{
    TEST_ASSERT(1 == 1)
}

void test2()
{
    TEST_ASSERT(2 == 1);
}

int main()
{
    delay_ms(2000);
    UNITY_BEGIN();
    RUN_TEST(test);
    RUN_TEST(test2);
    UNITY_END();
}

#ifdef EUL_TEST_BUILD

extern "C" {
    #include "EUL/HAL/twi.h"
};

int main()
{
    twi_begin();
    twi_setAddress(127);
}

#endif
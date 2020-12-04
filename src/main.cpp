#ifdef EUL_TEST_BUILD

#define F_CPU 16000000L

#include <util/delay.h>
#include <avr/io.h>

extern "C" {
    #include <EUL/HAL/usart.h>
    #include "EUL/util/logger.h"
    #include "EUL/util/defaultloggers.h"
    #include "EUL/HAL/digital_io.h"
};

int main()
{
//    logger_addLogger(&usartLogger9600);
//    logger_init();

//    logger_trace("Hoi");
//    logger_debug("Hoi debug\n");
//    logger_debug("Test 2\n");
//    logger_debug("Test 3\n");
//    logger_debug("Test 4\n");
//    logger_debug("Test 5\n");
//    logger_debug("Test 6\n");
//    logger_debug("Test 7\n");

    uint32_t led = DIO_PB5;
    uint32_t input = DIO_PB0;
    dio_setDirection(led, true);
    dio_setDirection(input, false);

    for(;;)
    {
//        char msg[32];
//        itoa(((input & 0xFF000000) >> 24), msg, 16);
//        Serial.println(msg);

        if(dio_getInput(input))
        {
            dio_setOutput(led, true);
        }
        else
        {
            dio_setOutput(led, false);
        }

    }
}

#endif
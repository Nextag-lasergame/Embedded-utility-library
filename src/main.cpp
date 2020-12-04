#ifdef EUL_TEST_BUILD

#define F_CPU 16000000L

#include <util/delay.h>
#include <EUL/EUL.h>

int main()
{
    logger_addLogger(&usartLogger115200);
    logger_init();

    logger_trace("Hoi");
    logger_debug("Hoi debug\n");
    logger_debug("Test 2\n");
    logger_debug("Test 3\n");
    logger_debug("Test 4\n");
    logger_debug("Test 5\n");
    logger_debug("Test 6\n");
    logger_debug("Test 7\n");

//    uint32_t led = DIO_PB5;
//    uint32_t input = DIO_PB0;
//    dio_setDirection(led, true);
//    dio_setDirection(input, false);
    for(;;)
    {
        logger_debug("Test\n");
        _delay_ms(1);
//        Serial.println(msg);

//        if(dio_getInput(input))
//        {
//            dio_setOutput(led, true);
//        }
//        else
//        {
//            dio_setOutput(led, false);
//        }

    }
}

#endif
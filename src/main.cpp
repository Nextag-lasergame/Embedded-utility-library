#ifdef EUL_TEST_BUILD

#define F_CPU 16000000L

#include <util/delay.h>
#include <avr/io.h>

extern "C" {
#include <EUL/HAL/usart.h>
#include "EUL/util/logger.h"
#include "EUL/util/defaultloggers.h"
};

int main()
{
    DDRB = _BV(PORTB5);
    logger_addLogger(&usartLogger9600);
    logger_init();

    logger_trace("Hoi");
    logger_debug("Hoi debug\n");
    logger_debug("Test 2\n");
    logger_debug("Test 3\n");
    logger_debug("Test 4\n");
    logger_debug("Test 5\n");
    logger_debug("Test 6\n");
    logger_debug("Test 7\n");

//    usart_begin(115200);
//    if(!usart_print("Test 3\n"))
//    {
//        PORTB = 0xFF;
//    }

    for(;;)
    {
        _delay_ms(100);
    }
}

#endif
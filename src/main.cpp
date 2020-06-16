#ifdef EUL_TEST_BUILD

#define F_CPU 16000000L

#include <util/delay.h>
#include <avr/io.h>
#include "EUL/util/loglevels.h"

//#define LOG_LEVEL LOG_LEVEL_WARN

extern "C" {
    #include "EUL/util/logger.h"
    #include "EUL/util/defaultloggers.h"
};

int main()
{
    DDRB = _BV(PORTB5);
    logger_addLogger(&usartLogger115200);
    logger_init();

    logger_trace("Hoi");
    logger_debug("Hoi debug");
//    _delay_ms(100);
    logger_info("Hoi info");
//    _delay_ms(100);
    logger_warn("Hoi warn");
//    _delay_ms(100);
    logger_error("Hoi error");

    for(;;)
    {
        _delay_ms(100);
    }
}

#endif
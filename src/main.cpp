#ifdef EUL_TEST_BUILD

#define F_CPU 16000000L

#define assert_true(statement, message) if(!statement) logger_debug(message)

#include "avr/io.h"

#include <EUL/EUL.h>
extern "C" {
#include <EUL/modules/IRRemote/ir_remote.h>
}
#include <util/delay.h>

uint32_t led = DIO_PB0;

int main()
{
//    CLKPR = _BV(CLKPCE);
//    CLKPR &= ~(_BV(CLKPS0) | _BV(CLKPS1) | _BV(CLKPS2) | _BV(CLKPS3));

//    logger_addLogger(&usartLogger115200);
//    logger_init();
    usart_begin(115200);

    while(!usart_println("Starting boot procedure"));
    dio_setDirection(led, true);
//    while(!usart_println("Output led direction set"));
//    while(!usart_println("Initializing ir module"));
    ir_init(0, led);
//    while(!usart_println("Initialized ir module"));
    while(!usart_println("Finished boot procedure"));

    ir_sendSamsungRaw(0xE0E0D02F);
//    _delay_ms(1000);
//    usart_println("Sent samsung ir message");

    for(;;)
    {
//        dio_setOutput(led, true);
//        dio_setOutput(led, false);
//        _delay_ms(250);

//        dio_setOutput(led, true);
//        dio_setOutput(led, false);
    }
}
#endif
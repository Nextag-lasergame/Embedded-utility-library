#ifndef EUL_TEST_BUILD

//#define F_CPU 16000000L

#define print(x) while(!usart_println(x))

#define assert_true(statement, message) if(!statement) logger_debug(message)

#include <EUL/EUL.h>
extern "C" {
#include <EUL/modules/IRRemote/ir_remote.h>
}
#include <util/delay.h>
#include <inttypes.h>

uint32_t input = DIO_PB1;
uint32_t led = DIO_PB5;

int main()
{
//    logger_addLogger(&usartLogger115200);
//    logger_init();
    usart_begin(115200);
//
    print("Starting boot procedure");
    dio_setDirection(led, true);
    dio_setDirection(input, true);
    while(!usart_println("Output led direction set"));
    while(!usart_println("Initializing ir module"));
    ir_init(0, input);
    while(!usart_println("Initialized ir module"));
    while(!usart_println("Finished boot procedure"));

//    ir_sendSamsungRaw(0xE0E0D02F);

    for(;;)
    {
        if(ir_available())
        {
//            dio_setOutput(led, true);
            uint32_t data = ir_read();
//            char hex[32];
//
//            sprintf(hex, "0x%" PRIX32, data);
//            while(!usart_print("Received hex value: "));
//            while(!usart_println(hex));
            if(data == 0xE0E0D02F)
                while(!usart_println("Volume down is pressed"));
            if(data == 0xE0E0E01F)
                while(!usart_println("Volume up is pressed"));


        }
        _delay_ms(100);
//
    }
}
#endif

#define F_CPU 16000000L

#include "EUL/EUL.h"
#include <util/delay.h>

#define F_CPU 16000000L

#include "EUL/EUL.h"
#include <util/delay.h>

int main()
{
    Pin_t led = {DIO_PB5};
    dio_setDirection(led, true);

    for(;;)
    {
        dio_setOutput(led, !dio_getInput(led));
        _delay_ms(1000);
    }
}


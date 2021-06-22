/*
 * Copyright (c) 2020-2021 Tim Herreijgers
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated
 * documentation files (the "Software"), to deal in the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial
 * portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO
 * THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#ifndef UNIT_TEST

#if 0

//#define F_CPU 16000000L

#define print(x) while(!usart_println(x))

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

#include "EUL/EUL.h"

int main()
{
    dio_setDirection(DIO_PB0, true);
    dio_setOutput(DIO_PB0, true);

    for(;;)
    {
        
    }
}

#endif
#define F_CPU 16000000L

#include "EUL/EUL.h"
#include <util/delay.h>

int main()
{
    usart_begin(115200);
    usart_println("Hello world!");

    for(;;)
    {
        _delay_ms(1000);
        usart_println("BeepBoop");
    }
}


#ifdef EUL_TEST_BUILD

#define F_CPU 16000000L

#include <util/delay.h>
#include <avr/io.h>

extern "C" {
    #include "EUL/HAL/usart.h"
};

int main()
{
    DDRB = _BV(PORTB5);
    usart_begin(9600);

    for(;;)
    {
        while(usart_available() > 0)
        {
            usart_write(usart_read());
        }
        //byte == 'a' ? PORTB &= ~(1<<PORTB5) : PORTB |= (1<<PORTB5);

//        usart_println("Hoi") ? PORTB &= ~(1<<PORTB5) : PORTB |= (1<<PORTB5);
//        usart_write(counter++);
//        usart_write('\n');
        _delay_ms(100);
    }
}

#endif
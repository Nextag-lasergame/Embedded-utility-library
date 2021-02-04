#define F_CPU 16000000L

#include "EUL/EUL.h"
#include <util/delay.h>

int main()
{
    Pin_t led = DIO_PB5;
    dio_setDirection(led, true);

    for(;;)
    {
        dio_setOutput(led, !dio_getInput(led));
        _delay_ms(1000);
    }
}

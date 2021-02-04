#define F_CPU 16000000L

#include "EUL/EUL.h"
#include <util/delay.h>

int main()
{
    dio_setDirection(DIO_PB5, true);

    for(;;)
    {
        dio_setOutput(DIO_PB5, !dio_getInput(DIO_PB5));
        _delay_ms(1000);
    }
}

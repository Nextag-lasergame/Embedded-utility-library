#include "EUL/util/defaultloggers.h"
#include "EUL/HAL/usart.h"

#define F_CPU 16000000L
#include <util/delay.h>

void usartLogger9600Init();
void usartLogger115200Init();
void usartLoggerLog(const char * msg);

Logger_t usartLogger9600 = { usartLogger9600Init, usartLoggerLog };
Logger_t usartLogger115200 = { usartLogger115200Init, usartLoggerLog };

void usartLogger9600Init()
{
    usart_begin(9600);
}

void usartLogger115200Init()
{
    usart_begin(115200);
}

void usartLoggerLog(const char * msg)
{
    usart_println(msg);
}
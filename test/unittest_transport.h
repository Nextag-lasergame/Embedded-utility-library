#ifndef UNITTEST_TRANSPORT_H
#define UNITTEST_TRANSPORT_H

#include <stdio.h>
#include <EUL/HAL/usart.h>

void unittest_uart_begin() {
    usart_begin(usart0, 9600);
}

void unittest_uart_putchar(char c) {
    usart_write(usart0, c);
}

void unittest_uart_flush() {

}

void unittest_uart_end() {

}

#endif
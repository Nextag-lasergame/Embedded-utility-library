//
// Created by Tim on 16/06/2020.
//

#ifndef EMBEDDED_UTILITY_LIBRARY_USART_H
#define EMBEDDED_UTILITY_LIBRARY_USART_H

#include <inttypes.h>
#include <stdbool.h>

#define USART_DATA_BITS_5 5
#define USART_DATA_BITS_6 6
#define USART_DATA_BITS_7 7
#define USART_DATA_BITS_8 8
#define USART_PARITY_BIT_NONE 0
#define USART_PARITY_BIT_ODD 1
#define USART_PARITY_BIT_EVEN 2
#define USART_STOP_BITS_1 1
#define USART_STOP_BITS_2 2

//TODO: Add event based reading of the usart port

typedef struct
{
    uint8_t databits;
    uint8_t parityBit;
    uint8_t stoBits;
}usartFrameFormat_t;

void usart_setFrameFormat(usartFrameFormat_t frameFormat);
void usart_begin(uint32_t baud);
void end();
int usart_available();
bool usart_print(const char *msg);
bool usart_println(const char *msg);
void usart_write(uint8_t byte);
uint8_t usart_read();

#endif //EMBEDDED_UTILITY_LIBRARY_USART_H

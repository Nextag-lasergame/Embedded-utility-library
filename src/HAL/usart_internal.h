/*
 * Copyright (c) 2020 Tim Herreijgers
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

#ifndef EMBEDDED_UTILITY_LIBRARY_USART_INTERNAL_H
#define EMBEDDED_UTILITY_LIBRARY_USART_INTERNAL_H

#ifdef __AVR_ATmega328P__

#define USART_BUFFER_SIZE 32
#define USART_BUFFER_INDEX_MAX_VALUE 255

#define USART_BAUD_RATE_REGISTER_L UBRR0L
#define USART_BAUD_RATE_REGISTER_H UBRR0H
#define USART_CONTROL_STATUS_REGISTER_A UCSR0A
#define USART_CONTROL_STATUS_REGISTER_B UCSR0B
#define USART_CONTROL_STATUS_REGISTER_C UCSR0C
#define USART_DATA_REGISTER UDR0

#define USART_DATA_REGISTER_EMPTY UDRE0
#define USART_RECEIVE_COMPLETE RXC0
#define USART_RX_ENABLE RXEN0
#define USART_RX_INTERRUPT_ENABLE RXCIE0
#define USART_TX_ENABLE TXEN0
#define USART_TX_INTERRUPT_ENABLE TXCIE0

#define USART_DATA_BITS_OFFSET 1
#define USART_PARITY_BITS_OFFSET 4
#define USART_STOP_BITS_OFFSET 2

#endif

#endif //EMBEDDED_UTILITY_LIBRARY_USART_INTERNAL_H

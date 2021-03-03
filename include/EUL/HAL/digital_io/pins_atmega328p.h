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

#ifndef EMBEDDED_UTILITY_LIBRARY_PINS_ATMEGA328P_H
#define EMBEDDED_UTILITY_LIBRARY_PINS_ATMEGA328P_H

//Order of registers: PIN DDR PORT BIT

#define DIO_PB0 {0x0023002400250000}
#define DIO_PB1 {0x0023002400250001}
#define DIO_PB2 {0x0023002400250002}
#define DIO_PB3 {0x0023002400250003}
#define DIO_PB4 {0x0023002400250004}
#define DIO_PB5 {0x0023002400250005}
#define DIO_PB6 {0x0023002400250006}
#define DIO_PB7 {0x0023002400250007}

#define DIO_PC0 {0x0026002700280000}
#define DIO_PC1 {0x0026002700280001}
#define DIO_PC2 {0x0026002700280002}
#define DIO_PC3 {0x0026002700280003}
#define DIO_PC4 {0x0026002700280004}
#define DIO_PC5 {0x0026002700280005}
#define DIO_PC6 {0x0026002700280006}

#define DIO_PD0 {0x0029002A002B0000}
#define DIO_PD1 {0x0029002A002B0001}
#define DIO_PD2 {0x0029002A002B0002}
#define DIO_PD3 {0x0029002A002B0003}
#define DIO_PD4 {0x0029002A002B0004}
#define DIO_PD5 {0x0029002A002B0005}
#define DIO_PD6 {0x0029002A002B0006}
#define DIO_PD7 {0x0029002A002B0007}

#endif //EMBEDDED_UTILITY_LIBRARY_PINS_ATMEGA328P_H

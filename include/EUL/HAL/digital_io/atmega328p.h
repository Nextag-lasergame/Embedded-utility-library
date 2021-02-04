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

#ifndef EMBEDDED_UTILITY_LIBRARY_ATMEGA328P_H
#define EMBEDDED_UTILITY_LIBRARY_ATMEGA328P_H

//Order of registers: PIN DDR PORT BIT

#define DIO_PB0 {0x03040500}
#define DIO_PB1 {0x03040501}
#define DIO_PB2 {0x03040502}
#define DIO_PB3 {0x03040503}
#define DIO_PB4 {0x03040504}
#define DIO_PB5 {0x03040505}
#define DIO_PB6 {0x03040506}
#define DIO_PB7 {0x03040507}

#define DIO_PC0 {0x06070800}
#define DIO_PC1 {0x06070801}
#define DIO_PC2 {0x06070802}
#define DIO_PC3 {0x06070803}
#define DIO_PC4 {0x06070804}
#define DIO_PC5 {0x06070805}
#define DIO_PC6 {0x06070806}

#define DIO_PD0 {0x090A0B00}
#define DIO_PD1 {0x090A0B01}
#define DIO_PD2 {0x090A0B02}
#define DIO_PD3 {0x090A0B03}
#define DIO_PD4 {0x090A0B04}
#define DIO_PD5 {0x090A0B05}
#define DIO_PD6 {0x090A0B06}
#define DIO_PD7 {0x090A0B07}

#endif //EMBEDDED_UTILITY_LIBRARY_ATMEGA328P_H

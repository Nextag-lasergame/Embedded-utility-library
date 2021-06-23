
/*
 * Copyright (c) 2020-2021 Tim Herreijgers
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

#ifndef EMBEDDED_UTILITY_LIBRARY_PINS_ATTINY45_H
#define EMBEDDED_UTILITY_LIBRARY_PINS_ATTINY45_H

#define DIO_PB0 {0x0016001700180000}
#define DIO_PB1 {0x0016001700180001}
#define DIO_PB2 {0x0016001700180002}
//#define DIO_PB3 {PIN_SHIFT(0x0016) | DDR_SHIFT(0x0017) | PORT_SHIFT(0x0018) | BIT_SHIFT(0x0003) }
#define DIO_PB3 {0x0016001700180003}
#define DIO_PB4 {0x0016001700180004}
#define DIO_PB5 {0x0016001700180005}

#endif //EMBEDDED_UTILITY_LIBRARY_PINS_ATTINY45_H


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

#define DIO_PB0 {(PIN_SHIFT(0x36) | DDR_SHIFT(0x37) | PORT_SHIFT(0x38) | BIT_SHIFT(0x00) )}
#define DIO_PB1 {(PIN_SHIFT(0x36) | DDR_SHIFT(0x37) | PORT_SHIFT(0x38) | BIT_SHIFT(0x01) )}
#define DIO_PB2 {(PIN_SHIFT(0x36) | DDR_SHIFT(0x37) | PORT_SHIFT(0x38) | BIT_SHIFT(0x02) )}
#define DIO_PB3 {(PIN_SHIFT(0x36) | DDR_SHIFT(0x37) | PORT_SHIFT(0x38) | BIT_SHIFT(0x03) )}
#define DIO_PB4 {(PIN_SHIFT(0x36) | DDR_SHIFT(0x37) | PORT_SHIFT(0x38) | BIT_SHIFT(0x04) )}
#define DIO_PB5 {(PIN_SHIFT(0x36) | DDR_SHIFT(0x37) | PORT_SHIFT(0x38) | BIT_SHIFT(0x05) )}

#endif //EMBEDDED_UTILITY_LIBRARY_PINS_ATTINY45_H

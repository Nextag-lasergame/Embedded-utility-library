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

#ifndef EMBEDDED_UTILITY_LIBRARY_TWI_H
#define EMBEDDED_UTILITY_LIBRARY_TWI_H

#ifdef __cplusplus
extern "C" {
#endif

#include <inttypes.h>

//TODO: Add errorcallback

extern void twi_begin();
extern void twi_setAddress(uint8_t address);
extern void twi_sendTo(uint8_t address, uint8_t *data, uint8_t amount);
extern void twi_requestFrom(uint8_t address, uint8_t amount);

extern void twi_onReceive(void (*)(uint8_t *, uint8_t));
extern void twi_onRequest(void (*)(void));
extern void twi_requestReply(uint8_t *data, uint8_t amount);

#ifdef __cplusplus
}
#endif

#endif //EMBEDDED_UTILITY_LIBRARY_TWI_H

#ifndef __TWI_H__
#define __TWI_H__

#include <inttypes.h>

//TODO: Add errorcallback

extern void twi_begin();
extern void twi_setAddress(uint8_t address);
extern void twi_sendTo(uint8_t address, uint8_t* data, uint8_t amount);
extern void twi_requestFrom(uint8_t address, uint8_t amount);

extern void twi_onReceive(void (*)(uint8_t*, uint8_t));
extern void twi_onRequest(void (*)(void));
extern void twi_requestReply(uint8_t *data, uint8_t amount);

#endif
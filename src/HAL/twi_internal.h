#include "../../../../.platformio/packages/toolchain-atmelavr/avr/include/inttypes.h"

#ifdef __AVR_ATmega328P__

#ifndef TWI_FREQ
#define TWI_FREQ 100000L
#endif

#define TWI_DATA_REGISTER TWDR
#define TWI_BIT_RATE_REGISTER TWBR
#define TWI_ADDRESS_REGISTER TWAR
#define TWI_STATUS_REGISTER TWSR
#define TWI_CONTROL_REGISTER TWCR

#define TWI_STATUS_REGISTER_STATUS_MASK 0xF8

// Start condition transmitted
#define TW_START		0x08

// repeated start condition transmitted
#define TW_REP_START		0x10

// SLA+W transmitted, ACK received
#define TW_MT_SLA_ACK		0x18

// SLA+W transmitted, NACK received
#define TW_MT_SLA_NACK		0x20

// data transmitted, ACK received */
#define TW_MT_DATA_ACK		0x28

// data transmitted, NACK received */
#define TW_MT_DATA_NACK		0x30

// arbitration lost in SLA+W or data */
#define TW_MT_ARB_LOST		0x38

// arbitration lost in SLA+R or NACK */
#define TW_MR_ARB_LOST		0x38

// SLA+R transmitted, ACK received */
#define TW_MR_SLA_ACK		0x40

// SLA+R transmitted, NACK received */
#define TW_MR_SLA_NACK		0x48

// data received, ACK returned */
#define TW_MR_DATA_ACK		0x50

// data received, NACK returned */
#define TW_MR_DATA_NACK		0x58

// SLA+R received, ACK returned */
#define TW_ST_SLA_ACK		0xA8

// arbitration lost in SLA+RW, SLA+R received, ACK returned */
#define TW_ST_ARB_LOST_SLA_ACK	0xB0

// data transmitted, ACK received */
#define TW_ST_DATA_ACK		0xB8

// data transmitted, NACK received */
#define TW_ST_DATA_NACK		0xC0

// last data byte transmitted, ACK received */
#define TW_ST_LAST_DATA		0xC8

// SLA+W received, ACK returned */
#define TW_SR_SLA_ACK		0x60

// arbitration lost in SLA+RW, SLA+W received, ACK returned */
#define TW_SR_ARB_LOST_SLA_ACK	0x68

// general call received, ACK returned */
#define TW_SR_GCALL_ACK		0x70

// arbitration lost in SLA+RW, general call received, ACK returned */
#define TW_SR_ARB_LOST_GCALL_ACK 0x78

// data received, ACK returned */
#define TW_SR_DATA_ACK		0x80

// data received, NACK returned */
#define TW_SR_DATA_NACK		0x88

// general call data received, ACK returned */
#define TW_SR_GCALL_DATA_ACK	0x90

// general call data received, NACK returned */
#define TW_SR_GCALL_DATA_NACK	0x98

// stop or repeated start condition received while selected */
#define TW_SR_STOP		0xA0

#define TWI_READY 0
#define TWI_MTX 1
#define TWI_MRX 2
#define TWI_STX 3
#define TWI_SRX 4

#endif
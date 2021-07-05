/*
 * msg_v3_uint16.h
 *
 *  Created on: Jul 1, 2021
 *      Author: Daniel Soto Guerrero
 */

#ifndef MSG_V3_UINT16_H_
#define MSG_V3_UINT16_H_

#include <header.h>

typedef struct V3_UINT16{
	uinteger16_t e1;
	uinteger16_t e2;
	uinteger16_t e3;
}V3_UINT16;

typedef struct msg_3v_uint16{
	HEADER header;
	V3_UINT16 payload;
	uint8_t checksum;
}msg_3v_uint16;


#define _MSG_3V_UINT16(x) \
	x.header.start = START_MSG; \
	x.header.n_payload = 0x07; \
	x.header.sequence.value = 0x0000; \
	x.header.id_emitter = 0x00; \
	x.header.id_composant = NO_ID; \
	x.header.type = V3_uINT16; \
	x.payload.e1.value=0x0000; \
	x.payload.e2.value=0x0000; \
	x.payload.e3.value=0x0000;

#define _MSG_3V_UINT16_CHECKSUM(x)\
	x.checksum = _CHECKSUM_HDR(x.header) ^ _CHECKSUM_INT16(x.payload.e1) ^ _CHECKSUM_INT16(x.payload.e2) ^ _CHECKSUM_INT16(x.payload.e3)

#endif /* MSG_V3_UINT16_H_ */
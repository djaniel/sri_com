/*
 * msg_v3_int8.h
 *
 *  Created on: Jul 1, 2021
 *      Author: Daniel Soto Guerrero
 */

#ifndef MSG_V2_INT8_H_
#define MSG_V2_INT8_H_

#include <header.h>

typedef struct V2_INT8{
	uint8_t e1;
	uint8_t e2;
}V2_INT8;

typedef struct msg_v2_int8{
	HEADER header;
	V2_INT8 payload;
	uint8_t checksum;
}msg_v2_int8;


#define _MSG_V2_INT8(x) \
	x.header.start = START_MSG; \
	x.header.n_payload = 0x02; \
	x.header.sequence = 0x00; \
	x.header.id_emitter = 0x00; \
	x.header.type = t_V2INT8; \
	x.payload.e1=0x00; \
	x.payload.e2=0x00;

#define _MSG_V2_INT8_SERIALIZE(x) \
	{x.header.start, \
	x.header.n_payload, \
	x.header.sequence, \
	x.header.id_emitter, \
	x.header.type, \
	x.payload.e1, \
	x.payload.e2, \
    x.checksum}

#define _MSG_V2_INT8_CHECKSUM(x)\
	x.checksum = _CHECKSUM_HDR(x.header) ^ x.payload.e1 ^ x.payload.e2

#endif /* MSG_V2_INT8_H_ */

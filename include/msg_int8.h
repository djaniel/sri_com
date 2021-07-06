/*
 * msg_int8.h
 *
 *  Created on: Jul 1, 2021
 *      Author: Daniel Soto Guerrero
 */

#ifndef MSG_INT8_H_
#define MSG_INT8_H_

#include <header.h>

typedef struct INT8{
	int8_t e1;
}INT8;

typedef struct msg_int8{
	HEADER header;
	INT8 payload;
	uint8_t checksum;
}msg_int8;


#define _MSG_INT8(x) \
	x.header.start = START_MSG; \
	x.header.n_payload = 0x01; \
	x.header.sequence = 0x00; \
	x.header.id_emitter = 0x00; \
	x.header.type = t_INT8; \
	x.payload.e1=0x00;

#define _MSG_INT8_SERIALIZE(x) \
	{x.header.start, \
	x.header.n_payload, \
	x.header.sequence, \
	x.header.id_emitter, \
	x.header.type, \
	x.payload.e1,\
	x.checksum}

#define _MSG_INT8_CHECKSUM(x)\
	x.checksum = _CHECKSUM_HDR(x.header) ^ x.payload.e1

#endif /* MSG_INT8_H_ */

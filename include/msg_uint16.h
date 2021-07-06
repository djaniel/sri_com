/*
 * msg_uint16.h
 *
 *  Created on: Jul 1, 2021
 *      Author: Daniel Soto Guerrero
 */

#ifndef MSG_UINT16_H_
#define MSG_UINT16_H_

#include <header.h>

typedef struct UINT16{
	uinteger16_t e1;
}UINT16;

typedef struct msg_uint16{
	HEADER header;
	UINT16 payload;
	uint8_t checksum;
}msg_uint16;


#define _MSG_UINT16(x) \
	x.header.start = START_MSG; \
	x.header.n_payload = 0x02; \
	x.header.sequence = 0x00; \
	x.header.id_emitter = 0x00; \
	x.header.type = t_uINT16; \
	x.payload.e1.value=0x0000;

#define _MSG_UINT16_SERIALIZE(x) \
	{x.header.start, \
	x.header.n_payload, \
	x.header.sequence, \
	x.header.id_emitter, \
	x.header.type, \
	x.payload.e1.bytes[0], \
	x.payload.e1.bytes[1]}

#define _MSG_UINT16_CHECKSUM(x)\
	x.checksum = _CHECKSUM_HDR(x.header) ^ _CHECKSUM_INT16(x.payload.e1)

#endif /* MSG_UINT16_H_ */

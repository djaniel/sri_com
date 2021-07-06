/*
 * msg_uint8.h
 *
 *  Created on: Jul 1, 2021
 *      Author: Daniel Soto Guerrero
 */

#ifndef MSG_UINT8_H_
#define MSG_UINT8_H_

#include <header.h>

typedef struct UINT8{
	uint8_t e1;
}UINT8;

typedef struct msg_uint8{
	HEADER header;
	UINT8 payload;
	uint8_t checksum;
}msg_uint8;


#define _MSG_UINT8(x) \
	x.header.start = START_MSG; \
	x.header.n_payload = 0x01; \
	x.header.sequence = 0x00; \
	x.header.id_emitter = 0x00; \
	x.header.type = t_uINT8; \
	x.payload.e1=0x00;

#define _MSG_UINT8_CHECKSUM(x)\
	x.checksum = _CHECKSUM_HDR(x.header) ^ x.payload.e1

#endif /* MSG_UINT8_H_ */

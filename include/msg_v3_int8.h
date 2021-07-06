/*
 * msg_v3_int8.h
 *
 *  Created on: Jul 1, 2021
 *      Author: Daniel Soto Guerrero
 */

#ifndef MSG_V3_INT8_H_
#define MSG_V3_INT8_H_

#include <header.h>

typedef struct V3_INT8{
	int8_t e1;
	int8_t e2;
	int8_t e3;
}V3_INT8;

typedef struct msg_3v_int8{
	HEADER header;
	V3_INT8 payload;
	uint8_t checksum;
}msg_3v_int8;


#define _MSG_3V_INT8(x) \
	x.header.start = START_MSG; \
	x.header.n_payload = 0x03; \
	x.header.sequence = 0x00; \
	x.header.id_emitter = 0x00; \
	x.header.type = t_V3INT8; \
	x.payload.e1=0x00; \
	x.payload.e2=0x00; \
	x.payload.e3=0x00;

#define _SRI_MSG_SEND_3V_INT8(x) \
	PRINT_SERIAL_FCN(x.header.start); \
	PRINT_SERIAL_FCN(x.header.n_payload); \
	PRINT_SERIAL_FCN(x.header.sequence); \
	PRINT_SERIAL_FCN(x.header.id_emitter); \
	PRINT_SERIAL_FCN(x.header.type); \
	PRINT_SERIAL_FCN(x.payload.e1); \
	PRINT_SERIAL_FCN(x.payload.e2); \
	PRINT_SERIAL_FCN(x.payload.e3);

#define _MSG_3V_INT8_CHECKSUM(x)\
	x.checksum = _CHECKSUM_HDR(x.header) ^ x.payload.e1 ^ x.payload.e2 ^ x.payload.e3

#endif /* MSG_V3_INT8_H_ */

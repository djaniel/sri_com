/*
 * msg_v3_int16.h
 *
 *  Created on: Jul 1, 2021
 *      Author: Daniel Soto Guerrero
 */

#ifndef MSG_V3_INT16_H_
#define MSG_V3_INT16_H_

#include <header.h>

typedef struct V3_sINT16{
	integer16_t e1;
	integer16_t e2;
	integer16_t e3;
}V3_sINT16;

typedef struct msg_3v_int16{
	HEADER header;
	V3_sINT16 payload;
	uint8_t checksum;
}msg_3v_int16;


#define _MSG_3V_INT16(x) \
	x.header.start = START_MSG; \
	x.header.n_payload = 0x06; \
	x.header.sequence = 0x00; \
	x.header.id_emitter = 0x00; \
	x.header.type = t_V3INT16; \
	x.payload.e1.value=0x0000; \
	x.payload.e2.value=0x0000; \
	x.payload.e3.value=0x0000;

#define _SRI_MSG_SEND_3V_INT16(x) \
	PRINT_SERIAL_FCN(x.header.start); \
	PRINT_SERIAL_FCN(x.header.n_payload); \
	PRINT_SERIAL_FCN(x.header.sequence); \
	PRINT_SERIAL_FCN(x.header.id_emitter); \
	PRINT_SERIAL_FCN(x.header.type); \
	PRINT_SERIAL_FCN(x.payload.e1.bytes[0]); \
	PRINT_SERIAL_FCN(x.payload.e1.bytes[1]); \
	PRINT_SERIAL_FCN(x.payload.e2.bytes[0]); \
	PRINT_SERIAL_FCN(x.payload.e2.bytes[1]); \
	PRINT_SERIAL_FCN(x.payload.e3.bytes[0]); \
	PRINT_SERIAL_FCN(x.payload.e3.bytes[1]);

#define _MSG_3V_INT16_CHECKSUM(x)\
	x.checksum = _CHECKSUM_HDR(x.header) ^ _CHECKSUM_INT16(x.payload.e1) ^ _CHECKSUM_INT16(x.payload.e2) ^ _CHECKSUM_INT16(x.payload.e3)

#endif /* MSG_V3_INT16_H_ */

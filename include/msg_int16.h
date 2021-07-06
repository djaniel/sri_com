/*
 * msg_int16.h
 *
 *  Created on: Jul 1, 2021
 *      Author: Daniel Soto Guerrero
 */

#ifndef MSG_INT16_H_
#define MSG_INT16_H_

#include <header.h>

typedef struct sINT16{
	integer16_t e1;
}sINT16;

typedef struct msg_int16{
	HEADER header;
	sINT16 payload;
	uint8_t checksum;
}msg_int16;


#define _MSG_INT16(x) \
	x.header.start = START_MSG; \
	x.header.n_payload = 0x02; \
	x.header.sequence = 0x00; \
	x.header.id_emitter = 0x00; \
	x.header.type = t_INT16; \
	x.payload.e1.value=0x0000;

#define _SRI_MSG_SEND_INT16(x) \
	PRINT_SERIAL_FCN(x.header.start); \
	PRINT_SERIAL_FCN(x.header.n_payload); \
	PRINT_SERIAL_FCN(x.header.sequence); \
	PRINT_SERIAL_FCN(x.header.id_emitter); \
	PRINT_SERIAL_FCN(x.header.type); \
	PRINT_SERIAL_FCN(x.payload.e1.bytes[0]); \
	PRINT_SERIAL_FCN(x.payload.e1.bytes[1]);

#define _MSG_INT16_CHECKSUM(x)\
	x.checksum = _CHECKSUM_HDR(x.header) ^ _CHECKSUM_INT16(x.payload.e1)

#endif /* MSG_INT16_H_ */

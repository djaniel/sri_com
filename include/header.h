/*
 * header.h
 *
 *  Created on: Jul 1, 2021
 *      Author: Daniel Soto Guerrero
 */

#ifndef HEADER_H_
#define HEADER_H_

#include <stdint.h>

#define START_MSG 0xFE

enum type_msg{
	BYTE=0x0,
	V2_BYTE,
	V3_BYTE,
	INT16,
	V2_INT16,
	V3_INT16,
	uINT16,
	V2_uINT16,
	V3_uINT16,
};

enum component{
	NO_ID=0x0,
	HEART_RATE,
	POSITION,
	HYGROMETER,
	ACCELEROMETER
};

typedef union uinteger16_t{
	uint16_t value;
	uint8_t bytes[2];
}uinteger16_t;

typedef union integer16_t{
	int16_t value;
	uint8_t bytes[2];
}integer16_t;

typedef struct HEADER{
	uint8_t start;
	uint8_t n_payload;
	uinteger16_t sequence;
	uint8_t id_emitter;
	uint8_t id_composant;
	uint8_t type;
}HEADER;

#define _CHECKSUM_INT16(x) x.bytes[0] ^ x.bytes[1]

#define _CHECKSUM_HDR(x) x.start ^ x.n_payload ^ _CHECKSUM_INT16(x.sequence) ^ x.id_emitter ^ x.id_composant ^ x.type

#endif /* HEADER_H_ */

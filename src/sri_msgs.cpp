//============================================================================
// Name        : sri_msgs.cpp
// Author      : Daniel Soto-Guerrero
// Version     : 0.1
// Copyright   : Use at you own risk
// Description : SRI messages C++, Ansi-style
//============================================================================

#include <iostream>
#include <sri_com.h>
#include <stdio.h>
#define PRINT_SERIAL_FCN(x) printf("%x",x)

using namespace std;


// loraweb.unilim.fr
// arduino, raspberry pi


int main() {
	msg_v3_uint16 msg;

	_MSG_V3_UINT16( msg );

	msg.payload.e1.value = 0x2401;
	msg.payload.e2.value = 0x2003;
	msg.payload.e3.value = 0xF005;

	_MSG_V3_UINT16_CHECKSUM( msg );


	cout << "start:    " << static_cast<unsigned>( msg.header.start )<< endl;
	cout << "n_payoad: " << static_cast<unsigned>( msg.header.n_payload) << endl;
	cout << "sequence: " << static_cast<unsigned>( msg.header.sequence )<< endl;
	cout << "emitter:  " << static_cast<unsigned>( msg.header.id_emitter)  << endl;
	cout << "type:  " << static_cast<unsigned>( msg.header.type )<< endl;
	cout << "e1:  " << hex << msg.payload.e1.value  ;
	cout << ", e2:  " << msg.payload.e2.value ;
	cout << ", e3:  " << msg.payload.e3.value << endl;

	msg_v3_int8 msg2;

	_MSG_V3_UINT8(msg2);

	msg2.payload.e1 = 0x02;
	msg2.payload.e2 = 0x03;
	msg2.payload.e3 = 0x04;

	uint8_t datas[] = _MSG_V3_UINT16_SERIALIZE(msg);


	return 0;
}

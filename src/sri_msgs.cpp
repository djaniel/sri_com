//============================================================================
// Name        : sri_msgs.cpp
// Author      : Daniel Soto-Guerrero
// Version     : 0.1
// Copyright   : Use at you own risk
// Description : SRI messages C++, Ansi-style
//============================================================================

#include <iostream>
#include <sri_com.h>
#define PRINT_SERIAL_FCN printf

using namespace std;

int main() {
	msg_3v_uint16 msg;

	_MSG_3V_UINT16( msg );

	msg.payload.e1.value = 0x2401;
	msg.payload.e2.value = 0x2003;
	msg.payload.e3.value = 0xF005;

	_MSG_3V_UINT16_CHECKSUM( msg );

	cout << "start:    " << static_cast<unsigned>( msg.header.start )<< endl;
	cout << "n_payoad: " << static_cast<unsigned>( msg.header.n_payload) << endl;
	cout << "sequence: " << static_cast<unsigned>( msg.header.sequence.value )<< endl;
	cout << "emitter:  " << static_cast<unsigned>( msg.header.id_emitter)  << endl;
	cout << "id_comp:  " << static_cast<unsigned>( msg.header.id_composant) << endl;
	cout << "type:  " << static_cast<unsigned>( msg.header.type )<< endl;
	cout << "e1:  " << hex << msg.payload.e1.value  ;
	cout << ", e2:  " << msg.payload.e2.value ;
	cout << ", e3:  " << msg.payload.e3.value << endl;

	msg_3v_int16 msg2;

	//_SRI_MSG_SEND_3V_UINT16(msg);



	return 0;
}

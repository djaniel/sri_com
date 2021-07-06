
#include <sri_com.h>

void setup() {
  // put your setup code here, to run once:
  msg_3v_uint16 msg;

  _MSG_3V_UINT16( msg );
  msg.payload.e1.value = 0x2401;
  msg.payload.e2.value = 0x2003;
  msg.payload.e3.value = 0xF005;

  _MSG_3V_UINT16_CHECKSUM( msg );

  byte datas[] = _MSG_3V_UINT16_SERIALIZE(msg);

  Serial.write( datas, sizeof(datas));


}

void loop() {
  // put your main code here, to run repeatedly:

}

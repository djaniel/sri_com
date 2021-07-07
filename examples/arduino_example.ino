
#include <sri_com.h>

msg_v3_uint16 msg;

void setup() {
  Serial.begin(9600);

  _MSG_V3_UINT16( msg );

  msg.payload.e1.value = 0x2401;
  msg.payload.e2.value = 0x2003;
  msg.payload.e3.value = 0xF005;

  _MSG_V3_UINT16_CHECKSUM( msg );
}

void loop() {
  byte datas[] = _MSG_V3_UINT16_SERIALIZE(msg);

  Serial.write( datas, sizeof(datas));

  delay(1000);
}

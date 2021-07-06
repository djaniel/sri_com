# sri_com
Serial communication Protocol

A headers-only multiplateform library that implements a serial communication protocol.

# Structure of the frame

| Byte number | Value [Range] | Description |
| :------------- | -----------: | -----------: |
| 0 | 0xFF | Start of frame |
| 1 | [0x0-0xFF] | Payload's length |
| 2 | [0x0-0xFF] | Sequence number |
| 3 | [0x0-0xFF] | Emitter identity |
| 4 | [0x0-0xFF] | Type of message |
| 5 to (n+5) | [0x0-0xFF] | Payload |
| (n+6) | [0x0-0xFF] | Checksum, one octet |
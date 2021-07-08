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
| (n+6) | [0x0-0xFF] | Checksum, one byte |

### Start frame 
Always 0xFF, it defines the start byte of the frame.
### Paylod's length
The number of bytes stored in the payload.
### Sequence number
Application specific, commonly use to detect packet loss.
### Emitter identy
The emitter's unique identity. Hereby only 256 unique identities/emitters are supported.
### Type of message
Depending on the nature of the information, the application can choose from a list of messages with different ranges and precision. See following section.
### Payload
A list of bytes varying in length that represents the information being transmitted. The length of the payload depends on the type of message.
### Checksum
Computed from the XOR of all bytes in the frame. 

# Type of message

Then messages currently supported are:

|Type      |
|:---------|
|t_INT8    |
|t_V2INT8  |
|t_V3INT8  |
|t_uINT8   |
|t_V2uINT8 |
|t_V3uINT8 |
|t_INT16   |
|t_V2INT16 |
|t_V3INT16 |
|t_uINT16  |
|t_V2uINT16|
|t_V3uINT16|


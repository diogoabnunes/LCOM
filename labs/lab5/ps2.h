#ifndef _LCOM_PS2_H
#define _LCOM_PS2_H

#define MOUSE_IRQ 12

#define MOUSE_RESET 0xFF
#define MOUSE_DEFAULT 0xF6
#define MOUSE_DISABLE 0xF5
#define MOUSE_ENABLE 0xF4
#define MOUSE_SET_REMOTE_MODE 0xF0
#define MOUSE_SET_STREAM_MODE 0xEA
#define MOUSE_READ_DATA 0xEB

#define WRITE_MOUSE 0xD4

#define READ_DATA 0xEB

#define MOUSE_YOVF BIT(7) 
#define MOUSE_XOVF BIT(6)
#define MOUSE_YSIGN BIT(5)
#define MOUSE_XSIGN BIT(4)
#define MOUSE_MB BIT(2)
#define MOUSE_RB BIT(1)
#define MOUSE_LB BIT(0)

#define MOUSE_ACK 0xFA
#define MOUSE_NACK 0xFE

#endif

#ifndef _LCOM_I8042_H_
#define _LCOM_I8042_H_

#include <lcom/lcf.h>
#include <stdint.h>

/*
 Constants for programming the i8042 Keyboard.
*/

// Mouse
#define MOUSE_IRQ 12

#define MOUSE_RESET 0xFF
#define MOUSE_DEFAULT 0xF6
#define MOUSE_DISABLE 0xF5
#define MOUSE_ENABLE 0XF4
#define MOUSE_SET_REMOTE_MODE 0xF0
#define MOUSE_SET_STREAM_MODE 0xEA

#define WRITE_MOUSE 0XD4

#define MOUSE_YOVF BIT(7) 
#define MOUSE_XOVF BIT(6)
#define MOUSE_YSIGN BIT(5)
#define MOUSE_XSIGN BIT(4)
#define MOUSE_MB BIT(2)
#define MOUSE_RB BIT(1)
#define MOUSE_LB BIT(0)

#define MOUSE_ACK 0xFA
#define MOUSE_NACK 0xFE
#define MOUSE_ERROR 0xFCs
#define READ_DATA 0xEB

// Keyboard
#define DELAY_US    20000
#define KEYBOARD_IRQ	1

#define ESC_BREAKCODE	0x81

#define STAT_REG 0x64
#define OUT_BUF 0x60

#define FIRST_BYTE_OF_2BYTES	0xE0
#define MAKE_CODE	BIT(7)

#define PARITY_ERROR	BIT(7)
#define TIMEOUT_ERROR	BIT(6)
#define IBF_FULL	BIT(1)
#define OBF_FULL	BIT(0)

#define KBD_DISABLE	0xAD
#define KBD_ENABLE	0xAE

#define KBC_READCMDBYTE 0x20 
#define KBC_WRITECMDBYTE 0x60 

#endif /* _LCOM_I8042_H */


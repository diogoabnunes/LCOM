#ifndef _LCOM_I8042_H_
#define _LCOM_I8042_H_

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

#endif

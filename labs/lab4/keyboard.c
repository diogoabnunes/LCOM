#include "keyboard.h"

int keyboard_ID = 1;
unsigned int sys_counter = 0;
uint8_t scan_code;

int keyboard_subscribe_int(uint8_t *bit_no)
{
	if (bit_no == 0) return 1;
	*bit_no = keyboard_ID;
	if (sys_irqsetpolicy(KEYBOARD_IRQ, IRQ_REENABLE | IRQ_EXCLUSIVE, &keyboard_ID) != 0) return 1;
 	return 0;
}

int keyboard_unsubscribe_int()
{
	if (sys_irqrmpolicy(&keyboard_ID) != 0) return 1;
  	return 0;
}

int sys_inb_count(port_t port, uint32_t *byte)
{
	sys_counter++;
	return sys_inb(port, byte);
}

int util_sys_inb_keyboard(port_t port, uint8_t *byte)
{
	uint32_t aux;
  	int result = sys_inb_count(port, &aux);
  	*byte = (uint8_t)aux;
  	return result;
}

void (kbc_ih)()
{
	uint32_t status_register;
	sys_inb_count(STAT_REG, &status_register);
	if ((status_register & OBF_FULL) == OBF_FULL)
		util_sys_inb_keyboard(OUT_BUF, &scan_code);
	else scan_code = 0xFF;
}

#include "kbc.h"

int sysCounter = 0; 	//Declaring counter for function sys_inb() calls
int kbcID = 1; 		//Declaring identification hook for keyboard configuration
uint8_t scancode;//Declaring scancode


int kbc_subscribe_int(uint8_t *bit_no)
{
	if(bit_no == 0)
    	return 1; //Testing for null pointer

  	*bit_no = kbcID; 

  	if(sys_irqsetpolicy(KEYBOARD_IRQ, IRQ_REENABLE | IRQ_EXCLUSIVE, &kbcID) != 0) {
  		printf("Error subscribing KBC interrupt...\n");
    	return 1; //Returns 1 and prints error upon error in calling function
    }

  	return 0; //Returns 0 upon success
}

int kbc_unsubscribe_int() {
	if(sys_irqrmpolicy(&kbcID) != 0) {
    	printf("Error unsubscribing KBC interrupt...\n");
    	return 1; //Returns 1 and prints error upon error in calling function
	}

  	return 0; //Returns 0 upon success
}

int sys_inb_count(port_t port, uint32_t *byte)
{
	int res = sys_inb(port, byte); //Tests for error
	sysCounter++; //Increments counter everytime the function is called

  	return res; //Returns 0 if successful, 1 otherwise
}

int util_sys_inb_kbc(port_t port, uint8_t *byte)
{
	uint32_t aux; //Temporary variable for calling sys_inb() function

  	if (sys_inb_count(port, &aux) != 0) //Tests for error
    	return 1; //Returns 1 if there's an error

  	(*byte) = (uint8_t) aux; //Cast

  	return 0; //Returns 0 upon success
}

void (kbc_ih)() {

  uint32_t status_reg;

  if (sys_inb_count(STAT_REG, &status_reg) != 0)// Gets status
    return;

  if ((status_reg & OBF_FULL)==OBF_FULL) { // Checks if Out_buffer is full. It needs to be in order to read data from it
    
    if (util_sys_inb_kbc(OUT_BUF, &scancode) != 0) // Retrieve data from output buffer
      return;


    if ((status_reg & (PARITY_ERROR | TIMEOUT_ERROR)) == 0)
      return;
    else
      return; // parity or timeout error
  }
  else {
  	scancode = 0xff;
  }

  return;
}

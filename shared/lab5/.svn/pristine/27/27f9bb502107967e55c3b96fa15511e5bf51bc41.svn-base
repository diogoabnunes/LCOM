#include <lcom/lcf.h>

#include <stdint.h>

int(util_get_LSB)(uint16_t val, uint8_t *lsb) {
  
  if (lsb == 0) 
    return 1; //Testing for null pointer

  *lsb = (uint8_t)val;

  return 0; //If successful
}

int(util_get_MSB)(uint16_t val, uint8_t *msb) {
  
  if (msb == 0)
    return 1; //Testing for null pointer

  val = val >> 8;
  *msb = (uint8_t)val; // Shift: MSB_LSB -> (0000)_MSB

  return 0; //If successful
}

int (util_sys_inb)(int port, uint8_t *value) {

  uint32_t aux;
  int result = sys_inb(port, &aux); //Testing for error

  uint8_t mask = 0xFF;
  *value = (aux & mask); //Using only the least significative byte

  return result;
}

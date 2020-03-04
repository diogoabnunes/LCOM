#include <lcom/lcf.h>

#include <stdint.h>

int(util_get_LSB)(uint16_t val, uint8_t *lsb) {
  if (lsb == 0) return 1;
  *lsb = (uint8_t)val;
  return 0;
}

int(util_get_MSB)(uint16_t val, uint8_t *msb) {
  if (msb == 0) return 1;
  val = val >> 8;
  *msb = (uint8_t)val;
  return 0;
}

int (util_sys_inb)(int port, uint8_t *value) {
  uint32_t aux;
  int result = sys_inb(port, &aux);
  uint8_t mask = 0xFF;
  *value = (aux & mask);
  return result;
}

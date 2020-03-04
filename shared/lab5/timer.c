#include <lcom/lcf.h>
#include <lcom/timer.h>

#include <stdint.h>

#include "i8254.h"

unsigned int interruption_counter = 0;
int timer_ID = 0;

int (timer_set_frequency)(uint8_t timer, uint32_t freq) {
  if (timer < 0 || timer > 2) return 1;
  if (freq < 19 || freq > TIMER_FREQ) return 1;

  uint8_t mask_to_preserve = BIT(3) | BIT(2) | BIT(1) | BIT(0); // 4 lsb
  uint8_t timer_config;
  if (timer_get_conf(timer, &timer_config) != 0) return 1;
  uint8_t control_word = (mask_to_preserve & timer_config) | TIMER_LSB_MSB;

  if (timer == 0) control_word |= TIMER_SEL0;
  else if (timer == 1) control_word |= TIMER_SEL1;
  else if (timer == 2) control_word |= TIMER_SEL2;
  else return 1;
  
  sys_outb(TIMER_CTRL, control_word);
  uint16_t div = (uint16_t)(TIMER_FREQ/freq);

  uint8_t lsb, msb;
  util_get_LSB(div, &lsb);
  util_get_MSB(div, &msb);
  sys_outb(TIMER_0 + timer, lsb);
  sys_outb(TIMER_0 + timer, msb);

  return 0;
}

int (timer_subscribe_int)(uint8_t *bit_no) {
  if (bit_no == 0) return 1;
  *bit_no = timer_ID;
  if (sys_irqsetpolicy(TIMER0_IRQ, IRQ_REENABLE, &timer_ID) != 0) return 1;
  return 0;
}

int (timer_unsubscribe_int)() {
  if (sys_irqrmpolicy(&timer_ID) != 0) return 1;
  return 0;
}

void (timer_int_handler)() {
  interruption_counter++;
}

int (timer_get_conf)(uint8_t timer, uint8_t *st) {
  uint8_t rbc = (TIMER_RB_CMD | TIMER_RB_COUNT_ | TIMER_RB_SEL(timer));
  if (sys_outb(TIMER_CTRL, rbc) != 0) return 1;
  if (util_sys_inb(TIMER_0 + timer, st) != 0) return 1;
  return 0;
}

int (timer_display_conf)(uint8_t timer, uint8_t st,
                        enum timer_status_field field) {
  union timer_status_field_val value;
  
  if (field == tsf_all) value.byte = st;
  else if (field == tsf_initial)
  {
    if ((st & INITIAL_MODE) == LSB) value.in_mode = LSB_only;
    else if ((st & INITIAL_MODE) == MSB) value.in_mode = MSB_only;
    else if ((st & INITIAL_MODE) == LSB_MSB) value.in_mode = MSB_after_LSB;
    else value.in_mode = INVAL_val;
  }
  else if (field == tsf_mode)
  {
    if ((st & COUNT_MODE) == MODE0) value.count_mode = 0;
    else if ((st & COUNT_MODE) == MODE1) value.count_mode = 1;
    else if ((st & COUNT_MODE) == MODE2a || (st & COUNT_MODE) == MODE2b) value.count_mode = 2;
    else if ((st & COUNT_MODE) == MODE3a || (st & COUNT_MODE) == MODE3b) value.count_mode = 3;
    else if ((st & COUNT_MODE) == MODE4) value.count_mode = 4;
    else if ((st & COUNT_MODE) == MODE5) value.count_mode = 5;
  }
  else if (field == tsf_base)
  {
    if ((st & BASE) == BASE_BINARY) value.bcd = false;
    else if ((st & BASE) == BASE_BCD) value.bcd = true;
  }

  if (timer_print_config(timer, field, value) != 0) return 1;
  return 0;
}

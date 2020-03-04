#include <lcom/lcf.h>
#include <lcom/timer.h>

#include <stdint.h>

#include "i8254.h"

//Global variables
int timerID = 1; //ID for subscribing the timer interruption 
unsigned int interruptionCounter = 0; //Counts the amount of interruptions

//Functions:
int (timer_set_frequency)(uint8_t timer, uint32_t freq) {
  
  if (timer < 0 || timer > 2) return 1; //no timer with that value - error;
  if (freq < 19 || freq > TIMER_FREQ) return 1; //not in range

  uint8_t mask = BIT(3) | BIT(2) | BIT(1) | BIT(0); // mask of 4 least-significant bits to write control word to configure Timer 0
  uint8_t timer_conf;
  timer_get_conf(timer, &timer_conf);
  
  uint8_t control_word = (mask & timer_conf) | TIMER_LSB_MSB; //6 LSB's 

  if (timer == 0)
    control_word = control_word | TIMER_SEL0;
  else if (timer == 1)
    control_word = control_word | TIMER_SEL1;
  else if (timer == 2)
    control_word = control_word | TIMER_SEL2;
  else
    return 1;

  sys_outb(TIMER_CTRL, control_word);

  uint16_t div = (uint16_t)(TIMER_FREQ / freq);

  uint8_t lsb, msb;

  util_get_LSB(div, &lsb);
  util_get_MSB(div, &msb);

  sys_outb(TIMER_0 + timer, lsb);
  sys_outb(TIMER_0 + timer, msb);

  return 0;
}

int (timer_subscribe_int)(uint8_t *bit_no) {
    if(bit_no == 0)
      return 1; //Testing for null pointer

    *bit_no = timerID;

    if(sys_irqsetpolicy(TIMER0_IRQ, IRQ_REENABLE, &timerID) != 0) //Subscribing timer interrupt while testing for error
      return 1; //If error subscribing timer interrupt

  return 0;
}

int (timer_unsubscribe_int)() {
  if(sys_irqrmpolicy(&timerID) != 0) //Unsubscribing timer interrupt while testing for error
    return 1; //If error unsubscribing timer interrupt

  return 0;
}

void (timer_int_handler)() {
  interruptionCounter++; //Increments the counter by 1
  interruptionCounter = interruptionCounter % 60; // make sure the value is between 0 and 59 (no doubts if overflow)
}

int (timer_get_conf)(uint8_t timer, uint8_t *st) {

  uint8_t rbc = (TIMER_RB_CMD | TIMER_RB_COUNT_ | TIMER_RB_SEL(timer)); //Readback call configuration
  
   if (sys_outb(TIMER_CTRL, rbc) != 0) //Communicates with the controller and tests for error
  {
    printf("sys_outb error...");
    return 1; //If unsuccessful
  }

  switch(timer) //Calls respective timer
  {
    case TIMER_0: 
      util_sys_inb(TIMER_0, st);
      break;
    case TIMER_1:
      util_sys_inb(TIMER_1, st);
      break;
    case TIMER_2:
      util_sys_inb(TIMER_2, st);
      break;
    case TIMER_CTRL:
      util_sys_inb(TIMER_CTRL, st);
      break;
  }

  uint32_t rbc_st;

  if (sys_inb(TIMER_0 + timer, &rbc_st)) //Communicates with the controller and tests for error
  {
    printf("sys_inb error...");
    return 1; //If unsuccessful
  }

  *st = (uint8_t)rbc_st;

  return 0;
}

int (timer_display_conf)(uint8_t timer, uint8_t st,
                        enum timer_status_field field) {
  
  union timer_status_field_val value;

  // we complicate the task in the next if & else block!

  if (field == tsf_all)
    value.byte = st; //Gets everything
  else if (field == tsf_initial) //Sets initialization mode // some error
  {
    if((st & INIT_MASK) == LSB_MASK)
      value.in_mode = LSB_only;
    else if((st & INIT_MASK) == MSB_MASK)
      value.in_mode = MSB_only;
    else if((st & INIT_MASK) == LSB_MSB_MASK)
      value.in_mode = MSB_after_LSB;
    else
      value.in_mode = INVAL_val;
  }
  else if (field == tsf_mode) //Sets counter mode // some error
  {
    if ((st & MODE_MASK) == MODE0)
      value.count_mode = 0;
    else if ((st & MODE_MASK) == MODE1)
      value.count_mode = 1;
    else if ((st & MODE_MASK) == MODE2_a || (st & MODE_MASK) == MODE2_b)
      value.count_mode = 2;
    else if ((st & MODE_MASK) == MODE3_a || (st & MODE_MASK) == MODE3_b)
      value.count_mode = 3;
    else if ((st & MODE_MASK) == MODE4)
      value.count_mode = 4;
    else if ((st & MODE_MASK) == MODE5)
      value.count_mode = 5;
  }
  else if (field == tsf_base) //Sets base
  {
    if ((st & BASE_MASK) == BASE_BINARY)
      value.bcd = false;
    else if ((st & BASE_MASK) == BASE_BCD)
      value.bcd = true;
  }

  int error = timer_print_config(timer, field, value);
  if (error != 0) //Checks for error
    return error; //If unsuccessful

  return 0; //If Successful
}

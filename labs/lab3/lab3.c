#include <lcom/lcf.h>

#include <lcom/lab3.h>

#include <stdbool.h>
#include <stdint.h>

#include "i8254.h"
#include <lcom/timer.h>
#include "i8042.h"
#include "keyboard.h"

extern uint8_t scan_code;
extern unsigned int sys_counter;

extern unsigned int interruption_counter;

int main(int argc, char *argv[]) {
  // sets the language of LCF messages (can be either EN-US or PT-PT)
  lcf_set_language("EN-US");

  // enables to log function invocations that are being "wrapped" by LCF
  // [comment this out if you don't want/need it]
  lcf_trace_calls("/home/lcom/labs/lab3/trace.txt");

  // enables to save the output of printf function calls on a file
  // [comment this out if you don't want/need it]
  lcf_log_output("/home/lcom/labs/lab3/output.txt");

  // handles control over to LCF
  // [LCF handles command line arguments and invokes the right function]
  if (lcf_start(argc, argv))
    return 1;

  // LCF clean up tasks
  // [must be the last statement before return]
  lcf_cleanup();

  return 0;
}

int(kbd_test_scan)() {
  int ipc_status;
  message msg;
  uint32_t r;

  bool two_bytes = false;
  uint8_t bytes[2];

  uint8_t bit_no;
  if (keyboard_subscribe_int(&bit_no) != 0) return 1;
  uint32_t irq_set = BIT(bit_no);

  while (scan_code != ESC_BREAKCODE)
  {
    if ((r = driver_receive(ANY, &msg, &ipc_status)) != 0)
    {
      printf("driver_receive failed with: %d", r);
      continue;
    }

    if (is_ipc_notify(ipc_status)) { //received notification
      switch (_ENDPOINT_P(msg.m_source)) {
        case HARDWARE: // hardware interrupt notification
          if (msg.m_notify.interrupts & irq_set) { //subscribed interrupt
            kbc_ih();
            
            if (two_bytes == true)
            {
              two_bytes = false;
              bytes[1] = scan_code;
              kbd_print_scancode(((scan_code & MAKE_CODE) == 0), 2, bytes);
            }
            else
            {
              if (scan_code == FIRST_BYTE_OF_2BYTES)
              {
                two_bytes = true;
                bytes[0] = scan_code;
              }
              else
              {
                bytes[0] = scan_code;
                kbd_print_scancode(((scan_code & MAKE_CODE) == 0), 1, bytes);
              }
            }
          }
          break;
        default:
          break; //no other notifications expected: do nothing
      }
    }
  }

  if (keyboard_unsubscribe_int() != 0) return 1;
  kbd_print_no_sysinb(sys_counter);
  return 0;
}

int(kbd_test_poll)() {
  bool two_bytes = false;
  uint8_t bytes[2]; 

  while (scan_code != ESC_BREAKCODE)
  {
    tickdelay(micros_to_ticks(DELAY_US));
    kbc_ih();

    if (scan_code == 0xFF) continue;
    if (two_bytes == true)
    {
      two_bytes = false;
      bytes[1] = scan_code;
      kbd_print_scancode(((scan_code & MAKE_CODE) == 0), 2, bytes);
    }
    else
    {
      if (scan_code == FIRST_BYTE_OF_2BYTES)
      {
        two_bytes = true;
        bytes[0] = scan_code;
      }
      else
      {
        bytes[0] = scan_code;
        kbd_print_scancode(((scan_code & MAKE_CODE) == 0), 1, bytes);
      }
    }
  }

  kbd_print_no_sysinb(sys_counter);
  return 0; 
}

int(kbd_test_timed_scan)(uint8_t n) {
  int ipc_status;
  message msg;
  uint32_t r;
  unsigned int counter = 0;

  bool two_bytes = false;
  uint8_t bytes[2];

  uint8_t bit_no_timer, bit_no_keyboard;
  if (timer_subscribe_int(&bit_no_timer) != 0) return 1;
  if (keyboard_subscribe_int(&bit_no_keyboard) != 0) return 1;
  uint32_t irq_set_timer = BIT(bit_no_timer);
  uint32_t irq_set_keyboard = BIT(bit_no_keyboard);

  while (scan_code != ESC_BREAKCODE && counter < n)
  {
    if ((r = driver_receive(ANY, &msg, &ipc_status)) != 0)
    {
      printf("driver_receive failed with: %d", r);
      continue;
    }

    if (is_ipc_notify(ipc_status)) { //received notification
      switch (_ENDPOINT_P(msg.m_source)) {
        case HARDWARE: // hardware interrupt notification
          if (msg.m_notify.interrupts & irq_set_keyboard) { //subscribed interrupt
            kbc_ih();
            interruption_counter = 0;
            counter = 0;
            
            if (two_bytes == true)
            {
              two_bytes = false;
              bytes[1] = scan_code;
              kbd_print_scancode(((scan_code & MAKE_CODE) == 0), 2, bytes);
            }
            else
            {
              if (scan_code == FIRST_BYTE_OF_2BYTES)
              {
                two_bytes = true;
                bytes[0] = scan_code;
              }
              else
              {
                bytes[0] = scan_code;
                kbd_print_scancode(((scan_code & MAKE_CODE) == 0), 1, bytes);
              }
            }
          }
          if (msg.m_notify.interrupts & irq_set_timer) {
            timer_int_handler();

            if (interruption_counter % 60 == 0)
            {
              counter++;
              timer_print_elapsed_time();
            }
          }
          break;
        default:
          break; //no other notifications expected: do nothing
      }
    }
  }

  if (keyboard_unsubscribe_int() != 0) return 1;
  if (timer_unsubscribe_int() != 0) return 1;
  return 0;
}

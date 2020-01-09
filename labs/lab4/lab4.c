// IMPORTANT: you must include the following line in all your C files
#include <lcom/lcf.h>

#include <stdint.h>
#include <stdio.h>

// Any header files included below this line should have been created by you
#include "mouse.h"
#include "i8042.h"
#include "ps2.h"

extern uint16_t packet[3];
extern unsigned int packet_counter;
extern struct packet pp;
extern uint32_t status;
extern unsigned int interruption_counter;

int main(int argc, char *argv[]) {
  // sets the language of LCF messages (can be either EN-US or PT-PT)
  lcf_set_language("EN-US");

  // enables to log function invocations that are being "wrapped" by LCF
  // [comment this out if you don't want/need/ it]
  lcf_trace_calls("/home/lcom/labs/lab4/trace.txt");

  // enables to save the output of printf function calls on a file
  // [comment this out if you don't want/need it]
  lcf_log_output("/home/lcom/labs/lab4/output.txt");

  // handles control over to LCF
  // [LCF handles command line arguments and invokes the right function]
  if (lcf_start(argc, argv))
    return 1;

  // LCF clean up tasks
  // [must be the last statement before return]
  lcf_cleanup();

  return 0;
}


int (mouse_test_packet)(uint32_t cnt) {

  write_mouse(MOUSE_ENABLE); // mouse_enable_data_reporting()

  int ipc_status;
  message msg;
  uint32_t r;
  int pos = 1;  

  uint8_t bit_no;
  if (mouse_subscribe_int(&bit_no) != 0) return 1;
  uint32_t irq_set = BIT(bit_no);

  while (packet_counter < cnt) {
    if ((r = driver_receive(ANY,&msg,&ipc_status)) != 0) {
      printf("driver_receive failed wih: %d", r);
      continue;
    }
    if (is_ipc_notify(ipc_status)) { 
      switch(_ENDPOINT_P(msg.m_source)) {
        case HARDWARE:
          if (msg.m_notify.interrupts & irq_set) {
            mouse_ih();

            if (pos == 1)
            {
              if(status & BIT(3))
              {
                packet[0] = status;
                pos++;
              }
            }
            else if (pos == 2)
            {
              packet[1] = status;
              pos++;
            }
            else if (pos == 3)
            {
              packet[2] = status;
              packet_create();
              mouse_print_packet(&pp);

              packet_counter += 1;
              pos = 1;
            }

          }
          break;
        default:
          break;
      }
    }
  }

  if (mouse_unsubscribe_int() != 0) return 1;

  write_mouse(MOUSE_DISABLE);

  return 0;  
}

int (mouse_test_remote)(uint16_t period, uint8_t cnt) {
    
  write_mouse(MOUSE_DISABLE);
  write_mouse(MOUSE_SET_REMOTE_MODE);

  int pos = 1;

  while(packet_counter < cnt)
  {
    mouse_ih();
    write_mouse(READ_DATA);

    if (pos == 1)
    {
      if(status & BIT(3))
      {

        packet[0] = status;
        pos++;
      }
    }
    else if (pos == 2)
    {
      packet[1] = status;
      pos++;
    }
    else if (pos == 3)
    {
      packet[2] = status;
      packet_create();
      mouse_print_packet(&pp);

      packet_counter += 1;
      pos = 1;
      tickdelay(micros_to_ticks(period*1000));
    }
  }
  write_mouse(MOUSE_SET_STREAM_MODE);
  write_mouse(MOUSE_DISABLE);
  write_command_byte(minix_get_dflt_kbc_cmd_byte());

  return 0;
}

int (mouse_test_async)(uint8_t idle_time) {
  
  write_mouse(MOUSE_ENABLE); // mouse_enable_data_reporting()

  int ipc_status;
  message msg;
  uint32_t r;
  int pos = 1;  

  uint8_t bit_no_mouse, bit_no_timer;
  if (mouse_subscribe_int(&bit_no_mouse) != 0) return 1;
  if (timer_subscribe_int(&bit_no_timer) != 0) return 1;
  uint32_t irq_set_mouse = BIT(bit_no_mouse);
  uint32_t irq_set_timer = BIT(bit_no_timer);

  while (interruption_counter < idle_time * sys_hz()) {
    if ((r = driver_receive(ANY,&msg,&ipc_status)) != 0) {
      printf("driver_receive failed wih: %d", r);
      continue;
    }
    if (is_ipc_notify(ipc_status)) { /* received notification */
      switch(_ENDPOINT_P(msg.m_source)) {
        case HARDWARE:
          if (msg.m_notify.interrupts & irq_set_timer) {
            timer_int_handler();
          }

          if (msg.m_notify.interrupts & irq_set_mouse) {
            mouse_ih();
            interruption_counter = 0;

            if (pos == 1)
            {
              if(status & BIT(3))
              {
                packet[0] = status;
                pos++;
              }
            }
            else if (pos == 2)
            {
              packet[1] = status;
              pos++;
            }
            else if (pos == 3)
            {
              packet[2] = status;
              packet_create();
              mouse_print_packet(&pp);

              packet_counter += 1;
              pos = 1;
            }

          }
          break;
        default:
          break;
      }
    }
  }

  if (timer_unsubscribe_int() != 0) return 1;
  if (mouse_unsubscribe_int() != 0) return 1;

  write_mouse(MOUSE_DISABLE);

  return 0;  
}

int (mouse_test_gesture)(uint8_t x_len, uint8_t tolerance) {
  
  write_mouse(MOUSE_ENABLE);
  
  int ipc_status;
  message msg;
  state_machine_t st_machine;
  st_machine.currentState = INITIAL_STATE;
  struct mouse_ev event;
  uint32_t r;    
  uint8_t bit_no;

  if (mouse_subscribe_int(&bit_no) != 0) return 1;
  uint32_t irq_set = BIT(bit_no);

  int pos = 1;
  int exit = 0;

  while (exit == 0) { /* You may want to use a different condition */
    if ((r = driver_receive(ANY, &msg, &ipc_status)) != 0) {
      printf("driver_receive failed with: %d", r);
      continue;
    }
    if (is_ipc_notify(ipc_status)) { /* received notification */
      switch (_ENDPOINT_P(msg.m_source)) {
      case HARDWARE: /* hardware interrupt notification */
        if (msg.m_notify.interrupts & irq_set) { /* subscribed interrupt */
          
          mouse_ih();
          if (pos == 1)
            {
              if(status & BIT(3))
              {
                packet[0] = status;
                pos++;
              }
            }
            else if (pos == 2)
            {
              packet[1] = status;
              pos++;
            }
            else if (pos == 3)
            {
              packet[2] = status;
              packet_create();
              mouse_print_packet(&pp);

              if(check_gesture(x_len, tolerance, &st_machine, event) == 0)
                exit = 1;

              pos = 1;
            }
        }
        break;
      default:
        break; /* no other notifications expected: do nothing */
      }
    }
  }

  if(mouse_unsubscribe_int() != 0) return 1;

  write_mouse(MOUSE_DISABLE);

  return 0;
}

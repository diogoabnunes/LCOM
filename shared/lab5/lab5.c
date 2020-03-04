// IMPORTANT: you must include the following line in all your C files
#include <lcom/lcf.h>

#include <lcom/lab5.h>

#include <stdint.h>
#include <stdio.h>

// Any header files included below this line should have been created by you
#include "keyboard.h"
#include "video.h"
#include "vbe.h"

extern uint8_t scan_code;
extern int keyboard_ID;
extern unsigned int interruption_counter;

int main(int argc, char *argv[]) {
  // sets the language of LCF messages (can be either EN-US or PT-PT)
  lcf_set_language("EN-US");

  // enables to log function invocations that are being "wrapped" by LCF
  // [comment this out if you don't want/need it]
  lcf_trace_calls("/home/lcom/labs/lab5/trace.txt");

  // enables to save the output of printf function calls on a file
  // [comment this out if you don't want/need it]
  lcf_log_output("/home/lcom/labs/lab5/output.txt");

  // handles control over to LCF
  // [LCF handles command line arguments and invokes the right function]
  if (lcf_start(argc, argv))
    return 1;

  // LCF clean up tasks
  // [must be the last statement before return]
  lcf_cleanup();

  return 0;
}

int(video_test_init)(uint16_t mode, uint8_t delay) {
  
  if (set_graphics_mode(mode) != 0) return 1;
  
  sleep(delay);
  
  if (vg_exit() != 0) return 1;
  return 0;
}

int(video_test_rectangle)(uint16_t mode, uint16_t x, uint16_t y,
                          uint16_t width, uint16_t height, uint32_t color) {
  
  if (vg_init(mode) == NULL)
  {
    vg_exit();
    return 1;
  }

  if (vg_draw_rectangle(x, y, width, height, color) != 0)
  {
    vg_exit();
    return 1;
  }

  int ipc_status;
  message msg;
  uint32_t r;

  uint8_t bit_no;
  if((keyboard_subscribe_int(&bit_no)) != 0) return 1;
  uint8_t irq_set = BIT(bit_no);

  while (scan_code != ESC_BREAKCODE) {

    if ((r = driver_receive(ANY, &msg, &ipc_status)) != 0) {
      printf("driver_receive failed with: %d", r);
      continue;
    }
    if (is_ipc_notify(ipc_status)) {

      switch (_ENDPOINT_P(msg.m_source)) {
        case HARDWARE:

          if (msg.m_notify.interrupts & irq_set) {

            kbc_ih();
          }
          break;
        default:
          break;
      }
    }
  }

  if((keyboard_unsubscribe_int()) != 0) return 1;

  if (vg_exit() != 0) return 1;
  return 0;
}

int(video_test_pattern)(uint16_t mode, uint8_t no_rectangles, uint32_t first, uint8_t step) {
  
  vg_init(mode);

  if (draw_pattern(mode, no_rectangles, first, step) != 0)
  {
    vg_exit();
    return 1;
  }

  int ipc_status;
  message msg;
  uint32_t r;

  uint8_t bit_no;
  if((keyboard_subscribe_int(&bit_no)) != 0) return 1;
  uint8_t irq_set = BIT(bit_no);

  while (scan_code != ESC_BREAKCODE) {

    if ((r = driver_receive(ANY, &msg, &ipc_status)) != 0) {
      printf("driver_receive failed with: %d", r);
      continue;
    }
    if (is_ipc_notify(ipc_status)) {

      switch (_ENDPOINT_P(msg.m_source)) {
        case HARDWARE:

          if (msg.m_notify.interrupts & irq_set) {

            kbc_ih();
          }
          break;
        default:
          break;
      }
    }
  }

  if((keyboard_unsubscribe_int()) != 0) return 1;

  if (vg_exit() != 0) return 1;
  return 0;
}

int(video_test_xpm)(xpm_map_t xpm, uint16_t x, uint16_t y) {
  
  vg_init(MODE_1024x768);

  xpm_image_t img;
  uint8_t *map;
  map = xpm_load(xpm, XPM_INDEXED, &img);

  if(map == NULL)
  {
    vg_exit();
    return 1;
  }
  
  if(draw_pix_map(img, x, y) != 0)
  {
    vg_exit();
    return 1;
  }

  int ipc_status;
  message msg;
  uint32_t r;

  uint8_t bit_no;
  if((keyboard_subscribe_int(&bit_no)) != 0) return 1;
  uint8_t irq_set = BIT(bit_no);

  while (scan_code != ESC_BREAKCODE) {

    if ((r = driver_receive(ANY, &msg, &ipc_status)) != 0) {
      printf("driver_receive failed with: %d", r);
      continue;
    }
    if (is_ipc_notify(ipc_status)) {

      switch (_ENDPOINT_P(msg.m_source)) {
        case HARDWARE:

          if (msg.m_notify.interrupts & irq_set) {

            kbc_ih();
          }
          break;
        default:
          break;
      }
    }
  }

  if((keyboard_unsubscribe_int()) != 0) return 1;

  if (vg_exit() != 0) return 1;
  return 0;
}

int(video_test_move)(xpm_map_t xpm, uint16_t xi, uint16_t yi, uint16_t xf, uint16_t yf,
                     int16_t speed, uint8_t fr_rate) {
  
  vg_init(MODE_1024x768);

  xpm_image_t img;
  uint8_t *map;
  map = xpm_load(xpm, XPM_INDEXED, &img);

  if(map == NULL)
  {
    vg_exit();
    return 1;
  }
  
  if(draw_pix_map(img, xi, yi) != 0)
  {
    vg_exit();
    return 1;
  }

  int frame_counter = 0;
  uint8_t frame_time = sys_hz()/fr_rate;
  
  int distance_to_go;
  if (xi == xf) distance_to_go = abs(yf-yi);
  else distance_to_go = abs(xf-xi);

  int ipc_status;
  message msg;
  uint32_t r;

  uint8_t bit_no_timer, bit_no_keyboard;
  if (timer_subscribe_int(&bit_no_timer) != 0) return 1;
  if (keyboard_subscribe_int(&bit_no_keyboard) != 0) return 1;
  uint32_t irq_set_timer = BIT(bit_no_timer);
  uint32_t irq_set_keyboard = BIT(bit_no_keyboard);

  while (scan_code != ESC_BREAKCODE) {

    if ((r = driver_receive(ANY, &msg, &ipc_status)) != 0) {
      printf("driver_receive failed with: %d", r);
      continue;
    }
    if (is_ipc_notify(ipc_status)) {
      switch (_ENDPOINT_P(msg.m_source)) {
        case HARDWARE:
          if (msg.m_notify.interrupts & irq_set_keyboard) { /* subscribed interrupt */

            kbc_ih();
          }

          if (msg.m_notify.interrupts & irq_set_timer)
          {
            timer_int_handler();

            if(speed > 0)
            {
              if((interruption_counter % frame_time == 0) && (distance_to_go > 0))
              {
                if((xi == xf) && (yi == yf)) continue;

                else if(xi == xf) //x doesn't move, y moves
                {
                  clear_pix_map(img, xi, yi);

                  if(yi < yf) yi += speed;
                  else yi -= speed;
                  distance_to_go -= speed;
                  if(distance_to_go < 0) yi = yf;

                  draw_pix_map(img, xi, yi);
                }

                else if(yi == yf) //y doesn't move, x moves
                {
                  clear_pix_map(img, xi, yi);

                  if(xi < xf) xi += speed;
                  else xi -= speed;
                  distance_to_go -= speed;
                  if(distance_to_go < 0) xi = xf;

                  draw_pix_map(img, xi, yi);
                }
              }
            }
            else //If speed < 0
            {
              if(interruption_counter % frame_time == 0 ) frame_counter++;

              if((frame_counter == abs(speed)) && (distance_to_go > 0))
              {
                frame_counter = 0;

                if(xi == xf && yi == yf) continue;

                else if(xi == xf) //x doesn't move, y moves
                {
                  clear_pix_map(img, xi, yi);

                  if(yi < yf) yi += 1;
                  else yi -= 1;
                  distance_to_go -= 1;

                  draw_pix_map(img, xi, yi);
                }

                else if(yi == yf) //x moves, y doesn't
                {
                  clear_pix_map(img, xi, yi);

                  if(xi < xf) xi += 1;
                  else xi -= 1;
                  distance_to_go -= 1;

                  draw_pix_map(img, xi, yi);
                }
              }
            }
          }
          break;
        default:
          break; /* no other notifications expected: do nothing */
      }
    }
  }

  if (keyboard_unsubscribe_int() != 0) return 1;
  if (timer_unsubscribe_int() != 0) return 1;
  if (vg_exit() != 0) return 1;
  return 0;
}

int(video_test_controller)() {
  printf("%s(): Not done...\n", __func__);
  return 1;
}

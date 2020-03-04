// IMPORTANT: you must include the following line in all your C files
#include <lcom/lcf.h>
#include <lcom/lab5.h>
#include <stdint.h>
#include <stdio.h>
#include <machine/int86.h>

// Any header files included below this line should have been created by you
#include "video.h"
#include "vbe.h"
#include "kbc.h"
#include "timer.h"

extern uint8_t scancode;
extern int kbcID;
extern unsigned int interruptionCounter;

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

  if (set_graphics_mode(mode) != 0)
    return 1; // configure the video card for the desired graphics mode, using VBE

  sleep(delay);

  if(vg_exit() != 0)
    return 1;

  return 0;
}

int(video_test_rectangle)(uint16_t mode, uint16_t x, uint16_t y,
                          uint16_t width, uint16_t height, uint32_t color) {
  
  if ((vg_init)(mode) == NULL)
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
  if((kbc_subscribe_int(&bit_no)) != 0) // first subscribe the KBC interrupts
    return 1;

  // verify if a interrupt should be handled
  uint8_t irq_set = BIT(bit_no);

  while (scancode != ESC_BREAKCODE) {

    if ((r = driver_receive(ANY, &msg, &ipc_status)) != 0) {
      printf("driver_receive failed with: %d", r);
      continue;
    }
    if (is_ipc_notify(ipc_status)) {

      switch (_ENDPOINT_P(msg.m_source)) {
        case HARDWARE:

          if (msg.m_notify.interrupts & irq_set) { /* subscribed interrupt */

            kbc_ih();
          }
          break;
        default:
          break; /* no other notifications expected: do nothing */
      }
    }
  }

  if((kbc_unsubscribe_int()) != 0) // first subscribe the KBC interrupts
    return 1;

  if (vg_exit() != 0)
    return 1;

  return 0;
}

int(video_test_pattern)(uint16_t mode, uint8_t no_rectangles, uint32_t first, uint8_t step) {
  
  if (vg_init(mode) == 0)
    return 1;

  if (draw_pattern(mode, no_rectangles, first, step) != 0)
    return 1;

  int ipc_status;
  message msg;
  uint32_t r;

  uint8_t bit_no;
  if((kbc_subscribe_int(&bit_no)) != 0) // first subscribe the KBC interrupts
    return 1;

  // verify if a interrupt should be handled
  uint8_t irq_set = BIT(bit_no);

  while (scancode != ESC_BREAKCODE) {

    if ((r = driver_receive(ANY, &msg, &ipc_status)) != 0) {
      printf("driver_receive failed with: %d", r);
      continue;
    }
    if (is_ipc_notify(ipc_status)) {

      switch (_ENDPOINT_P(msg.m_source)) {
        case HARDWARE:

          if (msg.m_notify.interrupts & irq_set) { /* subscribed interrupt */

            kbc_ih();
          }
          break;
        default:
          break; /* no other notifications expected: do nothing */
      }
    }
  }

  if((kbc_unsubscribe_int()) != 0) // first subscribe the KBC interrupts
    return 1;

  if (vg_exit() != 0)
    return 1;

  return 0;
}

int(video_test_xpm)(xpm_map_t xpm, uint16_t x, uint16_t y) {
  
  if (vg_init(MODE_1024x768) == NULL)// 0x105 VBE mode
  {
    vg_exit();
    return 1;
  } 
    

  xpm_image_t img;
  uint8_t *map;
  // get the pixmap from the XPM
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
  if((kbc_subscribe_int(&bit_no)) != 0) // first subscribe the KBC interrupts
    return 1;

  // verify if a interrupt should be handled
  uint8_t irq_set = BIT(bit_no);

  while (scancode != ESC_BREAKCODE) {

    if ((r = driver_receive(ANY, &msg, &ipc_status)) != 0) {
      printf("driver_receive failed with: %d", r);
      continue;
    }
    if (is_ipc_notify(ipc_status)) {

      switch (_ENDPOINT_P(msg.m_source)) {
        case HARDWARE:

          if (msg.m_notify.interrupts & irq_set) { /* subscribed interrupt */

            kbc_ih();

          }
          break;
        default:
          break; /* no other notifications expected: do nothing */
      }
    }
  }

  if (vg_exit() != 0)
    return 1;

  if((kbc_unsubscribe_int()) != 0) // first subscribe the KBC interrupts
    return 1;



  return 0;
}

int(video_test_move)(xpm_map_t xpm, uint16_t xi, uint16_t yi, uint16_t xf, uint16_t yf,
                     int16_t speed, uint8_t fr_rate) {
  
  if (vg_init(MODE_1024x768) == NULL) // 0x105 VBE mode
  {
    vg_exit();
    return 1;
  }

  xpm_image_t img;
  uint8_t *map;
  // get the pixmap from the XPM
  map = xpm_load(xpm, XPM_INDEXED, &img);

  if (map == NULL)
  {
    vg_exit();
    return 1;
  }

  uint8_t frame_time = sys_hz()/fr_rate;

  if (draw_pix_map(img, xi, yi) != 0)
  {
    vg_exit();
    return 1;
  }

  int distance_to_go;
  int frameCounter = 0;

  if (xi == xf) distance_to_go = abs(yf-yi);
  else distance_to_go = abs(xf-xi);

  int ipc_status;
  message msg;
  uint32_t r;

  uint8_t bit_no;
  if((kbc_subscribe_int(&bit_no)) != 0) // first subscribe the KBC interrupts
    return 1;

  uint8_t bit_no_timer;
  if ((timer_subscribe_int(&bit_no_timer)) != 0)
    return 1;

  // verify if a interrupt should be handled
  uint8_t irq_set = BIT(bit_no);
  uint8_t irq_set_timer = BIT(bit_no_timer);

  while (scancode != ESC_BREAKCODE) {

    if ((r = driver_receive(ANY, &msg, &ipc_status)) != 0) {
      printf("driver_receive failed with: %d", r);
      continue;
    }
    if (is_ipc_notify(ipc_status)) {

      switch (_ENDPOINT_P(msg.m_source)) {
        case HARDWARE:

          if (msg.m_notify.interrupts & irq_set) { /* subscribed interrupt */

            kbc_ih();
          }
          if (msg.m_notify.interrupts & irq_set_timer)
          {
            timer_int_handler();

            if(speed > 0)
            {
              if(interruptionCounter % frame_time == 0 && distance_to_go > 0)
              {
                if(xi == xf && yi == yf) //If finished, no need to update drawing
                  continue;

                else if(xi == xf) //x doesn't move, y moves
                {
                  if(clear_pix_map(img, xi, yi) != 0) //Erases pix map previously drawn
                  {
                    vg_exit();
                    return 1; 
                  }

                  if(yi < yf) //Direction of animation
                    yi = yi + speed;
                  else
                    yi = yi - speed;

                  distance_to_go -= speed;

                  if(distance_to_go < 0) //If distance is negative, then set current y as the final y
                    yi = yf;

                  if (draw_pix_map(img, xi, yi) != 0) //Draws pix map in new position
                  {
                    vg_exit();
                    return 1;
                  }


                }

                else if(yi == yf) //y doesn't move, x moves
                {
                  if(clear_pix_map(img, xi, yi) != 0) //Erases pix map previously drawn
                  {
                    vg_exit();
                    return 1; 
                  }

                  if(xi < xf) //Direction of animation
                    xi = xi + speed;
                  else 
                    xi = xi - speed;

                  distance_to_go -= speed;

                  if(distance_to_go < 0)
                    xi = xf;

                  if (draw_pix_map(img, xi, yi) != 0) //Draws pix map in new position
                  {
                    vg_exit();
                    return 1;
                  }
                }
              }
            }

            else //If speed < 0
            {
              if(interruptionCounter % frame_time == 0 )
                frameCounter++;

              if(frameCounter == abs(speed) && distance_to_go > 0)
              {
                frameCounter = 0; //Resets frame counter to 0

                if(xi == xf && yi == yf) //If already drawn, continue loop
                  continue;

                else if(xi == xf) //x doesn't move, y moves
                {
                  if(clear_pix_map(img, xi, yi) != 0) //Erases pix map previously drawn
                  {
                    vg_exit();
                    return 1; 
                  }

                  if(yi < yf) //Direction of animation
                    yi = yi + 1;
                  else
                    yi = yi - 1;

                  distance_to_go -= 1;

                  if(draw_pix_map(img, xi, yi) != 0) //Draws pix map in new position
                  {
                    vg_exit();
                    return 1;
                  }
                }

                else if(yi == yf) //x moves, y doesn't
                {
                  if(clear_pix_map(img, xi, yi) != 0) //Erases pix map previously drawn
                  {
                    vg_exit();
                    return 1; 
                  }

                  if(xi < xf) //Direction of animation
                    xi = xi + 1;
                  else 
                    xi = xi - 1;

                  distance_to_go -= 1;

                  if(draw_pix_map(img, xi, yi) != 0) //Draws pix map in new position
                  {
                    vg_exit();
                    return 1;
                  }
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



  if ((timer_unsubscribe_int()) != 0)
    return 1;

  if((kbc_unsubscribe_int()) != 0) // first subscribe the KBC interrupts
    return 1;

  if(vg_exit() != 0)
    return 1;

  return 0;
}


int(video_test_controller)() {
  
  /*vg_vbe_contr_info_t contr_info;
  vbe_info_t info;


  if(vbe_get_contr_info(&contr_info, &info) != 0)
    return 1;

  if(vg_display_vbe_contr_info(&contr_info) != 0)
    return 1;*/

  return 1;
}

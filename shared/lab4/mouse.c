#include "mouse.h"

int mouse_ID = 2;
uint32_t status;
uint16_t packet[3];
unsigned int packet_counter = 0;
struct packet pp;

int mouse_subscribe_int(uint8_t *bit_no)
{
  *bit_no = mouse_ID;
  if (sys_irqsetpolicy(MOUSE_IRQ, (IRQ_REENABLE | IRQ_EXCLUSIVE), &mouse_ID) != 0) return 1;
  return 0;
}

int mouse_unsubscribe_int()
{
  if (sys_irqrmpolicy(&mouse_ID) != 0) return 1;
  return 0;
}

void (mouse_ih)()
{
	uint32_t status_register;
	sys_inb(STAT_REG, &status_register);
	if ((status_register & OBF_FULL) == OBF_FULL)
		sys_inb(OUT_BUF, &status);
}

int write_keyboard(uint32_t port, uint32_t command)
{
  uint32_t status;
  while (1) {
    sys_inb(STAT_REG, &status);
    if ((status & IBF_FULL) == 0) return sys_outb(port, command);  
    tickdelay(micros_to_ticks(DELAY_US));    
  }
}

int read_keyboard(uint32_t *data)
{
  uint32_t status;
  while (1) {
    if (sys_inb(STAT_REG, &status)) return 1;
    if (status & OBF_FULL) return sys_inb(OUT_BUF, data);
    tickdelay(micros_to_ticks(DELAY_US));
  }
}

int write_command_byte(uint32_t command)
{
  uint32_t data;
  while (1) {
    if (write_keyboard(STAT_REG, KBC_WRITECMDBYTE) == 1) return 1;
    if (write_keyboard(OUT_BUF, command) == 1) return 1;
    sys_inb(OUT_BUF, &data);
    if (data == MOUSE_ACK) return 0;
  }
}

int write_mouse(uint32_t command)
{

  uint32_t data;
  while (1) {
    if (write_keyboard(STAT_REG, WRITE_MOUSE) == 1) return 1;
    if (write_keyboard(OUT_BUF, command) == 1) return 1;
    sys_inb(OUT_BUF, &data);
    if (data == MOUSE_ACK) return 0;
  }
}

void packet_create()
{
  pp.bytes[0] = packet[0];
  pp.bytes[1] = packet[1];
  pp.bytes[2] = packet[2];

  pp.lb = (packet[0] & MOUSE_LB);
  pp.rb = (packet[0] & MOUSE_RB) >> 1;
  pp.mb = (packet[0] & MOUSE_MB) >> 2;

  if((packet[0] & MOUSE_XSIGN) >> 4 == 0)
  {
    pp.delta_x = (packet[1] & 0x00FF);
  }
  else
  {
    pp.delta_x = (packet[1] | 0xFF00); 
    }
  
  if((packet[0] & MOUSE_YSIGN) >> 5 == 0)
  {
    pp.delta_y = (packet[2] & 0x00FF);
  }
  else
  {
    pp.delta_y = (packet[2] | 0xFF00); 
    }
  
  pp.x_ov = (packet[0] & MOUSE_XOVF) >> 6;
  pp.y_ov = (packet[0] & MOUSE_YOVF) >> 7;
}

void detect_mouse_event(struct packet *pp, state_machine_t *st_machine, struct mouse_ev *m_ev)
{
  switch(st_machine->currentState)
  {
    case INITIAL_STATE:
      if(pp->lb && !pp->mb && !pp->rb) m_ev->type = LB_PRESSED;
      else if(pp->mb || pp->rb) m_ev->type = BUTTON_EV;
      else m_ev->type = MOUSE_MOV;
      break;

    case LEFT_LINE:
      if(pp->lb && !pp->mb && !pp->rb) m_ev->type = MOUSE_MOV; 
      else if(pp->mb || pp->rb) m_ev->type = BUTTON_EV;
      else m_ev->type = LB_RELEASED;
      break;

    case VERTEX:
      if(pp->mb) m_ev->type = BUTTON_EV;
      else if(pp->lb && !pp->rb) m_ev->type = LB_PRESSED;
      else if(pp->rb) m_ev->type = RB_PRESSED;
      else m_ev->type = MOUSE_MOV;
      break;

    case RIGHT_LINE:
      if(!pp->lb && !pp->mb && pp->rb) m_ev->type = MOUSE_MOV;
      else if(pp->lb || pp->mb) m_ev->type = BUTTON_EV;
      else m_ev->type = RB_RELEASED;
      break;

    default: //This state will not be reached
      m_ev->type = MOUSE_MOV;
      break;
  }
  m_ev->delta_x = pp->delta_x;
  m_ev->delta_y = pp->delta_y;
}

void handle_mouse_event(state_machine_t *st_machine, struct mouse_ev event, uint8_t x_len, uint8_t tolerance)
{
  switch(st_machine->currentState)
  {
    case INITIAL_STATE:
      if(event.type == LB_PRESSED) {
        st_machine->currentState = LEFT_LINE;
        st_machine->x_displacement = 0;
        st_machine->y_displacement = 0;
      }
      break;


    case LEFT_LINE:
      if(event.type == MOUSE_MOV) 
      {
        if(-1 * event.delta_x > tolerance || -1 * event.delta_y > tolerance)
        {
          st_machine->currentState = INITIAL_STATE;
          st_machine->x_displacement = 0;
          st_machine->y_displacement = 0;
        }
        else 
        {
          st_machine->x_displacement += event.delta_x;
          st_machine->y_displacement += event.delta_y;
        }
      }
      else if(event.type == LB_RELEASED)
      {
        double x = abs(st_machine->x_displacement);
        double y = abs(st_machine->y_displacement);

        if ((x >= x_len) && ((y/x) > 1)) 
        {
          st_machine->currentState = VERTEX;
          st_machine->x_displacement = 0;
          st_machine->y_displacement = 0;
        }
        else
        {
          st_machine->currentState = INITIAL_STATE;
          st_machine->x_displacement = 0;
          st_machine->y_displacement = 0;
        }
      }
      else if(event.type == BUTTON_EV)
      {
        st_machine->currentState = INITIAL_STATE;
        st_machine->x_displacement = 0;
        st_machine->y_displacement = 0;
      }
      break;

    case VERTEX: 
      if(event.type == MOUSE_MOV)
      {
        if(abs(st_machine->x_displacement) > tolerance || abs(st_machine->y_displacement) > tolerance) 
        {
          st_machine->currentState = INITIAL_STATE; 
          st_machine->x_displacement = 0;
          st_machine->y_displacement = 0;
        }
      }
      else if(event.type == LB_PRESSED) 
      {
        st_machine->currentState = LEFT_LINE; 
        st_machine->x_displacement = 0;
        st_machine->y_displacement = 0;
      }
      else if(event.type == RB_PRESSED) 
      {
        st_machine->currentState = RIGHT_LINE; 
        st_machine->x_displacement = 0; 
        st_machine->y_displacement = 0; 
      }
      else if(event.type == BUTTON_EV) 
      {
        st_machine->currentState = INITIAL_STATE;
        st_machine->x_displacement = 0;
        st_machine->y_displacement = 0;
      }
      break;

    case RIGHT_LINE: 
      if(event.type == RB_RELEASED)
      {
        double x = abs(st_machine->x_displacement);
        double y = abs(st_machine->y_displacement);
        if(x >= x_len && (y/x) > 1) 
        {
          st_machine->currentState = FINAL_STATE;
        }
        else
        {
          st_machine->currentState = INITIAL_STATE; 
          st_machine->x_displacement = 0;
          st_machine->y_displacement = 0;
        }
      }
      else if(event.type == MOUSE_MOV) 
      {
        if(-1 * event.delta_x > tolerance || event.delta_y > tolerance) 
        {
          st_machine->currentState = INITIAL_STATE; 
          st_machine->x_displacement = 0;
          st_machine->y_displacement = 0;
        }
        else 
        {
          st_machine->x_displacement += event.delta_x;
          st_machine->y_displacement += event.delta_y;
        }

      }
      else if(event.type == BUTTON_EV)
      {
        st_machine->currentState = INITIAL_STATE; 
        st_machine->x_displacement = 0;
        st_machine->y_displacement = 0;
      }
      break;

    case FINAL_STATE: break;

    default: break;
  }
}

int check_gesture(uint8_t x_len, uint8_t tolerance, state_machine_t *st_machine, struct mouse_ev event)
{
  detect_mouse_event(&pp, st_machine, &event);
  handle_mouse_event(st_machine, event, x_len, tolerance);
  if (st_machine->currentState == FINAL_STATE) return 0;
  else return 1;
}

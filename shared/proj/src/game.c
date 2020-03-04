#include "game.h"

int card_counter = 0;
int pair_counter = 0;
uint8_t nsec;

void interrupt_handler(Game *game, Game_state *states)
{
  int ipc_status;
  message msg;
  uint32_t r;
  //int pos = 1;  //mouse
  bool two_bytes = false;
  uint8_t bytes[2];  

  while (scan_code != ESC_BREAKCODE) {

    if ((r = driver_receive(ANY, &msg, &ipc_status)) != 0) {
      printf("driver_receive failed with: %d", r);
      continue;
    }
    if (is_ipc_notify(ipc_status)) {

      switch (_ENDPOINT_P(msg.m_source)) {
        case HARDWARE:

          if (msg.m_notify.interrupts & game->irq_set_keyboard) { /* subscribed interrupt */
            kbc_ih();
            if (two_bytes == true)
            {
              two_bytes = false;
              bytes[1] = scan_code;
              kbd_print_scancode(((scan_code & MAKE_CODE) == 0),2,bytes);
            }
            
            else {
              if (scan_code == FIRST_BYTE_OF_2BYTES)
              {
                  two_bytes = true;
                  bytes[0] = scan_code;
              }
              else
              {
                bytes[0] = scan_code;
                kbd_print_scancode(((scan_code & MAKE_CODE) == 0),1,bytes);
              }
            }
            detect_keyboard_event(game, states);
            manage_states(game, states);
          }

          if (msg.m_notify.interrupts & game->irq_set_timer) {
            
            //manage_states(game, states);
            
            if (*states == GAME)
            {
              game->int_counter++;
              game->int_counter %= 60;
              if (game->int_counter == 0)
              {
                drawNsec(states, nsec);
                nsec++;
              }
            }
          }
          /*
          if (msg.m_notify.interrupts & game->irq_set_mouse) {
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
              //pto.x_pos += pp.delta_x;
              //pto.y_pos += pp.delta_y;
              //mouse_print_packet(&pp);
              pos = 1;
            }
            
          }*/
          break;
        default:
          break;
      }
    }
  }
}

int detect_keyboard_event(Game *game, Game_state *states)
{
  if (*states == MAIN_MENU)
  {
    if (scan_code == SCAN_J)
    {
      *states = GAME;
      pto.x_pos = LEFTMOST_POS;
      pto.y_pos = UPMOST_POS;
      pto.idx = 0;
      game->int_counter = 0;
      nsec = 0;
    }

    else if (scan_code == SCAN_I)
      *states = INSTRUCTIONS;
  }
  // -------------------------------
  else if (*states == INSTRUCTIONS)
  {
    if (scan_code == SCAN_H)
      *states = MAIN_MENU;
  }
  // -------------------------------
  else if (*states == GAME)
  {
    if (card_counter == 2)
    {
      analise_pairing(game->cards);
      card_counter = 0;
      if (pair_counter == 5)
      {
        game->you_won = true;
        *states = GAME_OVER;
      }
    }

    else if (scan_code == SCAN_UP) move_up(&pto);
    else if (scan_code == SCAN_LEFT) move_left(&pto);
    else if (scan_code == SCAN_RIGHT) move_right(&pto);
    else if (scan_code == SCAN_DOWN) move_down(&pto);
    else if (scan_code == SCAN_SPACE)
    {
      if (game->cards[pto.idx].founded == false)
      {
        if (card_counter == 0 || card_counter == 1)
        {
          turnCard(game->cards);
          card_counter++;
        }
      }
    }
  }
  // -------------------------------
  else if (*states == GAME_OVER)
  {
    if (scan_code == SCAN_S)
    {
      *states = GAME;
      createDeck(game->cards);
      pto.x_pos = LEFTMOST_POS;
      pto.y_pos = UPMOST_POS;
      pto.idx = 0;
      game->int_counter = 0;
      pair_counter = 0;
      card_counter = 0;
      nsec = 0;
      game->you_won = false;
    }
    else if (scan_code == SCAN_N)
    {
      *states = MAIN_MENU;
      createDeck(game->cards);
      pto.x_pos = LEFTMOST_POS;
      pto.y_pos = UPMOST_POS;
      pto.idx = 0;
      game->int_counter = 0;
      pair_counter = 0;
      card_counter = 0;
      nsec = 0;
    }
  }
  // ...
  return 0;
}

int manage_states(Game *game, Game_state *states)
{
  if (*states == MAIN_MENU)
  {
    drawMainMenu();
  }
  // -------------------------------
  if (*states == GAME)
  {
    drawBackground();
    drawCards(game->cards);
    drawRedDot(pto.x_pos, pto.y_pos);
    drawNsec(states, nsec);
  }
  // -------------------------------
  if (*states == INSTRUCTIONS)
  {
    drawInstructions();
  }
  // -------------------------------
  if (*states == GAME_OVER)
  {
    if (game->you_won == false)
    {
      drawYouLose();
    }
    else if (game->you_won == true)
    {
      drawYouWin();
    }
  }

  return 0;
}

void drawNsec(Game_state *states, uint8_t nsec)
{
  switch (nsec)
  {
    case 0: draw0(10,10); break;
    case 1: draw1(10,10); break;
    case 2: draw2(10,10); break;
    case 3: draw3(10,10); break;
    case 4: draw4(10,10); break;
    case 5: draw5(10,10); break;
    case 6: draw6(10,10); break;
    case 7: draw7(10,10); break;
    case 8: draw8(10,10); break;
    case 9: draw9(10,10); break;
    case 10: draw1(10,10); draw0(40,10); break;
    case 11: draw1(10,10); draw1(40,10); break;
    case 12: draw1(10,10); draw2(40,10); break;
    case 13: draw1(10,10); draw3(40,10); break;
    case 14: draw1(10,10); draw4(40,10); break;
    case 15: draw1(10,10); draw5(40,10); break;
    case 16: draw1(10,10); draw6(40,10); break;
    case 17: draw1(10,10); draw7(40,10); break;
    case 18: draw1(10,10); draw8(40,10); break;
    case 19: draw1(10,10); draw9(40,10); break;
    case 20: draw2(10,10); draw0(40,10); break;
    case 21: draw2(10,10); draw1(40,10); break;
    case 22: draw2(10,10); draw2(40,10); break;
    case 23: draw2(10,10); draw3(40,10); break;
    case 24: draw2(10,10); draw4(40,10); break;
    case 25: draw2(10,10); draw5(40,10); break;
    case 26: draw2(10,10); draw6(40,10); break;
    case 27: draw2(10,10); draw7(40,10); break;
    case 28: draw2(10,10); draw8(40,10); break;
    case 29: draw2(10,10); draw9(40,10); break;
    case 30: *states = GAME_OVER; break;
  }
}

Game *start_game()
{
	Game *game = malloc(sizeof(Game));

	uint8_t bit_no_timer; timer_subscribe_int(&bit_no_timer);
	uint8_t bit_no_mouse; mouse_subscribe_int(&bit_no_mouse);
	
	sys_irqdisable(&mouse_ID);
  write_mouse(MOUSE_ENABLE);
  sys_irqenable(&mouse_ID);
  	
  uint8_t bit_no_keyboard; keyboard_subscribe_int(&bit_no_keyboard);

  game->irq_set_timer = BIT(bit_no_timer);
  game->irq_set_mouse = BIT(bit_no_mouse);
  game->irq_set_keyboard = BIT(bit_no_keyboard);

  createDeck(game->cards);

  game->you_won = false;

  return game;
}

void end_game(Game *game)
{
	timer_unsubscribe_int();
	mouse_unsubscribe_int();
	keyboard_unsubscribe_int();

  free(game);
}

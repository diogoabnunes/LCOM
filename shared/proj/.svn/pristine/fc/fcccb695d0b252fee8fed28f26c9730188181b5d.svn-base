#ifndef __GAME_H
#define __GAME_H

#include "keyboard.h"
#include "mouse.h"
#include "video.h"
#include "state_machine.h"
#include "xpms.h"
#include "codes.h"
#include "dot.h"
#include "cards.h"

extern int mouse_ID;
extern uint8_t scan_code;
extern uint32_t status;
extern struct packet pp;
extern uint16_t packet[3];

dot_t pto;

typedef struct {
	int irq_set_keyboard;
	int irq_set_timer;
	int irq_set_mouse;

	int int_counter;
	uint8_t scan;

	card_t cards[NUM_CARDS];

	bool you_won;
} Game;

///@brief Esta função faz o loop que lida com as interrupções dos dispositivos
///@param game Estrutura com os atributos necessários para o jogo
///@param states Estados da máquina de estados que representa o jogo
void interrupt_handler(Game *game, Game_state *states);

///@brief Esta função detecta os eventos do teclado
///@param game Estrutura com os atributos necessários para o jogo
///@param states Estados da máquina de estados que representa o jogo
///@return 0
int detect_keyboard_event(Game *game, Game_state *states);

///@brief Esta função lida com os eventos do teclado
///@param game Estrutura com os atributos necessários para o jogo
///@param states Estados da máquina de estados que representa o jogo
///@return 0
int manage_states(Game *game, Game_state *states);

///@brief Esta função desenha o número de segundos que passaram durante o jogo.
///@param states Estados da máquina de estados que representa o jogo.
///@param nsec Número de segundos passados desde o início do jogo.
void drawNsec(Game_state *states, uint8_t nsec);

///@brief Esta função prepara o jogo que iniciará
///@return Um jogo pronto pra começar
Game *start_game();

///@brief Esta função termina o jogo
///@param game Estrutura com os atributos necessários para o jogo
void end_game(Game *game);

#endif

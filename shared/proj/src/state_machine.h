#ifndef STATE_MACHINE_H
#define STATE_MACHINE_H

typedef enum {
	MAIN_MENU, 
	GAME, 
	INSTRUCTIONS, 
	GAME_OVER
} Game_state;

///@brief Esta função aloca memória para um jogo
///@return O estado do jogo
Game_state *new_states();

///@brief Esta função libera o espaço alocado na memória para o jogo
///@param game_states O estado do jogo
void delete_states(Game_state *game_states);

#endif

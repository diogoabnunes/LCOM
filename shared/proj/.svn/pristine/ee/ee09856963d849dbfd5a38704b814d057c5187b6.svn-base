#include "state_machine.h"
#include "stdlib.h"

Game_state *new_states()
{
	Game_state *game_states = malloc(sizeof(Game_state));
	*game_states = MAIN_MENU;

	return game_states;
}

void delete_states(Game_state *game_states)
{
	free(game_states);
}

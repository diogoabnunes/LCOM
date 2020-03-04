#ifndef __DOT_H
#define __DOT_H

#include "video.h"

#define LEFTMOST_POS 167
#define RIGHTMOST_POS 567
#define UPMOST_POS 175
#define DOWNMOST_POS 325

typedef struct {
	uint32_t x_pos;
	uint32_t y_pos;
	int idx;
	xpm_image_t dot;
} dot_t;

///@brief Esta função move o cursor para cima
///@param ponto Ponteiro de dot_t que representa o cursor a ser movido
///@return 0
int move_up(dot_t *ponto);

///@brief Esta função move o cursor para a direita
///@param ponto Ponteiro de dot_t que representa o cursor a ser movido
///@return 0
int move_right(dot_t *ponto);

///@brief Esta função move o cursor para a esquerda
///@param ponto Ponteiro de dot_t que representa o cursor a ser movido
///@return 0
int move_left(dot_t *ponto);

///@brief Esta função move o cursor para baixo
///@param ponto Ponteiro de dot_t que representa o cursor a ser movido
///@return 0
int move_down(dot_t *ponto);

#endif

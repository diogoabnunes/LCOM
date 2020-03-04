#ifndef __CARDS_H
#define __CARDS_H

//Includes
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>

#include "xpms.h"
 
extern dot_t pto;
extern int pair_counter;

//Defines
#define NUM_CARDS 10
#define NUM_CLRS 10

#define X_COL1 150
#define X_COL2 250
#define X_COL3 350
#define X_COL4 450
#define X_COL5 550

#define Y_TOP_ROW 150
#define Y_BOTTOM_ROW 300

#define BLUE_CLR 1
#define DARK_GREEN_CLR 2
#define GREEN_CLR 3
#define GREY_CLR 4
#define ORANGE_CLR 5
#define PINK_CLR 6
#define PURPLE_CLR 7
#define SEA_BLUE_CLR 8
#define WHITE_CLR 9
#define YELLOW_CLR 10


//Structs
typedef struct
{
	uint8_t color; //Código com a cor da carta
	bool faceUp; //Para usarmos como boolean pra saber se ela já foi encontrada
	uint32_t x_pos; //Posição x do primeiro pixel da carta
	uint32_t y_pos; //Posição y do primeiro pixel da carta
	xpm_image_t verso; // verso da carta
	xpm_image_t frente; // frente da carta
	bool founded;
} card_t;

//Functions

///@brief Esta função embaralha as cores jogáveis para que cada jogo tenha cores diferentes 
///@param allColors Array com as cores jogáveis
void shuffleColors(uint8_t allColors[NUM_CLRS]);

///@brief Esta função embaralha o deck de cartas para que cada jogo tenha posições diferentes
///@param deck Array com as cartas a serem embaralhadas
void shuffleDeck(card_t deck[NUM_CARDS]);

///@brief Esta função prepara o deck para um jogo
///@param deck Array com as cartas que serão jogadas
///@return 0 se houver successo, 1 no caso contrário
int createDeck(card_t deck[NUM_CARDS]);

///@brief Esta função faz a ação de virar uma carta
///@param deck Array com as cartas das quais uma será virada
///@return 0 se houver successo, 1 no caso contrário
int turnCard(card_t deck[NUM_CARDS]);

///@brief Esta função desenha a parte da frente da carta
///@param card Carta a ser desenhada
///@return 0 se houver successo, 1 no caso contrário
int drawCartaFrente(card_t card);

///@brief Esta função desenha a parte de trás da carta
///@param card Carta a ser desenhada
///@return 0 se houver successo, 1 no caso contrário
int drawCartaVerso(card_t card);

///@brief Esta função desenha as cartas do jogo
///@param deck Array com as cartas que serão desenhadas
///@return 0 se houver successo, 1 no caso contrário
int drawCards(card_t deck[NUM_CARDS]);

///@brief Esta função analisa se o par de cartas escolhido é o par correto
///@param deck Array com as cartas do jogo
///@return 0 se houver successo, 1 no caso contrário
int analise_pairing(card_t deck[NUM_CARDS]);

#endif

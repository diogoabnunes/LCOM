#include "cards.h"

void shuffleColors(uint8_t allColors[NUM_CLRS])
{
    uint8_t i, j, tmp; //Create local variables to hold values for shuffle
    srand(time(NULL));
    for (i = NUM_CLRS - 1; i > 0; i--) //For loop to shuffle
    {
        j = rand() % (i + 1); //Randomise j for shuffle with Fisher-Yates algorithm
        tmp = allColors[j];
        allColors[j] = allColors[i];
        allColors[i] = tmp;
    }
}

void shuffleDeck(card_t deck[NUM_CARDS])
{
	uint8_t i, j; 
	card_t tmp; //Create local variables to hold values for shuffle
    srand(time(NULL));

    for (i = NUM_CARDS - 1; i > 0; i--) //For loop to shuffle
    {
        j = rand() % (i + 1); //Randomise j for shuffle with Fisher-Yates algorithm
        tmp = deck[j];
        deck[j] = deck[i];
        deck[i] = tmp;
    }
}


int createDeck(card_t deck[NUM_CARDS])
{
	uint8_t colors[NUM_CLRS] = {BLUE_CLR, DARK_GREEN_CLR, GREEN_CLR, GREY_CLR, 
				ORANGE_CLR, PINK_CLR, PURPLE_CLR, SEA_BLUE_CLR, WHITE_CLR, YELLOW_CLR}; //Possible card colors
	shuffleColors(colors); //Shuffles colors to be picked randomly

	for(uint8_t i = 0; i < NUM_CARDS; i += 2) //Assigns every other color to each pair of cards
	{
		deck[i].color = colors[i];
		deck[i + 1].color = colors[i];
	}

	shuffleDeck(deck); //Shuffles the deck so every game is different

	for(uint8_t i = 0; i < NUM_CARDS; i++) //This loop assigns the faceUp and coordinates for each card
	{
		deck[i].faceUp = false;
        deck[i].founded = false;

    	uint8_t *map = xpm_load(card_xpm, XPM_8_8_8, &deck[i].verso);
    	if(map == NULL) return 1;

    	switch(deck[i].color)
    	{
    		case BLUE_CLR:
    			map = xpm_load(blue_card_xpm, XPM_8_8_8, &deck[i].frente);
    		case DARK_GREEN_CLR:
    			map = xpm_load(dark_green_card_xpm, XPM_8_8_8, &deck[i].frente);
    		case GREEN_CLR:
    			map = xpm_load(green_card_xpm, XPM_8_8_8, &deck[i].frente);
    		case GREY_CLR:
    			map = xpm_load(grey_card_xpm, XPM_8_8_8, &deck[i].frente);
    		case ORANGE_CLR:
    			map = xpm_load(orange_card_xpm, XPM_8_8_8, &deck[i].frente);
    		case PINK_CLR:
    			map = xpm_load(pink_card_xpm, XPM_8_8_8, &deck[i].frente);
    		case PURPLE_CLR:
    			map = xpm_load(purple_card_xpm, XPM_8_8_8, &deck[i].frente);
    		case SEA_BLUE_CLR:
    			map = xpm_load(sea_blue_card_xpm, XPM_8_8_8, &deck[i].frente);
    		case WHITE_CLR:
    			map = xpm_load(white_card_xpm, XPM_8_8_8, &deck[i].frente);
    		case YELLOW_CLR:
    			map = xpm_load(yellow_card_xpm, XPM_8_8_8, &deck[i].frente);
    	}

		if(i < NUM_CARDS/2)
		{
			deck[i].y_pos = Y_TOP_ROW;
		}
		else
		{
			deck[i].y_pos = Y_BOTTOM_ROW;
		}

		switch((i%5) + 1)
		{
			case 1:
				deck[i].x_pos = X_COL1;
				break;
			case 2:
				deck[i].x_pos = X_COL2;
				break;
			case 3:
				deck[i].x_pos = X_COL3;
				break;
			case 4:
				deck[i].x_pos = X_COL4;
				break;
			case 5:
				deck[i].x_pos = X_COL5;
				break;
		} //End of switch
	} //End of for loop

	return 0;
} //End of function

int drawCartaFrente(card_t card)
{
    uint8_t *map;
    if (card.color == BLUE_CLR) map = xpm_load(blue_card_xpm, XPM_8_8_8, &card.frente);
    if (card.color == DARK_GREEN_CLR) map = xpm_load(dark_green_card_xpm, XPM_8_8_8, &card.frente);
    if (card.color == GREEN_CLR) map = xpm_load(green_card_xpm, XPM_8_8_8, &card.frente);
    if (card.color == GREY_CLR) map = xpm_load(grey_card_xpm, XPM_8_8_8, &card.frente);
    if (card.color == ORANGE_CLR) map = xpm_load(orange_card_xpm, XPM_8_8_8, &card.frente);
    if (card.color == PINK_CLR) map = xpm_load(pink_card_xpm, XPM_8_8_8, &card.frente);
    if (card.color == PURPLE_CLR) map = xpm_load(purple_card_xpm, XPM_8_8_8, &card.frente);
    if (card.color == SEA_BLUE_CLR) map = xpm_load(sea_blue_card_xpm, XPM_8_8_8, &card.frente);
    if (card.color == WHITE_CLR) map = xpm_load(white_card_xpm, XPM_8_8_8, &card.frente);
    if (card.color == YELLOW_CLR) map = xpm_load(yellow_card_xpm, XPM_8_8_8, &card.frente);
    if(map == NULL) return 1;
    draw_pix_map(card.frente, card.x_pos, card.y_pos);
    return 0;
}

int drawCartaVerso(card_t card)
{
    uint8_t *map = xpm_load(card_xpm, XPM_8_8_8, &card.verso);
    if(map == NULL) return 1;
    draw_pix_map(card.verso, card.x_pos, card.y_pos);
    return 0;
}


int drawCards(card_t deck[NUM_CARDS])
{
    for(int i = 0; i < NUM_CARDS; i++)
        if (deck[i].faceUp == false && deck[i].founded == false)
            drawCartaVerso(deck[i]);
        else if (deck[i].faceUp == true && deck[i].founded == false)
            drawCartaFrente(deck[i]);
	return 0;
}

int turnCard(card_t deck[NUM_CARDS])
{
    if(deck[pto.idx].faceUp == false)
    {
        deck[pto.idx].faceUp = true;
    }
    return 0;
}

int analise_pairing(card_t deck[NUM_CARDS])
{
    for(uint8_t first = 0; first < NUM_CARDS; first++)
    {
        if (deck[first].faceUp == true)
        {
            for(uint8_t second = first+1; second < NUM_CARDS; second++)
            {
                if (deck[second].faceUp == true)
                {
                    if (deck[first].color == deck[second].color)
                    {
                        deck[first].founded = true;
                        deck[second].founded = true;
                        pair_counter++;
                    }
                    deck[first].faceUp = false;
                    deck[second].faceUp = false;
                    sleep(1);
                    return 0;
                }
            }
        }
    }
    return 1;
}

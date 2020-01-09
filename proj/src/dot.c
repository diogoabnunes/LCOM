#include "dot.h"

int move_up(dot_t *ponto)
{
	if (ponto->y_pos != UPMOST_POS)
  {
    ponto->y_pos -= 150;
    ponto->idx -= 5;
  }
  return 0;
}

int move_right(dot_t *ponto)
{
	if (ponto->x_pos != RIGHTMOST_POS)
  {
    ponto->x_pos += 100;
    ponto->idx += 1;
  }
  return 0;
}

int move_left(dot_t *ponto)
{
	if (ponto->x_pos != LEFTMOST_POS)
  {
    ponto->x_pos -= 100;
    ponto->idx -= 1;
  }
  return 0;
}

int move_down(dot_t *ponto)
{
	if (ponto->y_pos != DOWNMOST_POS)
  {
    ponto->y_pos += 150;
    ponto->idx += 5;
  }
  return 0;
}

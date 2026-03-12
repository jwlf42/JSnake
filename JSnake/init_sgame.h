#ifndef INIT_SGAME
#define INIT_SGAME

#include "jconfig.h"

void InitGame();

void InitField(rast_t* spielfeld);

void InitFood(food_t* f);

void InitSnake(snake_t* snake, coordinates_t dir, color_t farbe, int length);

#endif

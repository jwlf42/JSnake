#ifndef INIT_SGAME
#define INIT_SGAME

#include "jconfig.h"

void InitGame();

void InitField(rast_t* spielfeld);

void InitFood(food* f);

void InitSnake(snakes* snake, coordinates dir, color_t farbe, int length);

#endif

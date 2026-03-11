#ifndef INIT_SGAME
#define INIT_SGAME

#include "jconfig.h"

void InitGame();

void InitField(field* spielfeld);

void InitFood(food* f);

void InitSnake(snakes* snake, coordinates dir, color farbe, int length);

#endif

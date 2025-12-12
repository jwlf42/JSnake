

/*
*   Headerdatei alle funktionen der gammelogik
*/

#ifndef FUNCTION_SNAKE_H
#define FUNCTION_SNAKE_H

#include "jconfig.h"

void InitGame();

void InitSnake(Snake* snake, color farbe, int length);

void UpdateAnimation();

void UpdateLogic();

void GenFood();

void SaveScore();

void LoadHighscore();

#endif



#ifndef FUNCTION_SNAKE_H
#define FUNCTION_SNAKE_H

#include "jconfig.h"

void InitGame();

void InitSnake(snakes* snake, coordinates dir, color farbe, int length);

int InputControl(coordinates* dir);

void UpdateAnimation();

void UpdateLogic();

void GenFood(food* food);

void SaveScore();

void LoadHighscore();

#endif


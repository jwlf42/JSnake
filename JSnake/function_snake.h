
#ifndef FUNCTION_SNAKE_H
#define FUNCTION_SNAKE_H

#include "jconfig.h"

int InputControl(coordinates_t* dir);

void UpdateAnimation(snake_t* snake);

void UpdateLogic();

void GenFood(food_t* food);

#endif


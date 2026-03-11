
#ifndef FUNCTION_SNAKE_H
#define FUNCTION_SNAKE_H

#include "jconfig.h"

int InputControl(coordinates* dir);

void UpdateAnimation();

void UpdateLogic();

void GenFood(food* food);

#endif


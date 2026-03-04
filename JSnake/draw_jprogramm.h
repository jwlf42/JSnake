#ifndef DRAW_JPROGRAMM_H
#define DRAW_JPROGRAMM_H

#include "jconfig.h"

void InitField();

void DrawGame();

void DrawStaticGame();

void DrawRectFill(coordinates size, int x, int y, color farbe, int w);

void DrawRect(coordinates size, int x, int y, color farbe, int w);

void PlaceTextDynamic(int x, int y, char* text, richtung modus);

#endif

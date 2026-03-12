#ifndef DRAW_JPROGRAMM_H
#define DRAW_JPROGRAMM_H

#include "jconfig.h"

void DrawGame();

void DrawStaticGame();

void DrawRectFill(coordinates size, int x, int y, color_t farbe, int w);

void DrawRect(coordinates size, int x, int y, color_t farbe, int w);

void DrawRectFillRast(coordinates size, coordinates pos, color_t farbe, int w);

void DrawRectRast(coordinates size, coordinates pos, color_t farbe, int w);

void PlaceTextDynamic(int x, int y, char* text, richtung modus);

coordinates RastToPix(coordinates pos);

#endif

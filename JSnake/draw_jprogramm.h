#ifndef DRAW_JPROGRAMM_H
#define DRAW_JPROGRAMM_H

#include "jconfig.h"

void DrawGame();

void DrawStaticGame();

void DrawRectFill(coordinates_t size, int x, int y, color_t farbe, int w);

void DrawRect(coordinates_t size, int x, int y, color_t farbe, int w);

void DrawRectFillRast(rast_t rast, int w);

void DrawRectRast(rast_t, int w);

void PlaceTextDynamic(int x, int y, char* text, richtung_t modus);

coordinates_t RastToPix(coordinates_t pos);

#endif

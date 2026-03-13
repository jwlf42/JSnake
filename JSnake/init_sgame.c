/*
  Projektname:                 JSnake
  externe Schnittstelle:       Grafikausgabe mit Hilfe von "Simple Draw"
  Simple Draw:                 erstellt von Prof. Dr. Martin Gräfe
  Datei:                       init_sgame.c
  Autor:                       Joel Wölfel
*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <time.h>
#include "init_sgame.h"
#include "jbutton.h"
#include "function_snake.h"
#include "jfile.h"
#include "draw_jprogramm.h"



/******************************************************
   Spiel Initialisierung

*******************************************************/
void InitGame()
{
    score = 0;

    InitField(&standardfield);
    InitGameButtons();
    InitSnake(&Jsnake, (coordinates_t) { 0, 0 }, controlColor, 1);
    InitFood(&apple);
    LoadHighscore();
    srand(time(NULL));
    GenFood(&apple);
    DrawStaticGame();
    DrawGame();
}



/*******************************************************
  Speilfeld mit Strichstäre genau auf Raster ausrichten
  Schlange genau an grenzen läuft
*******************************************************/
void InitField(rast_t* spielfeld)
{
    //Ausrichtung mit Strichstärke berücksichtigen (Strichstärke = Rast)
    spielfeld->pos.x = Rand_Links + (Rast / 2);
    spielfeld->pos.y = Rand_Oben + (Rast / 2);
    spielfeld->rastsize.x = FIELD_WIDTH * Rast;
    spielfeld->rastsize.y = FIELD_HEIGHT * Rast;
    spielfeld->draw = 1;

    return;
}



void InitFood(food_t* f)
{
    f->value = 1;
    f->rast.draw = 0;
    f->rast.rastsize.x = Rast - 8;
    f->rast.rastsize.y = Rast - 8;
    f->rast.color = COLOR_APPLERED;
}



/******************************************************
   Schlange initialisierung Übergabe als Pointer
   Funktion soll später mehrere Objekte initialisieren
*******************************************************/
void InitSnake(snake_t* snake, coordinates_t dir, color_t farbe, int length)
{
    int i;
    snake->length = length;
    snake->dir = dir;

    for (i = 0; i < length; i++)
    {
        snake->seg[i].pos.x = ((FIELD_WIDTH / 2) + Rand_Links / Rast) - (dir.x * i);
        snake->seg[i].pos.y = ((FIELD_HEIGHT / 2) + Rand_Oben / Rast) - (dir.y * i);
        snake->seg[i].offset.x = 0;
        snake->seg[i].offset.y = 0;
        snake->seg[i].color = farbe;
    }

    snake->progress = 0;
    snake->target.pos.x = snake->seg[0].pos.x + snake->dir.x;
    snake->target.pos.y = snake->seg[0].pos.y + snake->dir.y;
}

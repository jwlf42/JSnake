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
  damit Schlange genau an grenzen läuft
*******************************************************/
void InitField(rast_t* spielfeld)
{
    //Ausrichtung mit Strichstärke berücksichtigen (Strichstärke = Rast)
    spielfeld->pos.x = Rand_Links + (RAST / 2);
    spielfeld->pos.y = Rand_Oben + (RAST / 2)-1;
    spielfeld->offset.x = (RAST / 2);
    spielfeld->offset.y = (RAST / 2);
    spielfeld->size.x = FIELD_WIDTH*RAST+1;
    spielfeld->size.y = FIELD_HEIGHT*RAST;
    spielfeld->draw = 1;

    return;
}


/*******************************************************
  Essen Initialisierung ueber Zeiger 

*******************************************************/
void InitFood(food_t* f)
{
    f->value = 1;
    f->rast.draw = 0;
    f->rast.size.x = RAST - 8;
    f->rast.size.y = RAST - 8;
    f->rast.offset.x = 4;
    f->rast.offset.y = 8;
    f->rast.color = COLOR_APPLERED;
}



/******************************************************
   Schlange Initialisierung Übergabe als Pointer
   Funktion soll später mehrere Objekte initialisieren
*******************************************************/
void InitSnake(snake_t* snake, coordinates_t dir, color_t farbe, int length)
{
    int i;
    snake->length = length;
    snake->dir = dir;

    for (i = 0; i < length; i++)
    {
        snake->seg[i].rast.size = RASTSIZE;
        snake->seg[i].rast.pos.x = ((FIELD_WIDTH / 2) + Rand_Links / RAST) - (dir.x * i);
        snake->seg[i].rast.pos.y = ((FIELD_HEIGHT / 2) + Rand_Oben / RAST) - (dir.y * i);
        snake->seg[i].rast.offset.x = 0;
        snake->seg[i].rast.offset.y = 0;
        snake->seg[i].dir = snake->dir;
        snake->seg[i].rast.color = farbe;
    }

    snake->progress = 0;
    snake->target.pos.x = snake->seg[0].rast.pos.x + snake->dir.x;
    snake->target.pos.y = snake->seg[0].rast.pos.y + snake->dir.y;
}

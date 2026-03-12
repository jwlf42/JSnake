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
    InitSnake(&Jsnake, (coordinates) { 0, 0 }, controlColor, 1);
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



void InitFood(food* f)
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
void InitSnake(snakes* snake, coordinates dir, color_t farbe, int length)
{
    int i;
    snake->length = length;

    snake->target.direction.x = dir.x;
    snake->target.direction.y = dir.y;

    for (i = 0; i < MAX_SEG; i++)
    {
        snake->seg[i].position.x = ((FIELD_WIDTH / 2) + Rand_Links / Rast) - (dir.x * i);
        snake->seg[i].position.y = ((FIELD_HEIGHT / 2) + Rand_Oben / Rast) - (dir.y * i);
        snake->seg[i].direction.x = 0;
        snake->seg[i].direction.y = 0;
        snake->seg[i].farbe = farbe;
    }

    snake->pixtail.x = snake->seg[snake->length - 1].position.x * Rast;
    snake->pixtail.y = snake->seg[snake->length - 1].position.y * Rast;

    snake->headpix.x = snake->seg[0].position.x * Rast;
    snake->headpix.y = snake->seg[0].position.y * Rast;

    snake->target.position.x = snake->seg[0].position.x;
    snake->target.position.y = snake->seg[0].position.y;
}

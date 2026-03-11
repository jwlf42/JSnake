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
void InitField(field* spielfeld)
{
    //Ausrichtung mit Strichstärke berücksichtigen (Strichstärke = Rast)
    spielfeld->position.x = Rand_Links;
    spielfeld->position.y = Rand_Oben;
    spielfeld->size.x = FIELD_WIDTH * Rast;
    spielfeld->size.y = FIELD_HEIGHT * Rast;
    spielfeld->position.x += (Rast / 2);
    spielfeld->position.y -= (Rast / 2);
    spielfeld->draw = 1;

    return;
}



void InitFood(food* f)
{
    f->value = 1;
    f->active = 0;
    f->size.x = Rast - 8;
    f->size.y = Rast - 8;
    f->farbe = COLOR_APPLERED;
}



/******************************************************
   Schlange initialisierung Übergabe als Pointer
   Funktion soll später mehrere Objekte initialisieren
*******************************************************/
void InitSnake(snakes* snake, coordinates dir, color farbe, int length)
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

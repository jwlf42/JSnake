/*
  Projektname:                 JSnake
  externe Schnittstelle:       Grafikausgabe mit Hilfe von "Simple Draw"
  Simple Draw:                 erstellt von Prof. Dr. Martin Gräfe
  Datei:                       function_snake.c
  Autor:                       Joel Wölfel
*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <time.h>
#include "init_sgame.h"
#include "function_snake.h"
#include "simple_draw.h"



/******************************************************
  Animationsupadate, Berechnung offset

*******************************************************/
void UpdateAnimation(snake_t *snake)
{
    snake->progress += SPEED;

    snake->seg[0].rast.offset.x = (snake->seg[0].dir.x) * snake->progress;
    snake->seg[0].rast.offset.y = (snake->seg[0].dir.y) * snake->progress;

    snake->seg[snake->length - 1].rast.size.x = RAST - abs(snake->seg[snake->length - 1].dir.x) * (RAST - snake->progress);
    snake->seg[snake->length - 1].rast.size.y = RAST - abs(snake->seg[snake->length - 1].dir.y) * (RAST - snake->progress);

    snake->seg[snake->length - 1].rast.offset.x = (snake->seg[snake->length - 1].dir.x < 0) * (RAST - snake->progress);
    snake->seg[snake->length - 1].rast.offset.y = (snake->seg[snake->length - 1].dir.y < 0) * (RAST - snake->progress);

    return;
  }



/******************************************************
    Funktion update Rasterlogik und steuerung.
    Kollisionsprüfung und wachstumsprüfung
*******************************************************/
void UpdateLogic(snake_t* snake)
{
    int i;

    if (snake->progress >= RAST)
    {
        for (i = snake->length - 1; i > 0; i--)
        {
            snake->seg[i] = snake->seg[i - 1];
        }

        snake->seg[snake->length - 1].rast.color = COLOR_WHITE;
        snake->seg[0].rast.pos = snake->target.pos;
        snake->progress = 0;
    }

    InputControl(&snake->dir);

    if (snake->seg[0].rast.pos.x == snake->target.pos.x &&
        snake->seg[0].rast.pos.y == snake->target.pos.y)
    {
        snake->seg[0].dir = snake->dir;

        snake->target.pos.x = snake->seg[0].rast.pos.x + snake->dir.x;
        snake->target.pos.y = snake->seg[0].rast.pos.y + snake->dir.y;

        if (snake->target.pos.x <= 2 || snake->target.pos.x >= FIELD_WIDTH + 2 || snake->target.pos.y <= 8 || snake->target.pos.y >= FIELD_HEIGHT + 8)
        {
            gamestate = gameover;
        }

        for (i = 1; i <= snake->length - 1; i++)
        {
            if (snake->target.pos.x == snake->seg[i].rast.pos.x && snake->target.pos.y == snake->seg[i].rast.pos.y)
            {
                gamestate = gameover;
            }
        }

        if (snake->seg[0].rast.pos.x == apple.rast.pos.x && snake->seg[0].rast.pos.y == apple.rast.pos.y)
        {
            snake->length += apple.value;

            for (i = 1; i <= apple.value; i++)
            {
                snake->seg[snake->length - i] = snake->seg[snake->length - apple.value - 1];
            }

            GenFood(&apple);
            score += apple.value;

            if (score > highscore)
                highscore = score;
        }
    }

    return;
}


/******************************************************
    Steuerung mit "W,A,S,D" Tasten. Gibt 0 zurück, wenn 
    keine Taste gedrückt oder die gegenteilige gedrückt wurde
*******************************************************/
int InputControl(coordinates_t *dir)
{
    coordinates_t current = *dir;
    int taste;

    // Steuerung mit "W,S,A,D" Tasten 
    taste = GetKey();

    switch (taste)
    {
    case 87: //W
        current.x = 0;
        current.y = -1;
        break;
    case 83://S
        current.x = 0;
        current.y = 1;
        break;
    case 65: //A
        current.x = -1;
        current.y = 0;
        break;
    case 68: //D
        current.x = 1;
        current.y = 0;
        break;
    }

    if (current.x != -dir->x || current.y != -dir->y)
    {
        *dir = current;
        return taste;
    }
    return 0;
}



/******************************************************
    Funktion Food für Schlange generieren
    zufallszahl im feld und nicht auf der Schlange
*******************************************************/
void GenFood(food_t *food)
{ 
    int food_x, food_y;
    int collesion=0;
    int i;
 
    do
    {
        // Zufaellige X-Position:
        food_x = (rand() % (FIELD_WIDTH-1))+3;

        // Zufaellige Y-Position:
        food_y = (rand() % (FIELD_HEIGHT-1)) + 9;

        collesion = 0;

        for (i = 0; i <= Jsnake.length - 1; i++)
            if (food_x == Jsnake.seg[i].rast.pos.x && food_y == Jsnake.seg[i].rast.pos.y)
                collesion = 1;

    } while (collesion == 1);

    food->rast.draw = 1;
    food->rast.pos.x = food_x;
    food->rast.pos.y = food_y;

    return;
}
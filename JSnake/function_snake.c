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

snake_t Jsnake;
rast_t standardfield;
food_t apple;
color_t controlColor;

int score=0;
int highscore=0;
int last_score=-1;
int last_highscore=-1;


/******************************************************
  Animations update pro frame und berechnung.
  prüfung ob schlange zum raster animiert wurde
*******************************************************/
void UpdateAnimation()
{
    int i;

    Jsnake.headpix.x += (Jsnake.target.pos.x - Jsnake.seg[0].pos.x) * SPEED;
    Jsnake.headpix.y += (Jsnake.target.pos.y - Jsnake.seg[0].pos.y) * SPEED;

    Jsnake.pixtail.x += (Jsnake.seg[Jsnake.length - 1].pos.x - Jsnake.seg[Jsnake.length - 2].pos.x) * SPEED;
    Jsnake.pixtail.y += (Jsnake.seg[Jsnake.length - 1].pos.y - Jsnake.seg[Jsnake.length - 2].pos.y) * SPEED;
    
    if (Jsnake.headpix.x == Jsnake.target.pos.x * Rast && Jsnake.headpix.y == Jsnake.target.pos.y * Rast)
    {   
        for (i = Jsnake.length - 1; i > 0; i--)
        {
            Jsnake.seg[i] = Jsnake.seg[i - 1];
        }  
        Jsnake.seg[0].pos = Jsnake.target.pos;
    }
}



/******************************************************
    Funktion update Rasterlogik und steuerung.
    Kollisionsprüfung und wachstumsprüfung
*******************************************************/
void UpdateLogic()
{
    int i;
    
    InputControl(&Jsnake.dir);

    if (Jsnake.seg[0].pos.x == Jsnake.target.pos.x && Jsnake.seg[0].pos.y == Jsnake.target.pos.y)
    {
        //Jsnake.seg[0].direction = Jsnake.target.direction;
        
        Jsnake.target.pos.x = Jsnake.seg[0].pos.x + Jsnake.dir.x;
        Jsnake.target.pos.y = Jsnake.seg[0].pos.y + Jsnake.dir.y;

        //Schwanz verschiebung für schönere animation
        /*if (Jsnake.seg[Jsnake.length - 1].direction.x != Jsnake.seg[Jsnake.length - 2].direction.x || Jsnake.seg[Jsnake.length - 1].direction.y != Jsnake.seg[Jsnake.length - 2].direction.y)
        {
            Jsnake.seg[Jsnake.length - 1].direction = Jsnake.seg[Jsnake.length - 2].direction;
            
            Jsnake.seg[Jsnake.length - 1].position = Jsnake.seg[Jsnake.length - 2].position;

            Jsnake.pixtail.x = Jsnake.seg[Jsnake.length - 1].position.x * Rast - Jsnake.seg[Jsnake.length - 1].direction.x * Rast;
            Jsnake.pixtail.y = Jsnake.seg[Jsnake.length - 1].position.y * Rast - Jsnake.seg[Jsnake.length - 1].direction.y * Rast;
        }*/

        if (Jsnake.seg[Jsnake.length - 1].pos.x <= 3 || Jsnake.seg[Jsnake.length - 1].pos.x >= FIELD_WIDTH+1 || Jsnake.seg[Jsnake.length - 1].pos.y <= 9 || Jsnake.seg[Jsnake.length - 1].pos.y >= FIELD_HEIGHT + 7)
        {
            standardfield.draw = 1;
        }

        if (Jsnake.target.pos.x <= 2 || Jsnake.target.pos.x >= FIELD_WIDTH+2 || Jsnake.target.pos.y <= 8 || Jsnake.target.pos.y >= FIELD_HEIGHT + 8)
        { 
            gamestate=gameover;
        }

        for ( i = 1; i < Jsnake.length - 1; i++)
        {
            if (Jsnake.target.pos.x == Jsnake.seg[i].pos.x && Jsnake.target.pos.y == Jsnake.seg[i].pos.y)
            {
                gamestate = gameover;
            }
        }
        
        if (Jsnake.seg[0].pos.x == apple.rast.pos.x && Jsnake.seg[0].pos.y == apple.rast.pos.y)
        {
            Jsnake.length++;
            GenFood(&apple);
            score += 10;
            
            if (score > highscore)
                highscore = score;
        }  
    }
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
        food_x = (rand() % FIELD_WIDTH-1) + 3;

        // Zufaellige Y-Position:
        food_y = (rand() % (FIELD_HEIGHT-1)) + 9;

        collesion = 0;

        for (i = 1; i <= Jsnake.length - 1; i++)
            if (food_x == Jsnake.seg[i].pos.x && food_y == Jsnake.seg[i].pos.y)
                collesion = 1;

    } while (collesion == 1);

    food->rast.draw = 1;
    food->rast.pos.x = food_x;
    food->rast.pos.y = food_y;
}
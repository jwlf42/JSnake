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

snakes Jsnake;
field standardfield;
food apple;
color controlColor;

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

    Jsnake.headpix.x += Jsnake.seg[0].direction.x * SPEED;
    Jsnake.headpix.y += Jsnake.seg[0].direction.y * SPEED;

    Jsnake.pixtail.x += Jsnake.seg[Jsnake.length-1].direction.x * SPEED;
    Jsnake.pixtail.y += Jsnake.seg[Jsnake.length-1].direction.y * SPEED;
    
    if (Jsnake.headpix.x == Jsnake.target.position.x * Rast && Jsnake.headpix.y == Jsnake.target.position.y * Rast)
    {   
        for (i = Jsnake.length - 1; i > 0; i--)
        {
            Jsnake.seg[i] = Jsnake.seg[i - 1];
        }  
        Jsnake.seg[0].position = Jsnake.target.position;
    }
}



/******************************************************
    Funktion update Rasterlogik und steuerung.
    Kollisionsprüfung und wachstumsprüfung
*******************************************************/
void UpdateLogic()
{
    int i;
    
    InputControl(&Jsnake.target.direction);

    if (Jsnake.seg[0].position.x == Jsnake.target.position.x && Jsnake.seg[0].position.y == Jsnake.target.position.y)
    {
        Jsnake.seg[0].direction = Jsnake.target.direction;
        
        Jsnake.target.position.x = Jsnake.seg[0].position.x + Jsnake.seg[0].direction.x;
        Jsnake.target.position.y = Jsnake.seg[0].position.y + Jsnake.seg[0].direction.y;

        //Schwanz verschiebung für schönere animation
        if (Jsnake.seg[Jsnake.length - 1].direction.x != Jsnake.seg[Jsnake.length - 2].direction.x || Jsnake.seg[Jsnake.length - 1].direction.y != Jsnake.seg[Jsnake.length - 2].direction.y)
        {
            Jsnake.seg[Jsnake.length - 1].direction = Jsnake.seg[Jsnake.length - 2].direction;
            
            Jsnake.seg[Jsnake.length - 1].position = Jsnake.seg[Jsnake.length - 2].position;

            Jsnake.pixtail.x = Jsnake.seg[Jsnake.length - 1].position.x * Rast - Jsnake.seg[Jsnake.length - 1].direction.x * Rast;
            Jsnake.pixtail.y = Jsnake.seg[Jsnake.length - 1].position.y * Rast - Jsnake.seg[Jsnake.length - 1].direction.y * Rast;
        }

        if (Jsnake.seg[Jsnake.length - 1].position.x <= 3 || Jsnake.seg[Jsnake.length - 1].position.x >= FIELD_WIDTH+1 || Jsnake.seg[Jsnake.length - 1].position.y <= 9| Jsnake.seg[Jsnake.length - 1].position.y >= FIELD_HEIGHT + 7)
        {
            standardfield.draw = 1;
        }

        if (Jsnake.target.position.x <= 2 || Jsnake.target.position.x >= FIELD_WIDTH+2 || Jsnake.target.position.y <= 8 || Jsnake.target.position.y >= FIELD_HEIGHT + 8)
        { 
            gamestate=gameover;
        }

        for ( i = 1; i < Jsnake.length - 1; i++)
        {
            if (Jsnake.target.position.x == Jsnake.seg[i].position.x && Jsnake.target.position.y == Jsnake.seg[i].position.y)
            {
                gamestate = gameover;
            }
        }
        
        if (Jsnake.seg[0].position.x == apple.rastpos.x && Jsnake.seg[0].position.y == apple.rastpos.y)
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
int InputControl(coordinates *dir)
{
    coordinates current = *dir;
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
void GenFood(food *food)
{ 
    int food_x, food_y;
    int collesion=0;
    int i;
    coordinates size = { Rast - 6,Rast - 6 };
 
    do
    {
        // Zufaellige X-Position:
        food_x = (rand() % FIELD_WIDTH) + 3;

        // Zufaellige Y-Position:
        food_y = (rand() % (FIELD_HEIGHT-1)) + 9;

        collesion = 0;

        for (i = 1; i <= Jsnake.length - 1; i++)
            if (food_x == Jsnake.seg[i].position.x && food_y == Jsnake.seg[i].position.y)
                collesion = 1;

    } while (collesion == 1);

    food->active = 1;
    food->rastpos.x = food_x;
    food->rastpos.y = food_y;
}
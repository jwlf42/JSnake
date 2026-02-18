/*
  Projektname:                 JSnake
  externe Schnittstelle:       Grafikausgabe mit Hilfe von "Simple Draw"
  Simple Draw:                 erstellt von Prof. Dr. Martin Gräfe
  Datei:                       function_snake.c
  Autor:                       Joel Wölfel
*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <windows.h>
#include <time.h>
#include "simple_draw.h"
#include "draw_jprogramm.h"
#include "function_snake.h"
#include "jprogramm.h"

snakes Jsnake;
field spielfeld;
food apple;
color controlColor;

int score;
int highscore=0;
int last_score;
int last_highscore;



/******************************************************
   Spiel Initialisierung

*******************************************************/
void InitGame()
{   
    score = 0;
    last_score = -1;
    last_highscore = -1;
    apple.value = 1;
    apple.active = 0;
    apple.size.x = Rast-8;
    apple.size.y = Rast-8;
    apple.farbe = COLOR_APPLERED;

    Rand_Links = 2 * Rast;
    Rand_Oben = 8 * Rast;

    InitField();
    InitSnake(&Jsnake, (coordinates) { 0, 0 }, controlColor, 1); 
    LoadHighscore();
    GenFood(&apple);
    srand(time(NULL));
    DrawStaticGame();
    DrawGame();
}



/******************************************************
   Schlange initialisierung Übergabe als Pointer 
   Funktion soll später mehrere Objekte initialisieren
*******************************************************/
void InitSnake(snakes *snake, coordinates dir, color farbe, int length)
{
    int i;
    snake->length = length;

    snake->target.direction.x=dir.x;
    snake->target.direction.y=dir.y;

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

    snake->target.farbe = COLOR_SNAKEGREEN;
}



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

        if (Jsnake.target.position.x < 2 || Jsnake.target.position.x > FIELD_WIDTH + 1 || Jsnake.target.position.y <= 7 || Jsnake.target.position.y >= FIELD_HEIGHT + 8)
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
        food_x = (rand() % FIELD_WIDTH) + 2;

        // Zufaellige Y-Position:
        food_y = (rand() % FIELD_HEIGHT) + 8;

        collesion = 0;

        for (i = 1; i <= Jsnake.length - 1; i++)
            if (food_x == Jsnake.seg[i].position.x && food_y == Jsnake.seg[i].position.y)
                collesion = 1;

    } while (collesion == 1);

    food->active = 1;
    food->rastpos.x = food_x;
    food->rastpos.y = food_y;
}



/******************************************************
   Binaerdatei für Highscore lesen oder erstellen

*******************************************************/
void LoadHighscore()
{
    FILE* datei;
    int readscore=highscore;
    
    if ((datei = fopen("snakecore", "rb")) == NULL)
    {
        fprintf(stderr, "\nDatei konnte nicht geöffnet werden\n");
        fprintf(stderr, "\nDatei wird neu erstellt\n");

        if ((datei = fopen("snakecore", "wb")) == NULL)
            fprintf(stderr, "\nNeue Datei kann nicht erstellt werden\n");
        else
        {
            if ((fwrite(&readscore, sizeof(int), 1, datei)) != 1)
            {
                fprintf(stderr, "\nNeue Datei kann nicht beschrieben werden\n");
            }
            fclose(datei);
        }
    }
    else
    { 
        if (fread(&readscore, sizeof(int), 1, datei) == 1)
        {
            highscore = readscore;
        }
        else
            fprintf(stderr, "\nDaeti konnte nicht gelesen werden\n");
        
        fclose(datei);
    }
}



/******************************************************
   Highscore speichern

*******************************************************/
void SaveScore()
{
    FILE* datei;
    int writescore=highscore;

    if ((datei = fopen("snakecore", "r+b")) == NULL)
    {
        fprintf(stderr, "\nHighscore-Datei kann nicht zum speichern geoffnet werden\n");
    }
    else
    {
        if((fwrite(&writescore, sizeof(int), 1, datei))!=1)
        {
            fprintf(stderr, "\nHighscore kann nicht gespeichert werden\n");
        }
        fclose(datei);
    }
}


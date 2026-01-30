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


Snake Jsnake;
coordinates food;
color controlColor;

int score;
int highscore=0;
int last_score;
int last_highscore;
int start_snake;


/******************************************************
   Spiel Initialisierung

*******************************************************/
void InitGame()
{   
    score = 0;
    last_score = -1;
    last_highscore = -1;
    start_snake = 0;

    InitSnake(&Jsnake, controlColor, 3);

    srand(time(NULL));

    DrawStaticGame();
}



/******************************************************
   Schlange initialisierung Übergabe als Pointer 
   Funktion soll später mehrere Objekte initialisieren
*******************************************************/
void InitSnake(Snake *snake, color farbe, int length)
{
    int i;
    snake->length = length;

    snake->target.direction.x=0;
    snake->target.direction.y=0;

    for (i = 0; i < MAX_SEG; i++)
    {
        snake->seg[i].position.x = ((FELD_WIDTH / 2) + Rand_Links/Rast)-i;
        snake->seg[i].position.y = ((FELD_HEIGHT / 2) + Rand_Oben/Rast);
        snake->seg[i].direction.x = 0;
        snake->seg[i].direction.y = 0;
        snake->seg[i].farbe = COLOR_WHITE;
    }

    for (i = 0; i < snake->length; i++)
    {
        //snake->seg[i].direction.x = snake->target.direction.x;
        //snake->seg[i].direction.y = snake->target.direction.y;
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

    Jsnake.headpix.x += Jsnake.seg[0].direction.x * SPEED;
    Jsnake.headpix.y += Jsnake.seg[0].direction.y * SPEED;

    Jsnake.pixtail.x += Jsnake.seg[Jsnake.length-1].direction.x * SPEED;
    Jsnake.pixtail.y += Jsnake.seg[Jsnake.length-1].direction.y * SPEED;
    
    if (Jsnake.headpix.x == Jsnake.target.position.x * Rast && Jsnake.headpix.y == Jsnake.target.position.y * Rast)
    {   
        for (int i = Jsnake.length - 1; i > 0; i--)
        {
             Jsnake.seg[i] = Jsnake.seg[i - 1];
        }  
        Jsnake.seg[0].position = Jsnake.target.position;
        Jsnake.seg[Jsnake.length - 1].farbe = COLOR_WHITE;
    }
}



/******************************************************
    Funktion update Rasterlogik und steuerung.
    Kollisionsprüfung und wachstumsprüfung
*******************************************************/
void UpdateLogic()
{
    int taste, i;

        // Steuerung mit "W,S,A,D" Tasten 
        taste = GetKey();

        switch (taste)
        {
        case 87: //W
            if (Jsnake.target.direction.y != 1)
            {
                Jsnake.target.direction.y = -1;
                Jsnake.target.direction.x = 0;
                start_snake = 1;
            }
            break;
        case 83://S
            if (Jsnake.target.direction.y != -1)
            {
                Jsnake.target.direction.y = 1;
                Jsnake.target.direction.x = 0;
                start_snake = 1;
            }
            break;
        case 65: //A
            if (Jsnake.target.direction.x != 1)
            {
                Jsnake.target.direction.y = 0;
                Jsnake.target.direction.x = -1;
                start_snake = 1;
            }
            break;
        case 68: //D
            if (Jsnake.target.direction.x != -1)
            {
                Jsnake.target.direction.y = 0;
                Jsnake.target.direction.x = 1;
                start_snake = 1;
            }
            break;
        }

        if(start_snake==0)
            InitSnake(&Jsnake, controlColor, 3);
    
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

        if (Jsnake.target.position.x < 2 || Jsnake.target.position.x > FELD_WIDTH + 1 || Jsnake.target.position.y <= 7 || Jsnake.target.position.y >= FELD_HEIGHT + 8)
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
        
        if (Jsnake.seg[0].position.x == food.x && Jsnake.seg[0].position.y == food.y)
        {
            Jsnake.length++;
            GenFood();
            score += 10;
            
            if (score > highscore)
                highscore = score;
        }  
    }
}



/******************************************************
    Funktion Food für Schlange generieren
    zufallszahl im feld und nicht auf der Schlange
*******************************************************/
void GenFood()
{ 
    int food_x, food_y;
    int foodpix_x, foodpix_y;
    int collesion=0;
    int i;
    color apple = COLOR_APPLERED;
    
    CheckDDE();

    do
    {
        // Zuf�llige X-Position:
        food_x = (rand() % FELD_WIDTH) + 2;

        // Zuf�llige Y-Position:
        food_y = (rand() % FELD_HEIGHT) + 8;

        collesion = 0;

        for (i = 1; i <= Jsnake.length - 1; i++)
            if (food_x == Jsnake.seg[i].position.x && food_y == Jsnake.seg[i].position.y)
                collesion = 1;

    } while (collesion == 1);

    food.x = food_x;
    food.y = food_y;

    foodpix_x = food.x * Rast;
    foodpix_y = food.y * Rast;
    
    DrawBlock(Rast-6, foodpix_x+3, foodpix_y+6, apple, 2);

    //Apfelstiel
    SetPen(101, 67, 33, 5);
    DrawLine(foodpix_x + 12, foodpix_y + 8, foodpix_x + 12, foodpix_y+2);
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


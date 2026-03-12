/*
  Projektname:                 JSnake
  externe Schnittstelle:       Grafikausgabe mit Hilfe von "Simple Draw"
  Simple Draw:                 erstellt von Prof. Dr. Martin Gräfe
  Datei:                       draw_jprogramm.c
  Autor:                       Joel Wölfel
*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include "simple_draw.h"
#include "draw_jprogramm.h"

int Rand_Links;
int Rand_Oben;

const color_t COLOR_WHITE = { 255, 255, 255 };
const color_t COLOR_BLACK = { 0,0,0 };
const color_t COLOR_LIGHTGREEN = { 144, 238, 144 };
const color_t COLOR_DARKGRAY = { 50, 50, 50 };
const color_t COLOR_SNAKEGREEN = { 50, 205, 50 };
const color_t COLOR_APPLERED = { 255, 0, 0 };
const color_t COLOR_HELBLUE = { 173, 216, 230 }; 
const color_t COLOR_LILA = { 186, 85, 211 };     
const color_t COLOR_LIGHTGRAY = { 211, 211, 211 };
const color_t COLOR_DARKBLUE = { 25, 25, 112 };



/******************************************************
    Funktion Zeichnung aller dynamischen Elemnte und

*******************************************************/
void DrawGame()
{
    char sbuffer[20];
    coordinates snakesize = { Rast,Rast };
    coordinates pix;

    if (score != last_score)
    {
        sprintf(sbuffer, "Score: %d", score);
        PlaceTextDynamic((standardfield.rastsize.x + 100), standardfield.pos.y, sbuffer, richtung_L);
        last_score = score;
    }

    if (highscore != last_highscore)
    {
        sprintf(sbuffer, "Highscore %d", highscore);
        PlaceTextDynamic(standardfield.rastsize.x+100, standardfield.pos.y + 24, sbuffer, richtung_L);
        last_highscore = highscore;
    }

    if (apple.rast.draw == 1)
    {
        pix = RastToPix(apple.rast.pos);
        DrawRectFillRast(apple.rast.rastsize, apple.rast.pos, apple.rast.color, 2);
        SetPen(101, 67, 33, 5);
        DrawLine(pix.x + 12, pix.y + 8, pix.x + 12, pix.y + 2);

        apple.rast.draw = 0;
    }

    if (standardfield.draw == 1)
    {
        DrawRect(standardfield.rastsize, standardfield.pos.x, standardfield.pos.y, standardfield.color, Rast);
        standardfield.draw = 0;
    }
    
    //Schlangenblock uebermalen
    //DrawRectFill(snakesize, Jsnake.pixtail.x, Jsnake.pixtail.y, COLOR_WHITE, 2);
    DrawRectFillRast(snakesize, Jsnake.seg[Jsnake.length-1].position, COLOR_WHITE, 2);

    //Schlangenkopf malen
    //DrawRectFill(snakesize, Jsnake.headpix.x, Jsnake.headpix.y, Jsnake.seg[0].farbe, 2);
    DrawRectFillRast(snakesize, Jsnake.seg[0].position, Jsnake.seg[0].farbe, 2);
  
    return;
}



/******************************************************
  Zeichnet ein gefülltes Quadrat in der größe size farbe
  und strichstärke --> beeinflusst die Zeichengeschwindigkeit
*******************************************************/
void DrawRectFill(coordinates size, int x, int y, color_t farbe, int w)
{
    int x_size = x + size.x;
    int y_size = y + size.y;
    int i;

    SetPen(farbe.r, farbe.g, farbe.b, w);

    for (i = y; i < y_size; i += w)
    {
        DrawLine(x, i, x_size, i);
    }

    return;
}



/******************************************************
  Zeichnet ein Quadrat in der größe size farbe und
  Strichstärke w
*******************************************************/
void DrawRect(coordinates size, int x, int y, color_t farbe, int w)
{ 
    SetPen(farbe.r, farbe.g, farbe.b, w);
    MoveTo(x, y);
    DrawTo(x+size.x,y);
    DrawTo(x+size.x,y+size.y);
    DrawTo(x,y+size.y);
    DrawTo(x,y);
}


void DrawRectFillRast(coordinates size, coordinates pos, color_t farbe, int w)
{
    coordinates pix;

    pix = RastToPix(pos);
    DrawRectFill(size, pix.x, pix.y, farbe, w);
}

void DrawRectRast(coordinates size, coordinates pos, color_t farbe, int w)
{
    coordinates pix;

    pix = RastToPix(pos);
    DrawRect(size, pix.x, pix.y, farbe, w);
}



/******************************************************
 Hilfsfunktion Textausrichtung steureung mit typdef enum
 rechts / mittig / links Buendig
*******************************************************/
void PlaceTextDynamic(int x, int y, char* text, richtung modus)
{

    int textWidth = strlen(text) * 7;
    if (modus == richtung_L)
    {
        //printf("\nTextausrichtung modus Links");
        PlaceText(x, y, text);
    }
    if (modus == richtung_M)
    {
        //printf("\nTextausrichtung modus Mitte");
        PlaceText(client.x / 2 - textWidth / 2, y, text);
    }
    if (modus == richtung_R)
    {
        //printf("\nTextaurichtung modus Rechts");
        PlaceText(client.x - x - textWidth, y, text);
    }

    return;
}



/******************************************************
Hilfsfunktion alle statischen elemente in Initialisierung

*******************************************************/
void DrawStaticGame()
{
    PlaceTextDynamic(60, 100, "JSnake", richtung_M);
    PlaceTextDynamic(standardfield.rastsize.x + 100, standardfield.pos.y + 150, "Spielen mit den Tasten \"W, A ,S, D\"", richtung_L);

    standardfield.draw = 1;
    apple.rast.draw = 1;
    last_highscore = -1;
    last_score = -1;

    return;
}

coordinates RastToPix(coordinates pos)
{
    coordinates pix;

    pix.x = pos.x * Rast;
    pix.y = pos.y * Rast;

    return pix;
}
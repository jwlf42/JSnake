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



/******************************************************
    Funktion Zeichnung aller dynamischen Elemnte und

*******************************************************/
void DrawGame()
{
    char sbuffer[20];
    coordinates_t pix;

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
        DrawRectFillRast(apple.rast.rastsize, apple.rast.pos, apple.rast.offset, apple.rast.color, 2);
        SetPen(101, 67, 33, 5);
        DrawLine(pix.x + 12, pix.y + 8, pix.x + 12, pix.y + 2);

        apple.rast.draw = 0;
    }

    if (standardfield.draw == 1)
    {
        DrawRect(standardfield.rastsize, standardfield.pos.x, standardfield.pos.y, standardfield.color, RAST);
        standardfield.draw = 0;
    }
    
    //Schlangenblock uebermalen
    DrawRectFillRast(Jsnake.seg[0].rastsize, Jsnake.seg[Jsnake.length - 1].pos, Jsnake.seg[Jsnake.length - 1].offset, COLOR_WHITE, 2);

    //Schlangenkopf malen
    DrawRectFillRast(Jsnake.seg[Jsnake.length-1].rastsize, Jsnake.seg[0].pos, Jsnake.seg[0].offset, Jsnake.seg[0].color, 2);
  
    return;
}



/******************************************************
  Zeichnet ein gefülltes Quadrat in der größe size farbe
  und strichstärke --> beeinflusst die Zeichengeschwindigkeit
*******************************************************/
void DrawRectFill(coordinates_t size, int x, int y, color_t farbe, int w)
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
void DrawRect(coordinates_t size, int x, int y, color_t farbe, int w)
{ 
    SetPen(farbe.r, farbe.g, farbe.b, w);
    MoveTo(x, y);
    DrawTo(x+size.x,y);
    DrawTo(x+size.x,y+size.y);
    DrawTo(x,y+size.y);
    DrawTo(x,y);
}


void DrawRectFillRast(coordinates_t size, coordinates_t pos, coordinates_t offset, color_t farbe, int w)
{
    coordinates_t pix;

    pix = RastToPix(pos);
    pix.x += offset.x;
    pix.y += offset.y;
    DrawRectFill(size, pix.x, pix.y, farbe, w);
}

void DrawRectRast(coordinates_t size, coordinates_t pos, color_t farbe, int w)
{
    coordinates_t pix;

    pix = RastToPix(pos);
    DrawRect(size, pix.x, pix.y, farbe, w);
}



/******************************************************
 Hilfsfunktion Textausrichtung steureung mit typdef enum
 rechts / mittig / links Buendig
*******************************************************/
void PlaceTextDynamic(int x, int y, char* text, richtung_t modus)
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

coordinates_t RastToPix(coordinates_t pos)
{
    coordinates_t pix;

    pix.x = pos.x * RAST;
    pix.y = pos.y * RAST;

    return pix;
}
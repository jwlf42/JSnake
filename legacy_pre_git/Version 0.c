
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <windows.h>
#include "simple_draw.h"
#include "function_snake.h"

headpos Sposition = { 0,0 };
vec_direction direction;

int screenWidth; 
int screenHeight; 
int clientWidth; 
int clientHeight; 

void PlaceTextDynamic(int x, int y, char* text, trichtung modus);

/******************************************************
   Spiel initialisierung
*******************************************************/
void InitGame()
{  
    int border = GetSystemMetrics(SM_CXFRAME);    // Rahmen links/rechts
    int title = GetSystemMetrics(SM_CYCAPTION);  // Titelleiste oben
    int menu = GetSystemMetrics(SM_CYMENU);     // evtl. Menühöhe


    screenWidth = GetSystemMetrics(SM_CXSCREEN);
    screenHeight = GetSystemMetrics(SM_CYSCREEN);

    clientWidth = screenWidth - 2 * border;     // clientWidth =bildschirmbreite minus rand rechts links
    clientHeight = screenHeight - title - border - menu;

    Sposition.head_x = clientWidth / 2;
    Sposition.head_y = clientHeight / 2;
    direction.vec_x = 20;
    direction.vec_y = 0;

    printf("Breite: %d\n", screenWidth);
    printf("Hoehe: %d", screenHeight);

    printf("\n\nBerechnete breite:%d\n", clientWidth);
    printf("Berechnete hohe:%d\n", clientHeight);

    printf("\n\nVariablen: Border title menu: %d, %d, %d", border, title, menu);


    if (sd_dde_init())
        return;

    ResizeGraphic(0, 0, clientWidth, clientHeight);
}


/******************************************************
    Funktion update Bewegung.
*******************************************************/
void UpdateGame()
{
    brichtung richtung;
    int taste, lasttast = 0;
    char eingabe;

    taste = GetKey();

    switch (taste)
    {
    case 87:
        printf("W");
        direction.vec_y = -10;
        direction.vec_x = 0;
        break;
    case 83:
        printf("S");
        direction.vec_y = 10;
        direction.vec_x = 0;
        break;
    case 65:
        printf("A");
        direction.vec_y = 0;
        direction.vec_x = -10;
        break;
    case 68:
        printf("D");
        direction.vec_y = 0;
        direction.vec_x = 10;
        break;
    }

    Sposition.head_x = Sposition.head_x + direction.vec_x;
    Sposition.head_y = Sposition.head_y + direction.vec_y;
    

    printf("\nAscii code Taste:%d", taste);
}


/******************************************************
    Funktion zur zeichnung Des spielFeldes und allen Elementen
*******************************************************/
void Draw_Sgame()
{
    trichtung  modus;
    int x1 = 20, y1 = 150, x2 = clientWidth - 250, y2 = clientHeight - 70;
    int Aussprung_y = Sposition.head_y+ 20;
    int Aussprung_x = (clientWidth / 2) + 10;
    int Y_Lauf = Sposition.head_y;
    int X_Lauf = Sposition.head_y;
    int zaehler_x=0, zaehler_y=0;

    
    ClearGraphic();
    SetPen(0, 0, 0, 5);

    PlaceTextDynamic(40,100, "JSnake", richtung_M);
    PlaceTextDynamic(60, 150, "Highscore",richtung_R);
   
    //Spielfeld
    MoveTo(x1, y1);
    DrawTo(x2, y1);
    DrawTo(x2, y2);
    DrawTo(x1, y2);
    DrawTo(x1, y1);

    printf("\n\nbefor clientWidth: %d ", clientWidth);
    printf("\nbefor Aussprung_x: %d", Aussprung_x);

    //Schlangenkopf
    SetPen(50, 205, 50, 1);

    for (Y_Lauf; Y_Lauf < Aussprung_y; Y_Lauf++)
    {
        zaehler_y++;
        DrawLine(Sposition.head_x - 10, Y_Lauf, Sposition.head_x + 10, Y_Lauf);
    }

    printf("\n\nAusgabe nach schleife clientwidth:%d\nclientHeight:%d\n\n", clientWidth, clientHeight);
    printf("\n\nzaehler_x:%d", zaehler_x);
    printf("\nzaehler_y:%d", zaehler_y);
}


/******************************************************
Text Ausrichtung steureung mit typdef enum
rechts / mittig / links Bündig
*******************************************************/
void PlaceTextDynamic(int x, int y, char* text, trichtung modus)
{
    int textWidth = strlen(text) * 5;
    if (modus == richtung_L)
    {
        printf("\nTextausrichtung modus Links");
        PlaceText(x, y, text);
    }
    if (modus == richtung_M)
    {
        printf("\nTextausrichtung modus Mitte");
        PlaceText(clientWidth / 2 - textWidth / 2, y, text);
    }
    if (modus == richtung_R)
    {
        printf("\nTextaurichtung modus Rechts");
        PlaceText(clientWidth - x - textWidth, y, text);
    }
}

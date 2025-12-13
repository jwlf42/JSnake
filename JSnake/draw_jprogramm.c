/*
  Projektname:                 JSnake
  externe Schnittstelle:       Grafikausgabe mit Hilfe von "Simple Draw"
  Simple Draw:                 erstellt von Prof. Dr. Martin Gräfe
  Datei:                       draw_jprogramm.c
  Autor:                       Joel Wölfel
*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <windows.h>
#include "simple_draw.h"
#include "draw_jprogramm.h"



int Pixel_Breite;
int Pixel_Hoehe;
int Rand_Links;
int Rand_Oben;
int field_x1, field_y1, field_x2, field_y2;

const color COLOR_WHITE = { 255, 255, 255 };
const color COLOR_LIGHTGREEN = { 144, 238, 144 };
const color COLOR_DARKGRAY = { 50, 50, 50 };
const color COLOR_SNAKEGREEN = { 50, 205, 50 };
const color COLOR_APPLERED = { 255, 0, 0 };
const color COLOR_HELBLUE = { 173, 216, 230 };  // hellblau
const color COLOR_LILA = { 186, 85, 211 };      // lila
const color COLOR_LIGHTGRAY = { 211, 211, 211 };
const color COLOR_DARKBLUE = { 25, 25, 112 };




/*******************************************************
  Üpferprüft ob die Verbindung zu Simple Draw steht.
  gibt eine Windows fehlermeldung aus wenn nicht
*******************************************************/
gamestatus CheckDDE()
{
    if (hConversation == NULL)
    {
        fprintf(stderr, "\nsimple draw wurde geschlossen Abfrage Neustart\n");

        int result = MessageBoxA(
            NULL,
            "Simple Draw wurde beendet.\nMöchten Sie Simple Draw neu starten?",
            "JSnake",
            MB_YESNO | MB_ICONWARNING
        );

        if (result == IDYES)
        {
            fprintf(stderr, "\nVersuche simple draw zu starten\n");

            // Simple Draw neu starten
            system("start \"\" \"Simple DDE Draw.exe\"");
            Sleep(1000); // kurz warten

            hConversation = DdeConnect(sd_idInst, sd_hsz_service, sd_hsz_topic, NULL);

            if (hConversation == NULL)
            {
                fprintf(stderr, "\nsimple draw konnte nicht gestartet werden programm wird sofort beendet\n");

                MessageBoxA(NULL,
                    "Simple Draw konnte nicht gestartet werden.\nJSnake wird beendet.",
                    "JSnake", MB_OK | MB_ICONERROR);
                exit(1);
            }
            ResizeGraphic(0, 0, client.Width, client.Height);
            return menue;
        }
        else
        {
            return exidgame; // Nein -> sauber beenden
        }
    }
    return running;
}


/*******************************************************
  Speilfeld mit Strichstäre genau auf Raster ausrichten
  Schlange genau an grenzen läuft
*******************************************************/
void InitField()
{
    field_x1 = Rand_Links;
    field_x2 = field_x1 + Pixel_Breite;
    field_y1 = Rand_Oben;
    field_y2 = field_y1 + Pixel_Hoehe;

    //Ausrichtung mit Strichstärke berücksichtigen (Strichstärke = Rast)

    field_x1 -= (Rast / 2);
    field_y1 -= (Rast / 2)+1;
    field_x2 += (Rast / 2)+1;
    field_y2 += (Rast / 2);

    return;
}



/******************************************************
    Funktion Zeichnung aller dynamischen Elemnte und

*******************************************************/
void Draw_Sgame()
{
    char sbuffer[20];

    if (score != last_score)
    {
        sprintf(sbuffer, "Score: %d", score);
        PlaceTextDynamic((field_x2 + 40), field_y1, sbuffer, richtung_L);
        last_score = score;
    }

    if (highscore != last_highscore)
    {
        sprintf(sbuffer, "Highscore %d", highscore);
        PlaceTextDynamic(field_x2 + 40, field_y1 + 24, sbuffer, richtung_L);
        last_highscore = highscore;
    }
    
    //Schlangenblock ?bermalen
    DrawBlock(Rast, Jsnake.pixtail.x, Jsnake.pixtail.y, Jsnake.seg[Jsnake.length - 1].farbe, 2);

    //Schlangenkopf malen
    DrawBlock(Rast, Jsnake.headpix.x, Jsnake.headpix.y, Jsnake.seg[0].farbe, 2);

    if (Jsnake.seg[Jsnake.length - 1].position.x == 2 || Jsnake.seg[Jsnake.length - 1].position.x == FELD_WIDTH + 1 || Jsnake.seg[Jsnake.length - 1].position.y == 8 || Jsnake.seg[Jsnake.length - 1].position.y == FELD_HEIGHT + 7)
    {
        SetPen(0, 0, 0, Rast);

        //Spielfeld
        MoveTo(field_x1, field_y1);
        DrawTo(field_x2, field_y1);
        DrawTo(field_x2, field_y2);
        DrawTo(field_x1, field_y2);
        DrawTo(field_x1, field_y1);
    }
    return;
}



/******************************************************
  Zeichnet einen Quadrat in der größe size farbe
  und strichstärke --> beeinflusst die zeichengeschwindigkeit
*******************************************************/
void DrawBlock(int size, int x, int y, color farbe, int w)
{
    
    int x_size = x + size;
    int y_size = y + size;

    SetPen(farbe.r, farbe.g, farbe.b, w);

    for (int i = y; i < y_size; i += w)
    {
        DrawLine(x, i, x + size, i);
    }

    return;
}


/******************************************************
 Hilfsfunktion Textausrichtung steureung mit typdef enum
rechts / mittig / links B?ndig
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
        PlaceText(client.Width / 2 - textWidth / 2, y, text);
    }
    if (modus == richtung_R)
    {
        //printf("\nTextaurichtung modus Rechts");
        PlaceText(client.Width - x - textWidth, y, text);
    }

    return;
}



/******************************************************
Hilfsfunktion alle statischen elemente in Initialisierung
*******************************************************/
void DrawStaticGame()
{
    ClearGraphic();

    SetPen(0, 0, 0, Rast);

    PlaceTextDynamic(60, 100, "JSnake", richtung_M);

    //Spielfeld
    MoveTo(field_x1, field_y1);
    DrawTo(field_x2, field_y1);
    DrawTo(field_x2, field_y2);
    DrawTo(field_x1, field_y2);
    DrawTo(field_x1, field_y1);

    return;
}

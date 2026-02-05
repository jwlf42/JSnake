/*
  Projektname:                 JSnake
  externe Schnittstelle:       Grafikausgabe mit Hilfe von "Simple Draw"
  Simple Draw:                 erstellt von Prof. Dr. Martin Gräfe
  Datei:                       jbutton.c
  Autor:                       Joel Wölfel
*/

#include "jbutton.h"
#include "simple_draw.h"

button Neustart;
button Pause;
button Hauptmenue;

button Starten;
button Optionen;
button Beenden;

button gruen;
button blau;
button rot;
button lila;
button hellgrau;
button dunkelblau;
button Hauptmenue1;



/******************************************************
  Zuweisung der Buttons mit Startwerten im struct
  zeiger auf buttons
*******************************************************/
void InitButton(button* Button, color normal, color hovered, const char* text, int x, int y, int w, int h)
{
    Button->position.x = x;
    Button->position.y = y;
    Button->size.Height = h;
    Button->size.Width = w;
    Button->hoveredcolor = hovered;
    Button->normalcolor = normal;
    Button->text = text;
    Button->hovered = 0;
    Button->clicked = 0;
    Button->needsredraw = 1;
}



/******************************************************
  Anlegen der Buttons mit Startwerten farbe größe etc.
  Aufrauf der zuwesiungsfunktion übergabe als zeiger
*******************************************************/
void InitButtons()
{
    //Gameoverbuttons
    InitButton(&Neustart, COLOR_WHITE, COLOR_LIGHTGREEN, "Neustart", field_x2 + 48, (client.Height / 2) - 200, 200, 80);
    InitButton(&Hauptmenue, COLOR_WHITE, COLOR_LIGHTGRAY, "Hauptmenue", field_x2 + 48, (client.Height / 2) - 75, 200, 80);

    //Hauptmenuebutton
    InitButton(&Starten, COLOR_WHITE, COLOR_DARKGRAY, "Spiel Starten", (client.Width / 2) - 125, 200, 250, 100);
    InitButton(&Optionen, COLOR_WHITE, COLOR_DARKGRAY, "Optionen", (client.Width / 2) - 125, 348, 250, 100);
    InitButton(&Beenden, COLOR_WHITE, COLOR_APPLERED, "Beenden", (client.Width / 2) - 125, 496, 250, 100);

    //Frabauswahlbuttons
    InitButton(&gruen, COLOR_SNAKEGREEN, COLOR_SNAKEGREEN, "", (client.Width / 2) - 100 - (OP_BUTTON / 2), (4 * OP_BUTTON), OP_BUTTON, OP_BUTTON);
    InitButton(&blau, COLOR_HELBLUE, COLOR_HELBLUE, "", (client.Width / 2) - 100 - (OP_BUTTON / 2), (5 * OP_BUTTON) + 30, OP_BUTTON, OP_BUTTON);
    InitButton(&lila, COLOR_LILA, COLOR_LILA, "", (client.Width / 2) - 100 - (OP_BUTTON / 2), (6 * OP_BUTTON) + 60, OP_BUTTON, OP_BUTTON);
    InitButton(&rot, COLOR_APPLERED, COLOR_APPLERED, "", (client.Width / 2) + 100 - (OP_BUTTON / 2), (4 * OP_BUTTON), OP_BUTTON, OP_BUTTON);
    InitButton(&hellgrau, COLOR_LIGHTGRAY, COLOR_LIGHTGRAY, "", (client.Width / 2) + 100 - (OP_BUTTON / 2), (5 * OP_BUTTON) + 30, OP_BUTTON, OP_BUTTON);
    InitButton(&dunkelblau, COLOR_DARKBLUE, COLOR_DARKBLUE, "", (client.Width / 2) + 100 - (OP_BUTTON / 2), (6 * OP_BUTTON) + 60, OP_BUTTON, OP_BUTTON);

    //Zurück zum Hauptmenue
    InitButton(&Hauptmenue1, COLOR_WHITE, COLOR_DARKGRAY, "<-- zurueck", (client.Width / 2) - 150, (client.Height / 2) + 50, 300, 80);
}



/******************************************************
  Bekommt ein feld von Button Adressen. 
*******************************************************/
void DrawButtons(button** buttons, int count)
{
    // Durchläuft alle Buttons im Array und ruft UpdateButton und RenderButton für jeden auf
    for (int i = 0; i < count; i++)
    {
        // übergebe die Adresse (&) des i-ten Buttons an die DrawButton-Funktionen.
        UpdateButtonState(buttons[i]);
        RenderButton(buttons[i]);
    }
}



/******************************************************
  Aktualisiert nur den Zustand des Buttons
  (hovered, clicked)
*******************************************************/
void UpdateButtonState(button* b)
{
    int x_mouse = GetMouseX();
    int y_mouse = GetMouseY();
    int washov = b->hovered;

    // Hover prüfen
    if (x_mouse > b->position.x && x_mouse < (b->position.x + b->size.Width) &&
        y_mouse > b->position.y && y_mouse < (b->position.y + b->size.Height))
    {
        b->hovered = 1;
        b->clicked = GetMouseButton(); // 1 wenn gedrückt
    }
    else
    {
        b->hovered = 0;
        b->clicked = 0;
    }
    if (washov != b->hovered)
        b->needsredraw = 1;
}



/******************************************************
  Zeichnung von einem button bei zustands änderung
  Zustand des Buttons gepeichert im button struct
*******************************************************/
void RenderButton(button* b)
{
    color c;
    int x1 = b->position.x;
    int y1 = b->position.y;
    int x2 = x1 + b->size.Width;
    int y2 = y1 + b->size.Height;

    int textWidth = strlen(b->text) * 6;
    int textHeight = 8;
    int center_x = b->position.x + (b->size.Width - textWidth) / 2;
    int center_y = b->position.y + (b->size.Height - textHeight) / 2;

    PlaceText(center_x, center_y, b->text);

    if (b->needsredraw == 0)
        return;
   

    c = b->hovered ? b->hoveredcolor : b->normalcolor;

    SetPen(c.r, c.g, c.b, B_THICK);

    for (int i = y1 + B_THICK / 2; i < y2; i += B_THICK)
        DrawLine(x1 + 5, i, x2 - 5, i);


    SetPen(b->hoveredcolor.r, b->hoveredcolor.g, b->hoveredcolor.b, 10);

    MoveTo(x1, y1);
    DrawTo(x2, y1);
    DrawTo(x2, y2);
    DrawTo(x1, y2);
    DrawTo(x1, y1);

    SetPen(0, 0, 0, 6);
    MoveTo(x1 - 6, y1 - 6);
    DrawTo(x2 + 6, y1 - 6);
    DrawTo(x2 + 6, y2 + 6);
    DrawTo(x1 - 6, y2 + 6);
    DrawTo(x1 - 6, y1 - 6);

    b->needsredraw = 0;
}
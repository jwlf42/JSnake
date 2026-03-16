/*
  Projektname:                 JSnake
  externe Schnittstelle:       Grafikausgabe mit Hilfe von "Simple Draw"
  Simple Draw:                 erstellt von Prof. Dr. Martin Gräfe
  Datei:                       jbutton.c
  Autor:                       Joel Wölfel
*/

#include "jbutton.h"
#include "simple_draw.h"
#include "draw_jprogramm.h"



/******************************************************
  Zuweisung der Buttons mit Startwerten im struct
  zeiger auf buttons
*******************************************************/
void InitButton(button_t* Button, color_t normal, color_t hovered, coordinates_t size, const char* text, int x, int y)
{
    Button->position.x = x;
    Button->position.y = y;
    Button->size = size;
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
void InitProgrammButtons()
{
    //Hauptmenuebutton
    InitButton(&Starten, COLOR_WHITE, COLOR_DARKGRAY, MAIN_B_SIZE, "Spiel Starten", clientcenter.x - MAIN_B_SIZE.x/2, 200);
    InitButton(&Optionen, COLOR_WHITE, COLOR_DARKGRAY, MAIN_B_SIZE, "Optionen", clientcenter.x - MAIN_B_SIZE.x / 2, 348);
    InitButton(&Beenden, COLOR_WHITE, COLOR_APPLERED, MAIN_B_SIZE, "Beenden", clientcenter.x - MAIN_B_SIZE.x / 2, 496);

    //Frabauswahlbuttons
    InitButton(&gruen, COLOR_SNAKEGREEN, COLOR_SNAKEGREEN, OP_B_SIZE, "", clientcenter.x - 100 - (OP_BUTTON / 2), (4 * OP_BUTTON));
    InitButton(&blau, COLOR_HELBLUE, COLOR_HELBLUE, OP_B_SIZE, "", clientcenter.x - 100 - (OP_BUTTON / 2), (5 * OP_BUTTON) + 30);
    InitButton(&lila, COLOR_LILA, COLOR_LILA, OP_B_SIZE, "", clientcenter.x - 100 - (OP_BUTTON / 2), (6 * OP_BUTTON) + 60);
    InitButton(&rot, COLOR_APPLERED, COLOR_APPLERED, OP_B_SIZE, "", clientcenter.x + 100 - (OP_BUTTON / 2), (4 * OP_BUTTON));
    InitButton(&hellgrau, COLOR_LIGHTGRAY, COLOR_LIGHTGRAY, OP_B_SIZE, "", clientcenter.x + 100 - (OP_BUTTON / 2), (5 * OP_BUTTON) + 30);
    InitButton(&dunkelblau, COLOR_DARKBLUE, COLOR_DARKBLUE, OP_B_SIZE, "", clientcenter.x + 100 - (OP_BUTTON / 2), (6 * OP_BUTTON) + 60);

    //Zurück zum Hauptmenue
    InitButton(&Back, COLOR_WHITE, COLOR_DARKGRAY, BACK_B_SIZE, "<-- zurueck", clientcenter.x - (BACK_B_SIZE.x/2), (7 * OP_BUTTON) + 90);
}



void InitGameButtons()
{
    //Gamebuttons
    InitButton(&Neustart, COLOR_WHITE, COLOR_LIGHTGREEN, MEDIUM_B_SIZE, "Neustart", standardfield.size.x + 100, standardfield.pos.y + 190);
    InitButton(&Hauptmenue, COLOR_WHITE, COLOR_LIGHTGRAY, MEDIUM_B_SIZE, "Hauptmenue", standardfield.size.x + 100, standardfield.pos.y + 300);
}



/******************************************************
  Bekommt ein feld von Button Adressen. 
*******************************************************/
void DrawButtons(button_t** buttons, int count)
{
    int i;
    // Durchläuft alle Buttons im Array und ruft UpdateButton und RenderButton für jeden auf
    for (i = 0; i < count; i++)
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
void UpdateButtonState(button_t* b)
{
    int x_mouse = GetMouseX();
    int y_mouse = GetMouseY();
    int washov = b->hovered;

    // Hover prüfen
    if (x_mouse > b->position.x && x_mouse < (b->position.x + b->size.x) &&
        y_mouse > b->position.y && y_mouse < (b->position.y + b->size.y))
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
  Rendert einen Button, wenn sich sein Zustand ändert.
  benötigt die adresse des Buttons
*******************************************************/
void RenderButton(button_t* b)
{
    color_t c;
    coordinates_t tsize, center;

    if (!b->needsredraw)
        return;

    tsize.x = (int)strlen(b->text) * 6;
    tsize.y = 8;
    center.x = b->position.x + (b->size.x - tsize.x) / 2;
    center.y = b->position.y + (b->size.y - tsize.y) / 2;
   
    c = b->hovered ? b->hoveredcolor : b->normalcolor;
    
    DrawRectFill(b->size, b->position.x, b->position.y, c, B_THICK);
    DrawRect(b->size, b->position.x, b->position.y, b->hoveredcolor, B_THICK);
    DrawRect((coordinates_t) { b->size.x + (B_THICK / 2), b->size.y + (B_THICK / 2)}, b->position.x - (B_THICK / 4), b->position.y - (B_THICK / 4), COLOR_BLACK, (B_THICK / 2));
    PlaceText(center.x, center.y, b->text);

    b->needsredraw = 0;

    return;
}
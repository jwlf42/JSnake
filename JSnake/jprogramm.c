/*
  Projektname:                 JSnake
  externe Schnittstelle:       Grafikausgabe mit Hilfe von "Simple Draw"
  Simple Draw:                 erstellt von Prof. Dr. Martin Gräfe
  Datei:                       Jprogramm.c
  Autor:                       Joel Wölfel
*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <windows.h>
#include "jprogramm.h"
#include "function_snake.h"
#include "draw_jprogramm.h"
#include "jbutton.h"
#include "simple_draw.h"
#include "jfile.h"



gamestatus gamestate = menue;
coordinates screen;
coordinates client;
coordinates clientcenter;



/******************************************************
   Fenster goeße für simple draw zu Vollbild anpassen
   Spielfeld, Buttons und Highscore Initialisieren
*******************************************************/
void InitWindow()
{
	int border = GetSystemMetrics(SM_CXFRAME);    // Rahmen links/rechts
	int title = GetSystemMetrics(SM_CYCAPTION);  // Titelleiste oben
	int menu = GetSystemMetrics(SM_CYMENU);    

	screen.x = GetSystemMetrics(SM_CXSCREEN);
	screen.y = GetSystemMetrics(SM_CYSCREEN);

	client.x = screen.x - 2 * border;     // clientWidth =bildschirmbreite minus rand rechts links
	client.y = screen.y - title - border - menu;

	clientcenter.x = client.x / 2;
	clientcenter.y = client.y / 2;

	Rand_Links = 2 * Rast;
	Rand_Oben = 8 * Rast;

	controlColor = COLOR_SNAKEGREEN;

	ResizeGraphic(0, 0, client.x, client.y);

	ClearGraphic();
	
	InitField();

	InitButtons();
	
	return;
}



/******************************************************
   Startbildschrim Hauptmenue
   
*******************************************************/
void MenueLoop()
{
	button* MenueButtons[] = { &Starten, &Beenden, &Optionen };
	const int NUM_GO_BUTTONS = 3;
	int i;

	for (i = 0; i < NUM_GO_BUTTONS; i++)
	{
		MenueButtons[i]->needsredraw = 1;
	}

	PlaceTextDynamic(60, 150, "JSNAKE", richtung_M);

	while(CheckDDE(&gamestate)==0)
	{
		DrawButtons(MenueButtons, NUM_GO_BUTTONS);

		if(Starten.clicked & 2)
		{
			ClearGraphic();
			gamestate = ready;
			break;
		}

		if (Optionen.clicked & 2)
		{
			ClearGraphic();
			gamestate = option;
			break;
		}

		if (Beenden.clicked & 2)
		{
			ClearGraphic();
			gamestate = exitgame;
			break;
		}
	}
	return;
}



/******************************************************
   Warten aud Eingabe Bildschirm

*******************************************************/
void GameReadyLoop()
{
	button* GameReadyButtons[] = {&Hauptmenue};
	coordinates taste = {0,0};
	const int NUM_GO_BUTTONS = 1;
	int i;

	for (i = 0; i < NUM_GO_BUTTONS; i++)
	{
		GameReadyButtons[i]->needsredraw = 1;
	}

	InitGame();

	while(CheckDDE(&gamestate)==0)
	{
		DrawButtons(GameReadyButtons, NUM_GO_BUTTONS);

		if (InputControl(&taste)!=0)
		{
			gamestate = running;
			ClearGraphic();
			InitSnake(&Jsnake, taste, controlColor, 3);
			break;
		}

		if (Hauptmenue.clicked & 2)
		{
			ClearGraphic();
			gamestate = menue;
			break;
		}
	}
	return;
}



/******************************************************
   Speiel schleife

*******************************************************/
void GameLoop()
{	
	DrawStaticGame();
	DrawGame();

	while(CheckDDE(&gamestate)==0)
	{
		UpdateLogic();
		if (gamestate != running)
			break;
		UpdateAnimation();
		DrawGame();
		Sleep(14);
	}
	return;
}



/******************************************************
   Optionen Bildschirm

*******************************************************/
void OptionLoop()
{
	button* OptionButtons[] = { &gruen, &blau, &lila, &rot, &hellgrau, &dunkelblau, &Hauptmenue1 };
	const int NUM_GO_BUTTONS = 7;
	coordinates size = { OP_BUTTON,OP_BUTTON };
	int i;

	for (i = 0; i < NUM_GO_BUTTONS; i++)
	{
		OptionButtons[i]->needsredraw = 1;
	}
	
	PlaceTextDynamic(60, 150, "Schlangenfarbe wählen", richtung_M);
	PlaceText(client.x / 2 + 150, 150, "Anzeige:");

	while(CheckDDE(&gamestate)==0)
	{
		DrawButtons(OptionButtons, NUM_GO_BUTTONS);
		DrawRectFill(size, client.x / 2 + 220, 128, controlColor, 3);

		if (gruen.clicked & 2)
		{
			controlColor = gruen.normalcolor;
		}

		if (blau.clicked & 2)
		{
			controlColor = blau.normalcolor;
		}

		if (lila.clicked & 2)
		{
			controlColor = lila.normalcolor;
		}

		if (rot.clicked & 2)
		{
			controlColor = rot.normalcolor;
		}

		if (hellgrau.clicked & 2)
		{
			controlColor = hellgrau.normalcolor;
		}

		if (dunkelblau.clicked & 2)
		{
			controlColor = dunkelblau.normalcolor;
		}

		if (Hauptmenue1.clicked & 2)
		{
			ClearGraphic();
			gamestate = menue;
			break;
		}
	}
	return;
}



/******************************************************
   Gameoverbilschirm

*******************************************************/
void GameoverLoop()
{
	button* GameOverButtons[] = {&Neustart, &Hauptmenue};
	const int NUM_GO_BUTTONS = 2;
	int i;

	for (i = 0; i < NUM_GO_BUTTONS; i++)
	{
		GameOverButtons[i]->needsredraw = 1;
	}

	PlaceText(((FIELD_WIDTH / 2) * Rast)+Rand_Links, ((FIELD_HEIGHT / 2) * Rast)+Rand_Oben, "GAME OVER");

	while(CheckDDE(&gamestate)==0)
	{
		DrawButtons(GameOverButtons, NUM_GO_BUTTONS);

		if (Hauptmenue.clicked & 2)
		{
			ClearGraphic();
			gamestate = menue;
			break;
		}
		if (Neustart.clicked & 2)
		{
			ClearGraphic();
			gamestate = ready;
			break;
		}
	}
	return;
}
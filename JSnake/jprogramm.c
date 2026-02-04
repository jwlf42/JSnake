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

gamestatus gamestate = menue;
dimension screen;
dimension client;



/******************************************************
   Bei Programmstart Anlegen einer log Datei
   mit umgehnder umleitung des standartfehlerkanals stderr
*******************************************************/
void InitLog()
{
	FILE* datei = freopen("JSnake_errors.log", "w", stderr);

	if (datei == NULL)
		perror("InitLog: freopen fehlgeschlagen");
	else
		fprintf(stderr, "Programm gestartet\n");
}



/******************************************************
   Fenster goeße für simple draw zu Vollbild anpassen
   Spielfeld, Buttons und Highscore Initialisieren
*******************************************************/
void InitWindow()
{
	int border = GetSystemMetrics(SM_CXFRAME);    // Rahmen links/rechts
	int title = GetSystemMetrics(SM_CYCAPTION);  // Titelleiste oben
	int menu = GetSystemMetrics(SM_CYMENU);    

	screen.Width = GetSystemMetrics(SM_CXSCREEN);
	screen.Height = GetSystemMetrics(SM_CYSCREEN);

	client.Width = screen.Width - 2 * border;     // clientWidth =bildschirmbreite minus rand rechts links
	client.Height = screen.Height - title - border - menu;

	Pixel_Breite = FELD_WIDTH * Rast;
	Pixel_Hoehe = FELD_HEIGHT * Rast;
	Rand_Links = 2 * Rast;
	Rand_Oben = 8 * Rast;

	controlColor = COLOR_SNAKEGREEN;

	ResizeGraphic(0, 0, client.Width, client.Height);

	ClearGraphic();

	InitField();

	InitButtons();

	LoadHighscore();

	return;
}



/******************************************************
   Startbildschrim Hauptmenue
   
*******************************************************/
void MenueLoop()
{
	button* MenueButtons[] = { &Starten, &Beenden, &Optionen };
	const int NUM_GO_BUTTONS = 3;

	for (int i = 0; i < NUM_GO_BUTTONS; i++)
	{
		MenueButtons[i]->needsredraw = 1;
	}

	PlaceTextDynamic(60, 150, "JSNAKE", richtung_M);

	for(;;)
	{
		gamestate = CheckDDE();

		if (gamestate == exitgame || gamestate == menue)
			 break; 

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

	for (int i = 0; i < NUM_GO_BUTTONS; i++)
	{
		GameReadyButtons[i]->needsredraw = 1;
	}

	InitGame();
	InitSnake(&Jsnake, (coordinates){0,0}, controlColor, 7);
	Draw_Sgame();

	PlaceTextDynamic(field_x2 + 40, field_y1 + 168, "Spielen mit den Tasten\"W, A ,S, D\"", richtung_L);

	while(gamestate==ready)
	{
		gamestate = CheckDDE();

		if (gamestate == exitgame || gamestate == menue)
			break;
		gamestate = ready;

		DrawButtons(GameReadyButtons, NUM_GO_BUTTONS);

		if (InputControl(&taste)!=0)
		{
			gamestate = running;
			InitSnake(&Jsnake, taste, controlColor, 7);
			DrawBlock(225, field_x2 + 40, (client.Height / 2) - 75, COLOR_WHITE, 45);
		}

		if (Hauptmenue.clicked & 2)
		{
			ClearGraphic();
			gamestate = menue;
		}
	}
	return;
}



/******************************************************
   Speiel schleife

*******************************************************/
void GameLoop()
{	
	for(;;)
	{
		gamestate = CheckDDE();
		
		UpdateLogic();
		if (gamestate != running)
			break;
		UpdateAnimation();
		Draw_Sgame();
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

	

	for (int i = 0; i < NUM_GO_BUTTONS; i++)
	{
		OptionButtons[i]->needsredraw = 1;
	}
	
	
	PlaceTextDynamic(60, 150, "Schlangenfarbe waehlen", richtung_M);

	for (;;)
	{
		gamestate = CheckDDE();

		if (gamestate == exitgame || gamestate == menue)
			break;  // sofort rau

		DrawButtons(OptionButtons, NUM_GO_BUTTONS);

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

		PlaceText(client.Width / 2 + 150, 150, "Anzeige:");
		DrawBlock(OP_BUTTON, client.Width / 2 + 220, 128, controlColor, 1);
	}
	return;
}



/******************************************************
   Gameoverbilschirm

*******************************************************/
void GameoverLoop()
{
	button* GameOverButtons[] = {&Neustart, &Pause, &Hauptmenue};
	const int NUM_GO_BUTTONS = 3;

	for (int i = 0; i < NUM_GO_BUTTONS; i++)
	{
		GameOverButtons[i]->needsredraw = 1;
	}

	PlaceText(((FELD_WIDTH / 2) * Rast)+Rand_Links, ((FELD_HEIGHT / 2) * Rast)+Rand_Oben, "GAME OVER");
	PlaceTextDynamic(field_x2 + 40, field_y1 + 168, "________________________            ", richtung_L);

	for (;;)
	{
		gamestate = CheckDDE();

		if (gamestate == exitgame || gamestate == menue)
			break;  // sofort raus

		DrawButtons(GameOverButtons, NUM_GO_BUTTONS);

		if (Hauptmenue.clicked & 2)
		{
			ClearGraphic();
			gamestate = menue;
			break;
		}
		if (Neustart.clicked & 2)
		{
			gamestate = ready;
			break;
		}
		if (Pause.clicked & 2)
		{
			while (KeyPressed() == 0)
			{
				gamestate = CheckDDE();

				if (gamestate == exitgame || gamestate == menue)
					break;  // sofort rau

				PlaceText(((FELD_WIDTH / 2) * Rast) + Rand_Links, ((FELD_HEIGHT / 2) * Rast) + Rand_Oben, "\"|| Pause\" druecke Taste für weiter ->");
			}
			PlaceText(((FELD_WIDTH / 2) * Rast) + Rand_Links, ((FELD_HEIGHT / 2) * Rast) + Rand_Oben, "                                       ");

			break;
		}
	}
	return;
}
/*
  Projektname:                 JSnake
  externe Schnittstelle:       Grafikausgabe mit Hilfe von "Simple Draw"
  Simple Draw:                 erstellt von Prof. Dr. Martin Gräfe
  Datei:                       mainSnake.c
  Autor:                       Joel Wölfel
*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <windows.h>
#include "jprogramm.h"
#include "jfile.h"



int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	InitLog();
	InitWindow();
	
	while(gamestate!=exitgame)
	{
		switch (gamestate)
		{
		case menue:
			MenueLoop();
			break;
		case ready:
			GameReadyLoop();
			break;
		case running:
			GameLoop();
			break;
		case option:
			OptionLoop();
			break;
		case gameover:
			GameoverLoop();
			break;
		default:
			fprintf(stderr, "\nFehler: Kein gültiger Programmstatus: %d", gamestate);
			gamestate = menue;
		}
	}
	SaveScore();
	fprintf(stderr, "\nProgramm beendet\n");
	return 0;
}
/*
  Projektname:                 JSnake
  externe Schnittstelle:       Grafikausgabe mit Hilfe von "Simple Draw"
  Simple Draw:                 erstellt von Prof. Dr. Martin Gräfe
  Datei:                       mainSnake.c
  Autor:                       Joel Wölfel
*/

#define CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <time.h>
#include <windows.h>
#include "jprogramm.h"
#include "simple_draw.h"
#include "function_snake.h"


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	InitLog();
	InitWindow();
	
	while(gamestate!=exidgame)
	{
		switch (gamestate)
		{
		case menue:
			MenueLoop();
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
		}
	}
	SaveScore();
	fprintf(stderr, "\nProgramm beendet\n");
	fclose(stderr);
	return 0;
}
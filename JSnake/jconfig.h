
#ifndef JCONFIG_H
#define JCONFIG_H

#include <windows.h>

#define Rast 24
#define FELD_WIDTH 34
#define FELD_HEIGHT 20

#define SPEED 6
#define MAX_SEG 690
#define MASX_BUT 10
#define OP_BUTTON 60
#define B_THICK 15


typedef struct Koordinaten
{
	int x;
	int y;
}coordinates;


typedef struct abmessung
{
	int Height;
	int Width;
}dimension;


typedef struct Farben
{
	int r, g, b;
}color;


typedef enum Ausrichtung
{
	richtung_L,
	richtung_M,
	richtung_R
} richtung;


typedef struct Schlangensegmente
{
	coordinates position;
	coordinates direction;
	color farbe;
}snakeseg;


typedef struct Schlange
{
	snakeseg seg[MAX_SEG];
	snakeseg target;
	coordinates headpix;
	coordinates pixtail;
	int length;
}Snake;


typedef struct Schaltfläche
{
	coordinates position;
	dimension size;
	richtung alignment;
	color normalcolor;
	color hoveredcolor;
	const char* text;
	int needsredraw;
	int hovered;
	int clicked;
}button;

typedef enum Speilstatus
{
	menue,
	ready,
	running,
	option,
	gameover,
	exitgame
}gamestatus;

extern gamestatus gamestate;

extern color controlColor;

extern const color COLOR_WHITE;
extern const color COLOR_BLACK;
extern const color COLOR_LIGHTGREEN;
extern const color COLOR_DARKGRAY;
extern const color COLOR_SNAKEGREEN;
extern const color COLOR_APPLERED;
extern const color COLOR_HELBLUE;
extern const color COLOR_LILA;
extern const color COLOR_LIGHTGRAY;
extern const color COLOR_DARKBLUE;

extern dimension screen;
extern dimension client;

extern Snake Jsnake;
extern coordinates food;

extern button Neustart;
extern button Pause;
extern button Hauptmenue;

extern button Starten;
extern button Optionen;
extern button Beenden;

extern button gruen;
extern button blau;
extern button grau;
extern button rot;
extern button lila;
extern button dunkelblau;
extern button hellgrau;
extern button Hauptmenue1;

extern HCONV hConversation;
extern DWORD sd_idInst;
extern HSZ sd_hsz_service;
extern HSZ sd_hsz_topic;


extern int Pixel_Breite;
extern int Pixel_Hoehe;
extern int Rand_Links;
extern int Rand_Oben;
extern int field_x1, field_y1, field_x2, field_y2;
extern int score;
extern int highscore;
extern int last_score;
extern int last_highscore;

#endif



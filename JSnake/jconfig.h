
#ifndef JCONFIG_H
#define JCONFIG_H

#include <windows.h>

#define Rast 24
#define FIELD_WIDTH 34
#define FIELD_HEIGHT 20

#define SPEED 6
#define MAX_SEG 690
#define MASX_BUT 10
#define OP_BUTTON 60
#define B_THICK 15



typedef enum Speilstatus
{
	menue,
	ready,
	running,
	option,
	gameover,
	exitgame
}gamestatus;


typedef enum Ausrichtung
{
	richtung_L,
	richtung_M,
	richtung_R
} richtung;


typedef struct Koordinaten
{
	int x;
	int y;
}coordinates;


typedef struct Farben
{
	int r, g, b;
}color;

typedef struct Feld
{
	coordinates position;
	coordinates size;
	color farbe;
	int draw;
}field;


typedef struct Essen
{
	coordinates rastpos;
	coordinates size;
	color farbe;
	int active;
	int value;
}food;


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
}snakes;


typedef struct Schaltfläche
{
	coordinates position;
	coordinates size;
	richtung alignment;
	color normalcolor;
	color hoveredcolor;
	const char* text;
	int needsredraw;
	int hovered;
	int clicked;
}button;

extern gamestatus gamestate;

extern HCONV hConversation;
extern DWORD sd_idInst;
extern HSZ sd_hsz_service;
extern HSZ sd_hsz_topic;

extern snakes Jsnake;
extern food apple;

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

extern field standardfield;

extern coordinates screen;
extern coordinates client;
extern coordinates clientcenter;

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

extern int Rand_Links;
extern int Rand_Oben;
extern int score;
extern int highscore;
extern int last_score;
extern int last_highscore;

#endif

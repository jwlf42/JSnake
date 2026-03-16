
#ifndef JCONFIG_H
#define JCONFIG_H

#include <windows.h>

#define JCOORD(x,y) (coordinates_t){(x),(y)}

#define MAIN_BUTTON_W 250
#define MAIN_BUTTON_H 100
#define MEDIUM_BUTTON_W 200
#define MEDIUM_BUTTON_H 80
#define BACK_BUTTON_W 300
#define BACK_BUTTON_H 80
#define OP_BUTTON 60

#define B_THICK 12

#define RAST 24
#define RASTSIZE JCOORD(RAST,RAST)
#define FIELD_WIDTH 34
#define FIELD_HEIGHT 20

#define SPEED 6
#define MAX_SEG 690



typedef enum Speilstatus
{
	menue,
	ready,
	running,
	option,
	gameover,
	exitgame
}gamestatus_t;


typedef enum Ausrichtung
{
	richtung_L,
	richtung_M,
	richtung_R
} richtung_t;


typedef struct Koordinaten
{
	int x;
	int y;
}coordinates_t;


typedef struct Farben
{
	int r, g, b;
}color_t;


typedef struct Feld
{
	coordinates_t pos;
	coordinates_t size;
	coordinates_t offset;
	color_t color;
	int draw;
}rast_t;


typedef struct Essen
{
	rast_t rast;
	int value;
}food_t;


typedef struct Schlangensegment
{
	rast_t rast;
	coordinates_t dir;
}snakeseg_t;


typedef struct Schlange
{
	snakeseg_t seg[MAX_SEG];
	rast_t target;
	coordinates_t dir;
	int length;
	int progress;
}snake_t;


typedef struct Schaltfläche
{
	coordinates_t position;
	coordinates_t size;
	richtung_t alignment;
	color_t normalcolor;
	color_t hoveredcolor;
	const char* text;
	int needsredraw;
	int hovered;
	int clicked;
}button_t;

extern gamestatus_t gamestate;
extern HCONV hConversation;
extern DWORD sd_idInst;
extern HSZ sd_hsz_service;
extern HSZ sd_hsz_topic;

extern coordinates_t screen;
extern coordinates_t client;
extern coordinates_t clientcenter;
extern int Rand_Links;
extern int Rand_Oben;

extern rast_t standardfield;
extern snake_t Jsnake;
extern food_t apple;
extern color_t controlColor;
extern int score;
extern int highscore;
extern int last_score;
extern int last_highscore;

extern button_t Starten;
extern button_t Optionen;
extern button_t Beenden;
extern button_t gruen;
extern button_t blau;
extern button_t grau;
extern button_t rot;
extern button_t lila;
extern button_t dunkelblau;
extern button_t hellgrau;
extern button_t Back;
extern button_t Neustart;
extern button_t Pause;
extern button_t Hauptmenue;

extern const coordinates_t MAIN_B_SIZE;
extern const coordinates_t MEDIUM_B_SIZE;
extern const coordinates_t OP_B_SIZE;
extern const coordinates_t BACK_B_SIZE;

extern const color_t COLOR_WHITE;
extern const color_t COLOR_BLACK;
extern const color_t COLOR_LIGHTGREEN;
extern const color_t COLOR_DARKGRAY;
extern const color_t COLOR_SNAKEGREEN;
extern const color_t COLOR_APPLERED;
extern const color_t COLOR_HELBLUE;
extern const color_t COLOR_LILA;
extern const color_t COLOR_LIGHTGRAY;
extern const color_t COLOR_DARKBLUE;

#endif

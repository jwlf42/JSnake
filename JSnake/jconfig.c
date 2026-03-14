/*
  Projektname:                 JSnake
  externe Schnittstelle:       Grafikausgabe mit Hilfe von "Simple Draw"
  Simple Draw:                 erstellt von Prof. Dr. Martin Gräfe
  Datei:                       jconfig.c
  Autor:                       Joel Wölfel
*/

#include "jconfig.h"

gamestatus_t gamestate = menue;

coordinates_t screen;
coordinates_t client;
coordinates_t clientcenter;
int Rand_Links;
int Rand_Oben;


snake_t Jsnake;
rast_t standardfield;
food_t apple;
color_t controlColor;
int score = 0;
int highscore = 0;
int last_score = -1;
int last_highscore = -1;

button_t Starten;
button_t Optionen;
button_t Beenden;
button_t gruen;
button_t blau;
button_t rot;
button_t lila;
button_t hellgrau;
button_t dunkelblau;
button_t Back;
button_t Neustart;
button_t Pause;
button_t Hauptmenue;

const coordinates_t MAIN_B_SIZE = { MAIN_BUTTON_W, MAIN_BUTTON_H };
const coordinates_t MEDIUM_B_SIZE={MEDIUM_BUTTON_W,MEDIUM_BUTTON_H};
const coordinates_t OP_B_SIZE = { OP_BUTTON,OP_BUTTON };
const coordinates_t BACK_B_SIZE = { BACK_BUTTON_W,BACK_BUTTON_H };

const color_t COLOR_WHITE = { 255, 255, 255 };
const color_t COLOR_BLACK = { 0,0,0 };
const color_t COLOR_LIGHTGREEN = { 144, 238, 144 };
const color_t COLOR_DARKGRAY = { 50, 50, 50 };
const color_t COLOR_SNAKEGREEN = { 50, 205, 50 };
const color_t COLOR_APPLERED = { 255, 0, 0 };
const color_t COLOR_HELBLUE = { 173, 216, 230 };
const color_t COLOR_LILA = { 186, 85, 211 };
const color_t COLOR_LIGHTGRAY = { 211, 211, 211 };
const color_t COLOR_DARKBLUE = { 25, 25, 112 };



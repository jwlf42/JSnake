/*
  Projektname:                 JSnake
  externe Schnittstelle:       Grafikausgabe mit Hilfe von "Simple Draw"
  Simple Draw:                 erstellt von Prof. Dr. Martin Gräfe
  Datei:                       jfile.c
  Autor:                       Joel Wölfel
*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <windows.h>
#include "jfile.h"


/*******************************************************
  Üpferprüft ob die Verbindung zu Simple Draw steht.
  gibt eine Windows fehlermeldung aus wenn nicht
*******************************************************/
int CheckDDE(gamestatus* state)
{
    int result;

    if (hConversation == NULL)
    {
        fprintf(stderr, "\nsimple draw wurde geschlossen Abfrage Neustart\n");

        result = MessageBoxA(NULL, "Simple Draw wurde beendet.\nMöchten Sie Simple Draw neu starten?", "JSnake", MB_YESNO | MB_ICONWARNING);

        if (result == IDYES)
        {
            fprintf(stderr, "\nVersuche simple draw zu starten\n");

            // Simple Draw neu starten
            system("start \"\" \"Simple DDE Draw.exe\"");
            Sleep(1000); // kurz warten

            hConversation = DdeConnect(sd_idInst, sd_hsz_service, sd_hsz_topic, NULL);

            if (hConversation == NULL)
            {
                fprintf(stderr, "\nsimple draw konnte nicht gestartet werden programm wird sofort beendet\n");

                MessageBoxA(NULL, "Simple Draw konnte nicht gestartet werden.\nJSnake wird beendet.", "JSnake", MB_OK | MB_ICONERROR);
                exit(1);
            }
            ResizeGraphic(0, 0, client.x, client.y);
            *state = menue;
            return 1;
        }
        else
        {
            *state = exitgame; // Nein -> sauber beenden
            return 1;
        }
    }
    return 0;
}



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
   Binaerdatei für Highscore lesen oder erstellen

*******************************************************/
void LoadHighscore()
{
    FILE* datei;
    int readscore = highscore;

    if ((datei = fopen("snakecore", "rb")) == NULL)
    {
        fprintf(stderr, "\nDatei konnte nicht geöffnet werden\n");
        fprintf(stderr, "\nDatei wird neu erstellt\n");

        if ((datei = fopen("snakecore", "wb")) == NULL)
            fprintf(stderr, "\nNeue Datei kann nicht erstellt werden\n");
        else
        {
            if ((fwrite(&readscore, sizeof(int), 1, datei)) != 1)
            {
                fprintf(stderr, "\nNeue Datei kann nicht beschrieben werden\n");
            }
            fclose(datei);
        }
    }
    else
    {
        if (fread(&readscore, sizeof(int), 1, datei) == 1)
        {
            highscore = readscore;
        }
        else
            fprintf(stderr, "\nDaeti konnte nicht gelesen werden\n");

        fclose(datei);
    }
}



/******************************************************
   Highscore speichern

*******************************************************/
void SaveScore()
{
    FILE* datei;
    int writescore = highscore;

    if ((datei = fopen("snakecore", "r+b")) == NULL)
    {
        fprintf(stderr, "\nHighscore-Datei kann nicht zum speichern geoffnet werden\n");
    }
    else
    {
        if ((fwrite(&writescore, sizeof(int), 1, datei)) != 1)
        {
            fprintf(stderr, "\nHighscore kann nicht gespeichert werden\n");
        }
        fclose(datei);
    }
}
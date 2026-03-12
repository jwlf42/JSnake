#ifndef JBUTTON_H
#define JBUTTON_H

#include "jconfig.h"

void InitProgrammButtons();

void InitGameButtons();

void DrawButtons(button_t** buttons, int count);

void RenderButton(button_t* b);

void UpdateButtonState(button_t* b);

void InitButton(button_t* Button, color_t normal, color_t hovered, coordinates_t size, const char* text, int x, int y);

#endif

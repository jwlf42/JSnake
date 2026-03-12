#ifndef JBUTTON_H
#define JBUTTON_H

#include "jconfig.h"

void InitProgrammButtons();

void InitGameButtons();

void DrawButtons(button** buttons, int count);

void RenderButton(button* b);

void UpdateButtonState(button* b);

void InitButton(button* Button, color_t normal, color_t hovered, coordinates size, const char* text, int x, int y);

#endif

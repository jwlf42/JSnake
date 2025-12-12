#ifndef JBUTTON_H
#define JBUTTON_H

#include "jconfig.h"

void InitButtons();

void DrawButtons(button** buttons, int count);

void RenderButton(button* b);

void UpdateButtonState(button* b);

void InitButton(button* Button, color normal, color hovered, char* text, int x, int y, int w, int h);

#endif

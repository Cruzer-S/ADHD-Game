#ifndef SCREEN_H__
#define SCREEN_H__

#include "map.h"
#include "object.h"
#include "ui.h"

void screen_setup(void);

void screen_add_ui(UI );
void screen_draw_ui(void);

void screen_draw_map(int x, int y, Map );
void screen_draw_object(Object );

int screen_get_input(void);

void screen_cleanup(void);

#endif

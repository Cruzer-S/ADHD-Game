#ifndef SCREEN_H__
#define SCREEN_H__

#include "map.h"
#include "object.h"

void screen_setup(void);

void screen_draw_map(Map );
void screen_draw_object(Object );

int screen_get_input(void);

void screen_cleanup(void);

#endif

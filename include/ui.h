#ifndef UI_H__
#define UI_H__

#include <stdbool.h>

typedef struct ui *UI;

UI ui_create(int x, int y, int width, int height);

int ui_add_string(UI , int x, int y, char *string, int n);
int ui_del_string(UI , char *string);

void ui_set_border(UI , bool visible);
bool ui_is_border(UI );

void ui_set_hide(UI , bool hide);
bool ui_is_hidden(UI );

int ui_get_x(UI );
int ui_get_y(UI );

void ui_top(UI );
void ui_bottom(UI );

int ui_get_width(UI );
int ui_get_height(UI );

void ui_move(UI , int x, int y);
void ui_resize(UI , int width, int height);

void ui_destroy(UI );

#endif

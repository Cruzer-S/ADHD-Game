#include "player.h"
#include "screen.h"
#include "ui.h"

#include <ncurses.h>

#define SCREEN_SIZE_COLUMN		80
#define SCREEN_SIZE_ROW			24

#define SCREEN_BOARD_START_X		0
#define SCREEN_BOARD_START_Y		0
#define SCREEN_BOARD_SIZE_COLUMN	80
#define SCREEN_BOARD_SIZE_ROW		18

#define SCREEN_UI_START_X		0
#define SCREEN_UI_START_Y		18
#define SCREEN_UI_SIZE_COLUMN		80
#define SCREEN_UI_SIZE_ROW		6

#define SCREEN_START(NAME, XY)		SCREEN_##NAME##_START_##XY
#define SCREEN_XSTART(NAME)		SCREEN_START(NAME, X)
#define SCREEN_YSTART(NAME)		SCREEN_START(NAME, Y)

#define SCREEN_SIZE(NAME, ROWCOLUMN)	SCREEN_##NAME##_SIZE_##ROWCOLUMN
#define SCREEN_RSIZE(NAME)		SCREEN_SIZE(NAME, ROW)
#define SCREEN_CSIZE(NAME)		SCREEN_SIZE(NAME, COLUMN)

static bool check_movable(Map map, int x, int y)
{
	int width, height;

	width = map_get_size_x(temp_map);
	height = map_get_size_y(temp_map);

	if (x < 0 || x >= width)
		return false;

	if (y < 0 || y >= height)
		return false;

	return map_get_tile(map, x, y)->passable;
}

int main(void)
{
	Player player;
	Object p_obj;

	UI board, panel;

	char ui_name[BUFSIZ];
	char ui_level[BUFSIZ];

	player = player_create((char [16]){ "temp" });
	p_obj = player_as_object(player);

	object_set_x(p_obj, 4);
	object_set_y(p_obj, 5);

	screen_setup();

	board = ui_create(SCREEN_XSTART(BOARD), SCREEN_YSTART(BOARD),
		   	  SCREEN_CSIZE(BOARD), SCREEN_RSIZE(BOARD));
	panel = ui_create(SCREEN_XSTART(UI), SCREEN_YSTART(UI),
		   	  SCREEN_CSIZE(UI), SCREEN_RSIZE(UI));

	snprintf(ui_name, BUFSIZ, "name: %s", player_get_name(player));
	ui_add_string(panel, 1, 0, ui_name, BUFSIZ);

	snprintf(ui_level, BUFSIZ, "level: %d", player_get_level(player));
	ui_add_string(panel, 1, 1, ui_level, BUFSIZ);

	int ch;
	do {
		int map_x = SCREEN_XSTART(BOARD) + 1;
		int map_y = SCREEN_YSTART(BOARD) + 1;
		int x, y;

		screen_draw_ui();
		screen_draw_map(map_x, map_y, temp_map);
		screen_draw_object(p_obj);

		ch = screen_get_input();

		x = object_get_x(p_obj);
		y = object_get_y(p_obj);

		switch (ch) {
		case KEY_LEFT:	x--; break;
		case KEY_RIGHT:	x++; break;
		case KEY_UP:	y--; break;
		case KEY_DOWN:	y++; break;
		}

		if (check_movable(temp_map, x - map_x, y - map_y)) {
			object_set_x(p_obj, x);
			object_set_y(p_obj, y);
		}
	} while (ch != '\n');

	player_destroy(player);

	ui_del_string(panel, ui_name);
	ui_del_string(panel, ui_level);

	ui_destroy(panel);
	ui_destroy(board);

	screen_cleanup();

	return 0;
}

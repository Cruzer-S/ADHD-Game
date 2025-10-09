#include "player.h"
#include "screen.h"
#include "ui.h"

#include <ncurses.h>

int main(void)
{
	Player player;
	Object p_obj;

	UI map_border, user_panel;
	int map_width, map_height;

	player = player_create((char [16]){ "temp" });
	p_obj = player_as_object(player);

	object_set_x(p_obj, 4);
	object_set_y(p_obj, 5);

	screen_setup();

	map_width = map_get_size_x(temp_map);
	map_height = map_get_size_y(temp_map);

	map_border = ui_create(0, 0, map_width + 2, map_height + 2);
	user_panel = ui_create((map_width + 2) + 1, 0, 10, map_height + 2);

	int ch;
	do {
		int x, y;

		screen_draw_ui();
		screen_draw_map(1, 1, temp_map);
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

		object_set_x(p_obj, x);
		object_set_y(p_obj, y);
	} while (ch != '\n');

	player_destroy(player);

	ui_destroy(user_panel);
	ui_destroy(map_border);

	screen_cleanup();

	return 0;
}

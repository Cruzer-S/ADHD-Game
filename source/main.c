#include "player.h"
#include "screen.h"
#include "ui.h"

#include <ncurses.h>

int main(void)
{
	Player player;
	UI map_border, user_panel;
	int map_width, map_height;

	player = player_create((char [16]){ "temp" });
	object_set_x(player_as_object(player), 4);
	object_set_y(player_as_object(player), 5);

	screen_setup();

	map_width = map_get_size_x(temp_map);
	map_height = map_get_size_y(temp_map);

	map_border = ui_create(0, 0, map_width + 2, map_height + 2);
	user_panel = ui_create((map_width + 2) + 1, 0, 10, map_height + 2);

	int ch;
	do {
		Object object;

		object = player_as_object(player);

		screen_draw_ui();
		screen_draw_map(1, 1, temp_map);
		screen_draw_object(object);

		ch = screen_get_input();

		int x, y;

		x = object_get_x(object);
		y = object_get_y(object);

		switch (ch) {
		case KEY_LEFT:	x--; break;
		case KEY_RIGHT:	x++; break;
		case KEY_UP:	y--; break;
		case KEY_DOWN:	y++; break;
		}

		object_set_x(object, x);
		object_set_y(object, y);
	} while (ch != '\n');

	ui_destroy(user_panel);
	ui_destroy(map_border);

	screen_cleanup();

	return 0;
}

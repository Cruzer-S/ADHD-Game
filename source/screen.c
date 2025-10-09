#include "screen.h"

#include <ncurses.h>

void screen_setup(void)
{
	initscr();
	cbreak();
	noecho();
	keypad(stdscr, true);

	curs_set(0);
}

void screen_draw_map(int start_x, int start_y, Map map)
{
	for (int y = 0; y < map_get_size_y(map); y++)
		for (int x = 0; x < map_get_size_x(map); x++)
			mvaddch(start_y + y, start_x + x,
	   			img2chr[map_get_tile(map, x, y)->image]);
}

void screen_draw_object(Object obj)
{
	int x, y;
	enum image image;

	x = object_get_x(obj);
	y = object_get_y(obj);

	image = object_get_image(obj);

	mvaddch(y, x, img2chr[image]);
}

void screen_add_ui(UI ui)
{
	// do nothing
}

void screen_draw_ui(void)
{
	ui_update();
	doupdate();
}

void screen_cleanup(void)
{
	endwin();
}

int screen_get_input(void)
{
	return getch();
}

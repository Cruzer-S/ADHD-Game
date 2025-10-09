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

void screen_draw_map(Map map)
{
	for (int y = 0; y < map_get_size_y(map); y++)
		for (int x = 0; x < map_get_size_x(map); x++)
			mvaddch(y, x, img2chr[map_get_image(map, x, y)]);
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

void screen_cleanup(void)
{
	endwin();
}

int screen_get_input(void)
{
	return getch();
}

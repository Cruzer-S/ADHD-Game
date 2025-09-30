#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "player.h"
#include "image.h"

#include <ncurses.h>

static Player create_player(void)
{
	Player player;

	char name[PLAYER_NAME_MAX + 1];
	char fmt[16];

	snprintf(fmt, 16, "%%%ds", PLAYER_NAME_MAX);

	printf("enter name: ");
	if (scanf(fmt, name) != 1)
		return NULL;

	player = player_create(name);
	if (player == NULL)
		return NULL;

	return player;
}

static void draw_map(void)
{
	static enum image map[10][10] = {
		{ 0, 0, 0, 0, 1, 1, 0, 0, 0, 0 },
		{ 0, 1, 0, 0, 0, 0, 0, 1, 1, 0 },
		{ 0, 1, 0, 0, 0, 0, 0, 1, 1, 1 },
		{ 0, 0, 1, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 1, 0, 0, 1, 1, 0, 0, 0 },
		{ 0, 0, 0, 1, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 1, 0, 0, 0, 0, 0, 0, 0, 1, 1 },
		{ 0, 0, 1, 0, 0, 0, 0, 0, 1, 0 },
	};

	for (int y = 0; y < 10; y++)
		for (int x = 0; x < 10; x++)
			mvaddch(y, x, img2chr[map[y][x]]);
}

static void draw_object(Object obj)
{
	int x, y;
	enum image image;

	x = object_get_x(obj);
	y = object_get_y(obj);

	image = object_get_image(obj);

	mvaddch(y, x, img2chr[image]);
}

int main(void)
{
	Player player;

	player = create_player();
	if (player == NULL) {
		fprintf(stderr, "failed to create player\n");
		exit(EXIT_FAILURE);
	}

	printf("name: %s\n", player_get_name(player));
	printf("level: %d\n", player_get_level(player));

	object_set_xy(player_as_object(player), 2, 5);

	initscr();

	do {
		draw_map();
		draw_object(player_as_object(player));
	} while (getch());

	player_destroy(player);

	endwin();

	return 0;
}

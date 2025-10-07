#include <stdlib.h>
#include <stdbool.h>

#include "player.h"
#include "screen.h"
#include "map.h"

#include <ncurses.h>

int main(void)
{
	Player player;
	int key;

	player = player_create((char [PLAYER_NAME_MAX]) { "player" });
	if (player == NULL)
		exit(EXIT_FAILURE);

	object_set_xy(player_as_object(player), 2, 5);

	screen_setup();

	do {
		screen_draw_map(temp_map);
		screen_draw_object(player_as_object(player));

		key = screen_get_input();
	} while (key != '\n');

	screen_cleanup();

	player_destroy(player);

	return 0;
}

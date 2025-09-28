#include <stdio.h>
#include <stdlib.h>

#include "player.h"

Player create_player(void)
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

	return 0;
}

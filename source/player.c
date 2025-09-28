#include "player.h"

#include <stdlib.h>
#include <string.h>

struct player {
	char name[PLAYER_NAME_MAX + 1];
	int level;
};

Player player_create(char name[restrict PLAYER_NAME_MAX])
{
	Player player;

	player = malloc(sizeof(struct player));
	if (player == NULL)
		return NULL;

	strncpy(player->name, name, PLAYER_NAME_MAX);
	player->name[PLAYER_NAME_MAX] = '\0';
	player->level = 1;

	return player;
}

const char *player_get_name(Player player)
{
	return player->name;
}

int player_get_level(Player player)
{
	return player->level;
}

void player_destroy(Player player)
{
	free(player);
}

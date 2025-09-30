#include "player.h"

#include <stdlib.h>
#include <string.h>

#include "image.h"

struct player {
	Object object;

	char name[PLAYER_NAME_MAX + 1];
	int level;
};

Player player_create(char name[restrict PLAYER_NAME_MAX])
{
	Player player;

	player = malloc(sizeof(struct player));
	if (player == NULL)
		goto RETURN_NULL;

	player->object = object_create_xy(0, 0);
	if (player->object == NULL)
		goto FREE_PLAYER;

	object_set_image(player->object, IMAGE_PLAYER);

	strncpy(player->name, name, PLAYER_NAME_MAX);
	player->name[PLAYER_NAME_MAX] = '\0';
	player->level = 1;

	return player;

FREE_PLAYER:	free(player);
RETURN_NULL:	return NULL;
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
	object_destory(player->object);
	free(player);
}

Object player_as_object(Player player)
{
	return player->object;
}

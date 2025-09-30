#ifndef PLAYER_H__
#define PLAYER_H__

#define PLAYER_NAME_MAX	16

#include "object.h"

typedef struct player *Player;

Player player_create(char name[restrict PLAYER_NAME_MAX]);

const char *player_get_name(Player );
int player_get_level(Player );

void player_destroy(Player );

Object player_as_object(Player player);

#endif

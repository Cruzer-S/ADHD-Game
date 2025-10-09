#ifndef TILE_H__
#define TILE_H__

#include <stdbool.h>

#include "image.h"

typedef struct tile {
	enum image image;
	bool passable;
} *Tile;

extern struct tile tileset[];

#endif

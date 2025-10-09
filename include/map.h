#ifndef MAP_H__
#define MAP_H__

#include "tile.h"

typedef struct map *Map;

extern Map temp_map;

int map_get_size_x(Map );
int map_get_size_y(Map );

Tile map_get_tile(Map map, int x, int y);

#endif

#include "map.h"

#include "tile.h"

struct map {
	int size_x;
	int size_y;

	Tile (*board)[];
};

int map_get_size_x(Map map)
{
	return map->size_x;
}

int map_get_size_y(Map map)
{
	return map->size_y;
}

Tile map_get_tile(Map map, int x, int y)
{
	return ((Tile (*)[map->size_y]) map->board)[y][x];
}

#define T(X) (&tileset[X])
static Tile temp_board[10][10] = {
	{ T(0), T(0), T(0), T(0), T(1), T(1), T(0), T(0), T(0), T(0) },
	{ T(0), T(1), T(0), T(0), T(0), T(0), T(0), T(1), T(1), T(0) },
	{ T(0), T(1), T(0), T(0), T(0), T(0), T(0), T(1), T(1), T(1) },
	{ T(0), T(0), T(1), T(0), T(0), T(0), T(0), T(0), T(0), T(0) },
	{ T(0), T(0), T(0), T(0), T(0), T(0), T(0), T(0), T(2), T(0) },
	{ T(0), T(0), T(1), T(0), T(2), T(1), T(1), T(0), T(0), T(0) },
	{ T(0), T(0), T(0), T(1), T(2), T(0), T(0), T(2), T(0), T(0) },
	{ T(0), T(0), T(0), T(0), T(0), T(0), T(0), T(0), T(0), T(0) },
	{ T(1), T(0), T(0), T(0), T(0), T(0), T(0), T(0), T(1), T(1) },
	{ T(2), T(0), T(1), T(0), T(0), T(0), T(0), T(0), T(1), T(0) },
};
#undef T

Map temp_map = &(struct map) {
	.size_x = (sizeof(temp_board[0]) / sizeof(temp_board[0][0])),
	.size_y = (sizeof(temp_board)) / sizeof(temp_board[0]),
	.board = (Tile (*)[]) temp_board
};

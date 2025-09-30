#include "map.h"

#include "image.h"

struct map {
	int size_x;
	int size_y;

	enum image **board;
};

int map_get_size_x(Map map)
{
	return map->size_x;
}

int map_get_size_y(Map map)
{
	return map->size_y;
}

enum image map_get_image(Map map, int x, int y)
{
	return ((enum image (*)[map->size_y]) map->board)[y][x];
}

static enum image temp_board[10][10] = {
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

Map temp_map = &(struct map) {
	.size_x = (sizeof(temp_board[0]) / sizeof(temp_board[0][0])),
	.size_y = (sizeof(temp_board)) / sizeof(temp_board[0]),
	.board = (enum image **) temp_board
};

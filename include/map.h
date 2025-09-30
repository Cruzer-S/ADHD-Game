#ifndef MAP_H__
#define MAP_H__

typedef struct map *Map;

extern Map temp_map;

int map_get_size_x(Map );
int map_get_size_y(Map );

enum image map_get_image(Map, int x, int y);

#endif

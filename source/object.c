#include "object.h"

#include <stdlib.h>

struct object {
	enum image image;

	int x;
	int y;
};

Object object_create(void)
{
	return object_create_xy(-1, -1);
}

Object object_create_xy(int x, int y)
{
	Object object = malloc(sizeof(struct object));

	if (object == NULL)
		return NULL;

	object_set_xy(object, x, y);
	object_set_image(object, IMAGE_SPACE);

	return object;
}

int object_get_x(Object object)
{
	return object->x;
}

int object_get_y(Object object)
{
	return object->y;
}

enum image object_get_image(Object object)
{
	return object->image;
}

void object_set_x(Object object, int x)
{
	object->x = x;
}

void object_set_y(Object object, int y)
{
	object->y = y;
}

void object_set_xy(Object object, int x, int y)
{
	object->x = x;
	object->y = y;
}

void object_set_image(Object object, enum image image)
{
	object->image = image;
}

void object_destory(Object object)
{
	free(object);
}

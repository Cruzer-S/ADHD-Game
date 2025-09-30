#ifndef OBJECT_H__
#define OBJECT_H__

#include "image.h"

typedef struct object *Object;

Object object_create(void);
Object object_create_xy(int x, int y);

int object_get_x(Object );
int object_get_y(Object );

enum image object_get_image(Object );

void object_set_x(Object , int );
void object_set_y(Object , int );
void object_set_xy(Object, int , int );

void object_set_image(Object , enum image );

void object_destory(Object );

#endif

#ifndef OBJECT_LIBERATOR_H
# define OBJECT_LIBERATOR_H
# include "../minirt.h"

typedef void(*t_obj_liberator)(void *);
t_obj_liberator g_obj_liberator[8];

void init_object_liberator(void);
void free_object(void *object);

void free_camera(void *obj);
void free_light(void *obj);
void free_sphere(void *obj);
void free_plane(void *obj);
void free_square(void *obj);
void free_cylinder(void *obj);
void free_triangle(void *obj);

#endif
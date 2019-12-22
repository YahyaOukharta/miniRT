#ifndef OBJECT_PRINTER_H
# define OBJECT_PRINTER_H

#include "../minirt.h"


int print_cam(void *obj);
int print_light(void *obj);
int print_sphere(void *obj);
int print_plane(void *obj);
int print_square(void *obj);
int print_cylinder(void *obj);
int print_triangle(void *obj);

typedef int(*t_obj_printer)(void *);
t_obj_printer g_obj_printer[8];

int print_objs(void);
void init_obj_printer(void);

#endif
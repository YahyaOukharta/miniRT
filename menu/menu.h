#ifndef MENU_H
#define MENU_H

#include "../minirt.h"
int init_menu(void);
int show_menu(void);
int menu_toggle_msg(void);
int selected_objects_msg(void);




char **get_camera_details(t_object *obj);
char **get_light_details(t_object *obj);
char **get_sphere_details(t_object *obj);
char **get_plane_details(t_object *obj);
char **get_square_details(t_object *obj);
char **get_cylinder_details(t_object *obj);
char **get_triangle_details(t_object *obj);

typedef char**(*t_obj_details)(t_object *);
t_obj_details g_obj_details[8];

void init_obj_details(void);
#endif
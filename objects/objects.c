#include "objects.h"

extern t_list *objects;

int set_resolution(char **tab)
{   
    g_resolution.is_set = 1;
    g_resolution.x = ft_atoi(tab[1]);
    g_resolution.y = ft_atoi(tab[2]);
    return (1);
}
int set_ambient_light(char **tab)
{   
    g_ambient_light.is_set = 1;
    g_ambient_light.brightness = ft_atof(tab[1]);
    g_ambient_light.color = rgb_to_int(tab[2]);
    return (1);
}

// typedef struct	s_camera
// {
// 	t_vector pos;
// 	t_vector dir;

// 	int		fov; //probably
// }				t_camera;
t_camera *new_camera(char **info)
{
    t_camera *new_cam;
    char **tab;

    new_cam = (t_camera *)malloc(sizeof(t_camera));
    tab = ft_split(info[1], ',');
    ft_printf("tab_len = %d , 1 = %s 2 = %s 3 = %s\n",tab_len(tab),tab[0],tab[1],tab[2]);
    new_cam->pos.x = ft_atof(tab[0]);
    new_cam->pos.y = ft_atof(tab[1]);
    new_cam->pos.z = ft_atof(tab[2]);

    tab = ft_split(info[2], ',');
    new_cam->dir.x = ft_atof(tab[0]);
    new_cam->dir.y = ft_atof(tab[1]);
    new_cam->dir.z = ft_atof(tab[2]);

    new_cam->fov = ft_atof(info[3]);
    return (new_cam);
}

int add_camera(char **tab)
{
    t_object *obj;

    obj = (t_object *)malloc(sizeof(t_object));
    obj->type = tab[0];
    obj->details = (void *)new_camera(tab);
    ft_lstadd_back(&objects, ft_lstnew(obj));
    return (1);
}
t_light *new_light(char **info)
{
    t_light *new_light;
    char **tab;

    new_light = (t_light *)malloc(sizeof(t_light));
    tab = ft_split(info[1], ',');
    ft_printf("tab_len = %d , 1 = %s 2 = %s 3 = %s\n",tab_len(tab),tab[0],tab[1],tab[2]);
    new_light->pos.x = ft_atof(tab[0]);
    new_light->pos.y = ft_atof(tab[1]);
    new_light->pos.z = ft_atof(tab[2]);

    new_light->brightness = ft_atof(info[2]);
    new_light->color = rgb_to_int(info[3]);
    return (new_light);
}

int add_light(char **tab)
{
    t_object *obj;

    obj = (t_object *)malloc(sizeof(t_object));
    obj->type = tab[0];
    obj->details = (void *)new_light(tab);
    ft_lstadd_back(&objects, ft_lstnew(obj));
    return (1);
}

void init_obj_constructor(void){
    g_obj_constructor[0] = set_resolution;
    g_obj_constructor[1] = set_ambient_light;
    g_obj_constructor[2] = add_camera;
    g_obj_constructor[3] = add_light;
    // g_obj_constructor[4] = check_info_sphere;
    // g_obj_constructor[5] = check_info_plane;
    //g_obj_constructor[6] = check_info_square;
    //g_obj_constructor[7] = check_info_cylinder;
    //g_obj_constructor[8] = check_info_triangle;
}
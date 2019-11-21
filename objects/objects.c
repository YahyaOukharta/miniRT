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
    new_cam->pos.x = ft_atof(tab[0]);
    new_cam->pos.y = ft_atof(tab[1]);
    new_cam->pos.z = ft_atof(tab[2]);
    free_s_tab(tab);

    tab = ft_split(info[2], ',');
    new_cam->dir.x = ft_atof(tab[0]);
    new_cam->dir.y = ft_atof(tab[1]);
    new_cam->dir.z = ft_atof(tab[2]);
    free_s_tab(tab);

    new_cam->fov = ft_atof(info[3]);
    return (new_cam);
}

int add_camera(char **tab)
{
    t_object *obj;

    obj = (t_object *)malloc(sizeof(t_object));
    obj->type = ft_strdup(tab[0]);
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
    new_light->pos.x = ft_atof(tab[0]);
    new_light->pos.y = ft_atof(tab[1]);
    new_light->pos.z = ft_atof(tab[2]);
   free_s_tab(tab);

    new_light->brightness = ft_atof(info[2]);
    new_light->color = rgb_to_int(info[3]);
    return (new_light);
}

int add_light(char **tab)
{
    t_object *obj;

    obj = (t_object *)malloc(sizeof(t_object));
    obj->type = ft_strdup(tab[0]);
    obj->details = (void *)new_light(tab);
    ft_lstadd_back(&objects, ft_lstnew(obj));
    return (1);
}
t_sphere *new_sphere(char **info)
{
    t_sphere *new_sphere;
    char **tab;

    new_sphere = (t_sphere *)malloc(sizeof(t_sphere));
    tab = ft_split(info[1], ',');
    new_sphere->pos.x = ft_atof(tab[0]);
    new_sphere->pos.y = ft_atof(tab[1]);
    new_sphere->pos.z = ft_atof(tab[2]);
   free_s_tab(tab);

    new_sphere->diameter = ft_atof(info[2]);
    new_sphere->color = rgb_to_int(info[3]);
    return (new_sphere);
}

int add_sphere(char **tab)
{
    t_object *obj;

    obj = (t_object *)malloc(sizeof(t_object));
    obj->type = ft_strdup(tab[0]);
    obj->details = (void *)new_sphere(tab);
    ft_lstadd_back(&objects, ft_lstnew(obj));
    return (1);
}
t_plane *new_plane(char **info)
{
    t_plane *new_plane;
    char **tab;

    new_plane = (t_plane *)malloc(sizeof(t_plane));
    tab = ft_split(info[1], ',');
    new_plane->pos.x = ft_atof(tab[0]);
    new_plane->pos.y = ft_atof(tab[1]);
    new_plane->pos.z = ft_atof(tab[2]);
   free_s_tab(tab);

    tab = ft_split(info[2], ',');
    new_plane->orientation.x = ft_atof(tab[0]);
    new_plane->orientation.y = ft_atof(tab[1]);
    new_plane->orientation.z = ft_atof(tab[2]);
   free_s_tab(tab);

    new_plane->color = rgb_to_int(info[3]);
    return (new_plane);
}

int add_plane(char **tab)
{
    t_object *obj;

    obj = (t_object *)malloc(sizeof(t_object));
    obj->type = ft_strdup(tab[0]);
    obj->details = (void *)new_plane(tab);
    ft_lstadd_back(&objects, ft_lstnew(obj));
    return (1);
}
t_square *new_square(char **info)
{
    t_square *new_square;
    char **tab;

    new_square = (t_square *)malloc(sizeof(t_square));
    tab = ft_split(info[1], ',');
    new_square->pos.x = ft_atof(tab[0]);
    new_square->pos.y = ft_atof(tab[1]);
    new_square->pos.z = ft_atof(tab[2]);
    free_s_tab(tab);

    tab = ft_split(info[2], ',');
    new_square->orientation.x = ft_atof(tab[0]);
    new_square->orientation.y = ft_atof(tab[1]);
    new_square->orientation.z = ft_atof(tab[2]);
    free_s_tab(tab);

    new_square->side_size = ft_atof(info[3]);
    new_square->color = rgb_to_int(info[4]);
    return (new_square);
}

int add_square(char **tab)
{
    t_object *obj;

    obj = (t_object *)malloc(sizeof(t_object));
    obj->type = ft_strdup(tab[0]);
    obj->details = (void *)new_square(tab);
    ft_lstadd_back(&objects, ft_lstnew(obj));
    return (1);
}
t_cylinder *new_cylinder(char **info)
{
    t_cylinder *new_cylinder;
    char **tab;

    new_cylinder = (t_cylinder *)malloc(sizeof(t_cylinder));
    tab = ft_split(info[1], ',');
    new_cylinder->pos.x = ft_atof(tab[0]);
    new_cylinder->pos.y = ft_atof(tab[1]);
    new_cylinder->pos.z = ft_atof(tab[2]);
   free_s_tab(tab);

    tab = ft_split(info[2], ',');
    new_cylinder->orientation.x = ft_atof(tab[0]);
    new_cylinder->orientation.y = ft_atof(tab[1]);
    new_cylinder->orientation.z = ft_atof(tab[2]);
    free_s_tab(tab);
   
    new_cylinder->diameter = ft_atof(info[3]);
    new_cylinder->height = ft_atof(info[4]);
    new_cylinder->color = rgb_to_int(info[5]);
   
    return (new_cylinder);
}

int add_cylinder(char **tab)
{
    t_object *obj;

    obj = (t_object *)malloc(sizeof(t_object));
    obj->type = ft_strdup(tab[0]);
    obj->details = (void *)new_cylinder(tab);
    ft_lstadd_back(&objects, ft_lstnew(obj));
    return (1);
}
t_triangle *new_triangle(char **info)
{
    t_triangle *new_triangle;
    char **tab;

    new_triangle = (t_triangle *)malloc(sizeof(t_triangle));

    tab = ft_split(info[1], ',');
    new_triangle->p1.x = ft_atof(tab[0]);
    new_triangle->p1.y = ft_atof(tab[1]);
    new_triangle->p1.z = ft_atof(tab[2]);
  free_s_tab(tab);

    tab = ft_split(info[2], ',');
    new_triangle->p2.x = ft_atof(tab[0]);
    new_triangle->p2.y = ft_atof(tab[1]);
    new_triangle->p2.z = ft_atof(tab[2]);
   free_s_tab(tab);

    tab = ft_split(info[3], ',');
    new_triangle->p3.x = ft_atof(tab[0]);
    new_triangle->p3.y = ft_atof(tab[1]);
    new_triangle->p3.z = ft_atof(tab[2]);
   free_s_tab(tab);

    new_triangle->color = rgb_to_int(info[4]);
    return (new_triangle);
}

int add_triangle(char **tab)
{
    t_object *obj;

    obj = (t_object *)malloc(sizeof(t_object));
    obj->type = ft_strdup(tab[0]);
    obj->details = (void *)new_triangle(tab);
    ft_lstadd_back(&objects, ft_lstnew(obj));
    return (1);
}

void init_obj_constructor(void){
    g_obj_constructor[0] = set_resolution;
    g_obj_constructor[1] = set_ambient_light;
    g_obj_constructor[2] = add_camera;
    g_obj_constructor[3] = add_light;
    g_obj_constructor[4] = add_sphere;
    g_obj_constructor[5] = add_plane;
    g_obj_constructor[6] = add_square;
    g_obj_constructor[7] = add_cylinder;
    g_obj_constructor[8] = add_triangle;
}
#include "objects.h"

#include "../minirt.h"
extern struct s_minirt g_rt;

int set_resolution(char **tab)
{   
    g_rt.g_res.is_set = 1;
    g_rt.g_res.x = ft_atoi(tab[1]);
    g_rt.g_res.y = ft_atoi(tab[2]);
    return (1);
}
int set_ambient_light(char **tab)
{   
    g_rt.g_ambient_light.is_set = 1;
    g_rt.g_ambient_light.brightness = ft_atof(tab[1]);
    g_rt.g_ambient_light.color = rgb_to_int(tab[2]);
    return (1);
}

t_cam *new_camera(char **info)
{
    t_cam *new_cam;
    char **tab;

    new_cam = (t_cam *)malloc(sizeof(t_cam));
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
    t_vector tmp;

    tmp = vec_normalize(new_cam->dir);
    tmp.x = 0;
    tmp = vec_normalize(tmp);
    float Rx = acos(vec_dot(vec_create(0,0,-1),tmp));

    tmp = vec_normalize(new_cam->dir);
    tmp.y = 0;
    tmp = vec_normalize(tmp);
    float Ry = acos(vec_dot(vec_create(0,0,-1),tmp));
    new_cam->rot = vec_create(Rx,Ry,0);
    return (new_cam);
}

int add_camera(char **tab)
{
    t_obj *obj;

    obj = (t_obj *)malloc(sizeof(t_obj));
    obj->type = ft_strdup(tab[0]);
    obj->details = (void *)new_camera(tab);
    ft_lstadd_back(&g_rt.cameras, ft_lstnew(obj));
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
    t_obj *obj;

    obj = (t_obj *)malloc(sizeof(t_obj));
    obj->type = ft_strdup(tab[0]);
    obj->details = (void *)new_light(tab);
    ft_lstadd_back(&g_rt.lights, ft_lstnew(obj));
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
    t_obj *obj;

    obj = (t_obj *)malloc(sizeof(t_obj));
    obj->type = ft_strdup(tab[0]);
    obj->details = (void *)new_sphere(tab);
    ft_lstadd_back(&g_rt.objects, ft_lstnew(obj));
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
    t_obj *obj;

    obj = (t_obj *)malloc(sizeof(t_obj));
    obj->type = ft_strdup(tab[0]);
    obj->details = (void *)new_plane(tab);
    ft_lstadd_back(&g_rt.objects, ft_lstnew(obj));
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
    t_obj *obj;

    obj = (t_obj *)malloc(sizeof(t_obj));
    obj->type = ft_strdup(tab[0]);
    obj->details = (void *)new_square(tab);
    ft_lstadd_back(&g_rt.objects, ft_lstnew(obj));
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
    t_obj *obj;

    obj = (t_obj *)malloc(sizeof(t_obj));
    obj->type = ft_strdup(tab[0]);
    obj->details = (void *)new_cylinder(tab);
    ft_lstadd_back(&g_rt.objects, ft_lstnew(obj));
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
    t_obj *obj;

    obj = (t_obj *)malloc(sizeof(t_obj));
    obj->type = ft_strdup(tab[0]);
    obj->details = (void *)new_triangle(tab);
    ft_lstadd_back(&g_rt.objects, ft_lstnew(obj));
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
//
int	transform_sphere(int key, void *param)
{
	t_sphere *sphere = (t_sphere *)g_rt.selected_object->details;
    t_cam *cam = (t_cam *)((t_obj *)g_rt.curr_cam->content)->details;
	float vel = 0.1;
	if (key == KEY_D)
		sphere->pos = vec_add(sphere->pos,vec_mult(vec_rotate(vec_create(1,0,0), cam->rot),vel));
	if (key == KEY_A)
		sphere->pos = vec_add(sphere->pos,vec_mult(vec_rotate(vec_create(1,0,0), cam->rot),-vel));
	if (key == KEY_W)
		sphere->pos = vec_add(sphere->pos,vec_mult(vec_rotate(vec_create(0,1,0), cam->rot),vel));
	if (key == KEY_S)
		sphere->pos = vec_add(sphere->pos,vec_mult(vec_rotate(vec_create(0,1,0), cam->rot),-vel));
	return (0);
}
int	transform_plane(int key, void *param)
{
	t_plane *plane = (t_plane *)g_rt.selected_object->details;
    t_cam *cam = (t_cam *)((t_obj *)g_rt.curr_cam->content)->details;
	float vel = 0.1;
	if (key == KEY_D)
		plane->pos = vec_add(plane->pos,vec_mult(vec_rotate(vec_create(1,0,0), cam->rot),vel));
	if (key == KEY_A)
		plane->pos = vec_add(plane->pos,vec_mult(vec_rotate(vec_create(1,0,0), cam->rot),-vel));
	if (key == KEY_W)
		plane->pos = vec_add(plane->pos,vec_mult(vec_rotate(vec_create(0,1,0), cam->rot),vel));
	if (key == KEY_S)
		plane->pos = vec_add(plane->pos,vec_mult(vec_rotate(vec_create(0,1,0), cam->rot),-vel));
    if (key == KEY_RIGHT)
    	rotate_y(&plane->orientation.x,&plane->orientation.z,vel);
	if (key == KEY_LEFT)
    	rotate_y(&plane->orientation.x,&plane->orientation.z,-vel);
	if (key == KEY_UP)
    	rotate_x(&plane->orientation.y,&plane->orientation.z,vel);
	if (key == KEY_DOWN)
    	rotate_x(&plane->orientation.y,&plane->orientation.z,-vel);
	return (0);
}
int	transform_square(int key, void *param)
{
	t_square *square = (t_square *)g_rt.selected_object->details;
    t_cam *cam = (t_cam *)((t_obj *)g_rt.curr_cam->content)->details;
	float vel = 0.1;
	if (key == KEY_D)
		square->pos = vec_add(square->pos,vec_mult(vec_rotate(vec_create(1,0,0), cam->rot),vel));
	if (key == KEY_A)
		square->pos = vec_add(square->pos,vec_mult(vec_rotate(vec_create(1,0,0), cam->rot),-vel));
	if (key == KEY_W)
		square->pos = vec_add(square->pos,vec_mult(vec_rotate(vec_create(0,1,0), cam->rot),vel));
	if (key == KEY_S)
		square->pos = vec_add(square->pos,vec_mult(vec_rotate(vec_create(0,1,0), cam->rot),-vel));
    if (key == KEY_RIGHT)
    	rotate_y(&square->orientation.x,&square->orientation.z,vel);
	if (key == KEY_LEFT)
    	rotate_y(&square->orientation.x,&square->orientation.z,-vel);
	if (key == KEY_UP)
    	rotate_x(&square->orientation.y,&square->orientation.z,vel);
	if (key == KEY_DOWN)
    	rotate_x(&square->orientation.y,&square->orientation.z,-vel);
	return (0);
}
int	transform_triangle(int key, void *param)
{
	t_triangle *tri = (t_triangle *)g_rt.selected_object->details;
    t_cam *cam = (t_cam *)((t_obj *)g_rt.curr_cam->content)->details;
	float vel = 0.1;
    t_vector dir;
	if (key == KEY_D || key == KEY_A)
	{	
        dir = vec_mult(vec_rotate(vec_create(1,0,0), cam->rot),(key == KEY_D ? 1 : -1) * vel);
        tri->p1 = vec_add(tri->p1,dir);
        tri->p2 = vec_add(tri->p2,dir);
        tri->p3 = vec_add(tri->p3,dir);
    }
	if (key == KEY_W || key == KEY_S)
	{	
        dir = vec_mult(vec_rotate(vec_create(0,1,0), cam->rot),(key == KEY_D ? 1 : -1) * vel);
        tri->p1 = vec_add(tri->p1,dir);
        tri->p2 = vec_add(tri->p2,dir);
        tri->p3 = vec_add(tri->p3,dir);
    }
	return (0);
}
int	transform_light(int key, void *param)
{
	t_light *light = (t_light *)g_rt.selected_object->details;
    t_cam *cam = (t_cam *)((t_obj *)g_rt.curr_cam->content)->details;
	float vel = 0.1;
	if (key == KEY_D)
		light->pos = vec_add(light->pos,vec_mult(vec_rotate(vec_create(1,0,0), cam->rot),vel));
	if (key == KEY_A)
		light->pos = vec_add(light->pos,vec_mult(vec_rotate(vec_create(1,0,0), cam->rot),-vel));
	if (key == KEY_W)
		light->pos = vec_add(light->pos,vec_mult(vec_rotate(vec_create(0,1,0), cam->rot),vel));
	if (key == KEY_S)
		light->pos = vec_add(light->pos,vec_mult(vec_rotate(vec_create(0,1,0), cam->rot),-vel));
	return (0);
}
int	transform_cylinder(int key, void *param)
{
	t_cylinder *cylinder = (t_cylinder *)g_rt.selected_object->details;
    t_cam *cam = (t_cam *)((t_obj *)g_rt.curr_cam->content)->details;
	float vel = 0.1;
	if (key == KEY_D)
		cylinder->pos = vec_add(cylinder->pos,vec_mult(vec_rotate(vec_create(1,0,0), cam->rot),vel));
	if (key == KEY_A)
		cylinder->pos = vec_add(cylinder->pos,vec_mult(vec_rotate(vec_create(1,0,0), cam->rot),-vel));
	if (key == KEY_W)
		cylinder->pos = vec_add(cylinder->pos,vec_mult(vec_rotate(vec_create(0,1,0), cam->rot),vel));
	if (key == KEY_S)
		cylinder->pos = vec_add(cylinder->pos,vec_mult(vec_rotate(vec_create(0,1,0), cam->rot),-vel));
    if (key == KEY_RIGHT)
       cylinder->orientation = vec_rotate(cylinder->orientation, vec_create(0,0,vel));
    if (key == KEY_LEFT)
        cylinder->orientation = vec_rotate(cylinder->orientation, vec_create(0,0,-vel));
	if (key == KEY_UP)
        cylinder->orientation = vec_rotate(cylinder->orientation, vec_create(vel,0,0));
	if (key == KEY_DOWN)
        cylinder->orientation = vec_rotate(cylinder->orientation, vec_create(-vel,0,0));
	return (0);
}
void init_obj_transformer(void){
    g_obj_transformer[0] = transform_light;
    g_obj_transformer[1] = transform_sphere;
    g_obj_transformer[2] = transform_plane;
    g_obj_transformer[3] = transform_square;
    g_obj_transformer[4] = transform_cylinder;
    g_obj_transformer[5] = transform_triangle;
}
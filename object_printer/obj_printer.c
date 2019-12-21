#include "obj_printer.h"

extern struct s_minirt g_rt;

int print_objs(t_list *objects)
{
    t_obj *obj;
    int index;
    char **tmp;
	
    if (g_rt.g_res.is_set)
		ft_printf("Resolution    = %dx%d\t\t", g_rt.g_res.x,g_rt.g_res.y);
	if (g_rt.g_ambient_light.is_set)
		printf("Ambient light = %.2f, %d\n\n", g_rt.g_ambient_light.brightness, g_rt.g_ambient_light.color);
    init_obj_printer();
    while (objects)
    {
        obj = (t_obj *)(g_rt.objects->content);
        index = index_of_in_tab(obj->type,
            (tmp = ft_split(g_rt.g_supported_objects, ';'))) - 2;
        free_s_tab(tmp);
        g_obj_printer[index](obj->details);
        objects = objects->next;
    }
    return (1);
}



int print_cam(void *obj)
{   
    t_cam *cam = (t_cam *)obj;
    printf("camera      pos %.2f %.2f %.2f dir %.2f %.2f %.2f fov %d\n",cam->pos.x,cam->pos.y,cam->pos.z,cam->dir.x,cam->dir.y,cam->dir.z,cam->fov);
	return (1);
}
int print_light(void *object)
{
    t_light *light = (t_light *)object;
	printf("light       pos %.2f %.2f %.2f brightness %.2f color %d\n",light->pos.x,light->pos.y,light->pos.z, light->brightness, light->color);
	return (1);
}
int print_sphere(void *object)
{
    t_sphere *sphere = (t_sphere *)object;
	printf("sphere      pos %.2f %.2f %.2f diameter %.2f color %d\n",sphere->pos.x,sphere->pos.y,sphere->pos.z, sphere->diameter, sphere->color);
	return (1);
}
int print_plane(void *object)
{

    t_plane *plane = (t_plane *)object;
	printf("plane       pos %.2f %.2f %.2f color %d\n",plane->pos.x,plane->pos.y,plane->pos.z, plane->color);
	return (1);
}
int print_square(void *object)
{
    t_square *square = (t_square *)object;
	printf("square      pos %.2f %.2f %.2f side_size %.2f color %d\n",square->pos.x,square->pos.y,square->pos.z, square->side_size,square->color);
	return (1);
}
int print_cylinder(void *object)
{
    t_cylinder *cylinder = (t_cylinder *)object;
	printf("cylinder    pos %.2f %.2f %.2f diameter %.2f height %.2f color %d\n",cylinder->pos.x,cylinder->pos.y,cylinder->pos.z, cylinder->diameter,cylinder->height,cylinder->color);
	return (1);
}
int print_triangle(void *object)
{
    t_triangle *triangle = (t_triangle *)object;
	printf("triangle    p1 %.2f %.2f %.2f p2 %.2f %.2f %.2f p3 %.2f %.2f %.2f color %d\n",triangle->p1.x,triangle->p1.y,triangle->p1.z, triangle->p2.x,triangle->p2.y,triangle->p2.z,triangle->p3.x,triangle->p3.y,triangle->p3.z,triangle->color);
	return (1);
}
void init_obj_printer(void)
{
    g_obj_printer[0] = print_cam;
    g_obj_printer[1] = print_light;
    g_obj_printer[2] = print_sphere;
    g_obj_printer[3] = print_plane;
    g_obj_printer[4] = print_square;
    g_obj_printer[5] = print_cylinder;
    g_obj_printer[6] = print_triangle;
}

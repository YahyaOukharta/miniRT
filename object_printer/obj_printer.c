#include "obj_printer.h"

extern char	*g_supported_objects;

int print_objects(t_list *objects)
{
    t_object *obj;
    int index;

    init_object_printer();
    while (objects)
    {
        obj = (t_object *)(objects->content);
        index = index_of_in_tab(obj->type, ft_split(g_supported_objects, ';')) - 2;
        ft_printf("index = %d\n",index);
        g_obj_printer[index](obj->details);
        objects = objects->next;
    }
    return (1);
}

int print_camera(void *obj)
{   
    t_camera *cam = (t_camera *)obj;
    printf("camera pos %.2f %.2f %.2f fov %d\n",cam->pos.x,cam->pos.y,cam->pos.z,cam->fov);
	return (1);
}
int print_light(void *object)
{
    t_light *light = (t_light *)object;
	printf("light pos %.2f %.2f %.2f brightness %.2f color %d\n",light->pos.x,light->pos.y,light->pos.z, light->brightness, light->color);
	return (1);
}
int print_sphere(void *object)
{
    t_sphere *sphere = (t_sphere *)object;
	printf("sphere pos %.2f %.2f %.2f diameter %.2f color %d\n",sphere->pos.x,sphere->pos.y,sphere->pos.z, sphere->diameter, sphere->color);
	return (1);
}
int print_plane(void *object)
{

    t_plane *plane = (t_plane *)object;
	printf("plane pos %.2f %.2f %.2f color %d\n",plane->pos.x,plane->pos.y,plane->pos.z, plane->color);
	return (1);
}
int print_square(void *object)
{
    t_square *square = (t_square *)object;
	printf("square pos %.2f %.2f %.2f side_size %.2f color %d\n",square->pos.x,square->pos.y,square->pos.z, square->side_size,square->color);
	return (1);
}
int print_cylinder(void *object)
{
    t_cylinder *cylinder = (t_cylinder *)object;
	printf("cylinder pos %.2f %.2f %.2f diameter %.2f height %.2f color %d\n",cylinder->pos.x,cylinder->pos.y,cylinder->pos.z, cylinder->diameter,cylinder->height,cylinder->color);
	return (1);
}
int print_triangle(void *object)
{
    t_triangle *triangle = (t_triangle *)object;
	printf("triangle p1 %.2f %.2f %.2f p2 %.2f %.2f %.2f p3 %.2f %.2f %.2f color %d\n",triangle->p1.x,triangle->p1.y,triangle->p1.z, triangle->p2.x,triangle->p2.y,triangle->p2.z,triangle->p3.x,triangle->p3.y,triangle->p3.z,triangle->color);
	return (1);
}
void init_object_printer(void)
{
    g_obj_printer[0] = print_camera;
    g_obj_printer[1] = print_light;
    g_obj_printer[2] = print_sphere;
    g_obj_printer[3] = print_plane;
    g_obj_printer[4] = print_square;
    g_obj_printer[5] = print_cylinder;
    g_obj_printer[6] = print_triangle;
}

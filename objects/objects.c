#include "objects.h"
#include "../minirt.h"

extern struct s_minirt g_rt;

int			set_resolution(char **tab)
{
	g_rt.g_res.is_set = 1;
	g_rt.g_res.x = ft_atoi(tab[1]);
	g_rt.g_res.y = ft_atoi(tab[2]);
	return (1);
}

int			set_ambient_light(char **tab)
{
	g_rt.g_ambient_light.is_set = 1;
	g_rt.g_ambient_light.brightness = ft_atof(tab[1]);
	g_rt.g_ambient_light.color = rgb_to_int(tab[2]);
	return (1);
}

void		init_obj_constructor(void)
{
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

void		init_obj_transformer(void)
{
	g_obj_transformer[0] = transform_light;
	g_obj_transformer[1] = transform_sphere;
	g_obj_transformer[2] = transform_plane;
	g_obj_transformer[3] = transform_square;
	g_obj_transformer[4] = transform_cylinder;
	g_obj_transformer[5] = transform_triangle;
}
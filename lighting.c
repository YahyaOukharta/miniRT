#include "minirt.h"
//lighting function
extern struct s_minirt g_minirt;

int get_ambient_color(t_intersection *closest)
{
	return (add_colors(mult_colors(g_minirt.g_ambient_light.color, g_minirt.g_ambient_light.brightness), mult_colors(closest->object_color, g_minirt.g_ambient_light.brightness)));
}
int get_diffuse_color(t_intersection *closest, t_ray shadow_ray, t_light *light)
{	
	t_vector light_dir = vec_normalize(vec_sub(light->pos,shadow_ray.pos));
	float  dot = fmax(vec_dot(closest->normal, light_dir),0);
	return (mult_colors(light->color, dot * closest->diffuse * light->brightness));
}
int get_specular_color(t_intersection *closest, t_ray ray, t_ray shadow_ray, t_light *light)
{
	t_vector light_dir = vec_normalize(vec_sub(light->pos,shadow_ray.pos));
	t_vector reflection_dir = vec_sub(ray.dir, vec_mult(closest->normal, 2 * vec_dot(ray.dir,closest->normal)));
	t_vector view_dir = vec_mult(ray.dir,-1);
	float dot =  fmax(vec_dot(reflection_dir, light_dir), 0);
	return(mult_colors(light->color, closest->specular * pow(dot, closest->s_power) * light->brightness));
}
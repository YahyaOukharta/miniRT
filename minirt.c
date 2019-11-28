/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youkhart <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/16 21:37:07 by youkhart          #+#    #+#             */
/*   Updated: 2019/11/17 09:10:37 by youkhart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "mlx.h"

char	*g_supported_objects = "R;A;c;l;sp;pl;sq;cy;tr";
struct s_ambient_light g_ambient_light;
struct s_resolution g_resolution;
t_list *objects;

void init_objects(void)
{
    g_resolution.is_set = 0;
    g_ambient_light.is_set = 0;
	init_obj_constructor();
}
//mlx struct
typedef struct    data_s
{
    void          *mlx_ptr;
    void          *mlx_win;
}                 data_t;
//lighting function
int get_ambient_color(t_intersection *closest)
{
	return (add_colors(g_ambient_light.color, mult_colors(closest->object_color, g_ambient_light.brightness)));
}
int get_diffuse_color(t_intersection *closest, t_vector light_pos ,int light_color, t_vector light_dir)
{	
	float  dot = fmax(vec_dot(closest->normal, light_dir),0);
	return (mult_colors(light_color, dot * closest->diffuse));
}
int get_specular_color(t_intersection *closest, t_ray ray, int light_color, t_vector light_dir)
{
	t_vector reflection_dir = vec_sub(ray.dir, vec_mult(closest->normal, 2 * vec_dot(ray.dir,closest->normal)));
	t_vector view_dir = vec_mult(ray.dir,-1);
	float dot =  fmax(vec_dot(reflection_dir, light_dir), 0);
	return(mult_colors(light_color, closest->specular * pow(dot, closest->s_power)));
}
t_intersection *get_closest_intersection(t_list *objects, t_ray ray)
{
	t_list *objs = objects;
	t_intersection *closest = NULL;
	t_intersection *inter = NULL;
	float min_t = INFINITY;

	while (objs)
	{
		t_object *sph = (t_object *)(objs->content);
		if (!ft_memcmp(sph->type,"sp",2))
		 	inter = intersects_with_sphere(ray, sph);
		if (!ft_strncmp(sph->type,"pl",2))
			inter = intersects_with_plane(ray, sph);		
		if (!ft_strncmp(sph->type,"tr",2))
			inter = intersects_with_triangle(ray, sph);
		// closest intersection
		if(inter && inter->t < min_t && inter->t > 0.0000001)
		{
			min_t = inter->t;
			closest = inter;
		}
		objs = objs->next;
	}
	return (closest);
}

int compute_pixel_color(t_intersection *closest,t_ray ray, t_vector light_pos, int light_color)
{
	int blocked = 0;
	float color,a_color,d_color,s_color = 0;
	t_ray shadow_ray;

	//ambient lighting
	a_color = get_ambient_color(closest);
	color = a_color;
	//cast shadow ray towards light
	shadow_ray.pos = vec_add(vec_add(ray.pos,vec_mult(ray.dir, closest->t)),vec_mult(closest->normal, 0.00000001));
	shadow_ray.dir = vec_normalize(vec_sub(light_pos , shadow_ray.pos));

	t_list *objs = objects;
	while (objs)
	{
		t_object *sph = (t_object *)(objs->content);
	
		if((!ft_memcmp(sph->type,"sp",max(ft_strlen(sph->type),2)) && intersects_with_sphere(shadow_ray, sph))
			|| (!ft_memcmp(sph->type,"pl",max(ft_strlen(sph->type),2)) && intersects_with_sphere(shadow_ray, sph))
			|| (!ft_memcmp(sph->type,"tr",max(ft_strlen(sph->type),2)) && intersects_with_triangle(shadow_ray, sph)))
		{
			blocked = 1;
			break;
		}

		objs = objs->next;
	}
	if(!blocked)
	{
		t_vector light_dir = vec_normalize(vec_sub(light_pos,shadow_ray.pos));
		//diffuse lighting
		d_color = get_diffuse_color(closest, light_pos, light_color, light_dir);
		color = add_colors(color, d_color);
		//specular lighting
		s_color = get_specular_color(closest, ray, light_color, light_dir);
		color = add_colors(color, s_color);
		printf("color = %d\n",(int)color);
	}
	return (color);
}

int main (int argc, char **argv)
{
	//mlx 
	data_t        data;
	//file processing and scene objects storing
	if (argc != 2)
		return (ft_printf("Error\n [!] Wrong numbers of arguments, Enter only one argument\n") ? 0 : 0);
	if(!process_file(argv))
		return (0);
		print_objects(objects);
    if (!(data.mlx_ptr = mlx_init()))
        return (EXIT_FAILURE);
    if (!(data.mlx_win = mlx_new_window(data.mlx_ptr, g_resolution.x, g_resolution.y, "Hello world !!!")))
        return (EXIT_FAILURE);
	// RENDER HERE
	int image[g_resolution.y][g_resolution.x];
	int x = 0;
	int y = 0;
	int aspect_ratio = g_resolution.x / g_resolution.y;
	int value;
	int fov = 70;
	t_ray ray;
	t_vector light = {1.6,4,-1};
	int light_color = rgb_to_int("255,255,255");
	while (y < g_resolution.y)
	{
		x = 0;
		while (x < g_resolution.x)
		{
			//colors for different types of lighting
			float color,a_color,d_color,s_color = 0;
			//convert raster space to Normalized Device Coordinates (NDC)
			 float NDC_x = (x + 0.5) / g_resolution.x; //adding 0.5 to align with middle of the pixel ...
			 float NDC_y = (y + 0.5) / g_resolution.y;

			// //convert NDC to screen space // values from -1 to 1
			 float screen_x =   2 * NDC_x - 1;
			 float screen_y = -(2 * NDC_y - 1); // to make y values above x axis (screen space) positive .....

			// //convert screen space to camera space, 
			float Px = screen_x * tan(fov / 2 * M_PI / 180) * aspect_ratio;
			float Py = screen_y * tan(fov / 2 * M_PI / 180);

			//cast ray
			ray.pos.x = 0;
			ray.pos.y = 0;
			ray.pos.z = 0;
			ray.dir.x = Px;
			ray.dir.y = Py;
			ray.dir.z = -1; // ZOOM 
			ray.dir = vec_normalize(ray.dir);

			t_intersection* closest = get_closest_intersection(objects, ray);
			if (closest)
				color = compute_pixel_color(closest,ray,light,light_color);
			else
				color = 0;
			mlx_pixel_put(data.mlx_ptr,data.mlx_win, x, y, (int)floor(color));
			x++;
		}
		//printf("\n");
		y++;
	}
	ft_lstclear(&objects,free_object);
	ft_printf("[ GOOD ]");
	mlx_loop(data.mlx_ptr);

    return (EXIT_SUCCESS);
}
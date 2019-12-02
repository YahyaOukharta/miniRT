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
t_list *lights;
t_list *cameras;
t_list *current_camera;

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

int is_ray_blocked(t_ray shadow_ray)
{
	t_list *objs = objects;
	while (objs)
	{
		t_object *sph = (t_object *)(objs->content);
	
		if((!ft_memcmp(sph->type,"sp",max(ft_strlen(sph->type),2)) && intersects_with_sphere(shadow_ray, sph))
			|| (!ft_memcmp(sph->type,"pl",max(ft_strlen(sph->type),2)) && intersects_with_sphere(shadow_ray, sph))
			|| (!ft_memcmp(sph->type,"tr",max(ft_strlen(sph->type),2)) && intersects_with_triangle(shadow_ray, sph)))
		{
			return(1);
		}
		objs = objs->next;
	}return (0);
}

int compute_pixel_color(t_intersection *closest,t_ray ray, t_list *lights)
{
	int blocked = 0;
	float color,a_color,d_color,s_color = 0;
	t_ray shadow_ray;

	//ambient lighting
	a_color = get_ambient_color(closest);
	color = a_color;
	//cast shadow ray towards lights
	while (lights)
	{
		t_light* light = ((t_light *)((t_object *)(lights->content))->details);
		shadow_ray.pos = vec_add(vec_add(ray.pos,vec_mult(ray.dir, closest->t)),vec_mult(closest->normal, 0.00000001));
		shadow_ray.dir = vec_normalize(vec_sub(light->pos, shadow_ray.pos));
		if(!is_ray_blocked(shadow_ray))
		{
			//diffuse lighting
			d_color = add_colors(d_color, get_diffuse_color(closest, shadow_ray, light));
			//specular lighting
			s_color = add_colors(s_color, get_specular_color(closest, ray, shadow_ray, light));
		}
		lights = lights->next;
	}
	color = add_colors(d_color,s_color);
	color = add_colors(color , a_color);
	return (color);
}	
int render(data_t data,t_list *objects, t_list *lights, t_list* current_camera)
{
	int aspect_ratio = g_resolution.x / g_resolution.y;
	t_ray ray;
	t_camera *current_cam = (t_camera *)((t_object *)current_camera->content)->details;	
	int fov = current_cam->fov;

	int x = 0;
	int y = 0;
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

			t_vector camera_pos = current_cam->pos;
			t_vector cam_dir = current_cam->dir;
			//cast ray
			// ray.pos.x = 0;
			// ray.pos.y = 0;
			// ray.pos.z = 0;
			ray.pos = camera_pos;
			ray.dir.x = Px;
			ray.dir.y = Py;
			ray.dir.z = -1; // ZOOM
			ray.dir = vec_normalize(ray.dir);

			//ray.dir = vec_rotate(ray.dir,vec_normalize(cam_dir));

			t_intersection* closest = get_closest_intersection(objects, ray);
			if (closest)
				color = compute_pixel_color(closest,ray,lights);
			else
				color = 0;

		// int index = (x * bpp / 8) + (y * size_line);
		// img_data[index] = color;
		// img_data[++index] = (int)color >> 8;
		// img_data[++index] = (int)color >> 16;
			mlx_pixel_put(data.mlx_ptr,data.mlx_win, x, y, (int)floor(color));
			x++;
		}
		y++;
	}
	return (1);
}
	data_t        data;

int	move_sph(int key,void *param)
{
	t_light *sph;
	sph = (t_light *)param;
	if (key == 125)
		sph->pos.y -= 0.1;
	else if (key == 126)
		sph->pos.y += 0.1;
	else if (key == 123)
		sph->pos.x -= 0.1;
	else if (key == 124)
		sph->pos.x += 0.1;

	mlx_clear_window(data.mlx_ptr, data.mlx_win);
	render(data,objects,lights,current_camera);
	return (0);
}

int main (int argc, char **argv)
{
	//mlx 
	//file processing and scene objects storing
	if (argc != 2)
		return (ft_printf("Error\n [!] Wrong numbers of arguments, Enter only one argument\n") ? 0 : 0);
	if(!process_file(argv))
		return (0);
	print_objects(objects);
	print_objects(lights); 
	print_objects(cameras);

    if (!(data.mlx_ptr = mlx_init()))
        return (EXIT_FAILURE);
    if (!(data.mlx_win = mlx_new_window(data.mlx_ptr, g_resolution.x, g_resolution.y, "Hello world !!!")))
        return (EXIT_FAILURE);
	// RENDER HERE
	
	
	
	current_camera = cameras;
	if(!render(data,objects,lights,current_camera))
		return (0);

	t_light *li = (t_light *)((t_object *)lights->content)->details;
	mlx_key_hook(data.mlx_win, move_sph,li);
	mlx_loop(data.mlx_ptr);

	ft_lstclear(&objects,free_object);
	ft_printf("[ GOOD ]");
    return (EXIT_SUCCESS);
}
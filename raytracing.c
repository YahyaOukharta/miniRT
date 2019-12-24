/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youkhart <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/19 21:40:38 by youkhart          #+#    #+#             */
/*   Updated: 2019/12/19 21:42:22 by youkhart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <time.h>

extern struct s_minirt	g_rt;
extern int				g_saving;
int						g_tmp_y;

t_intersection	*test_intersection(t_obj *obj, t_ray ray)
{
	if (!ft_memcmp(obj->type, "sp", 2))
		return (intersects_with_sphere(ray, obj));
	else if (!ft_strncmp(obj->type, "pl", 2))
		return (intersects_with_plane(ray, obj));
	else if (!ft_strncmp(obj->type, "tr", 2))
		return (intersects_with_triangle(ray, obj));
	else if (!ft_strncmp(obj->type, "cy", 2))
		return (intersects_with_cylinder(ray, obj));
	else if (!ft_strncmp(obj->type, "sq", 2))
		return (intersects_with_square(ray, obj));
	else
		return (0);
}

int				intersects_with_any(t_obj *obj, t_ray ray, float *t)
{
	if (!ft_memcmp(obj->type, "sp", 2))
		return (bool_intersects_with_sphere(ray, obj, t));
	else if (!ft_strncmp(obj->type, "pl", 2))
		return (bool_intersects_with_plane(ray, obj, t));
	else if (!ft_strncmp(obj->type, "tr", 2))
		return (bool_intersects_with_triangle(ray, obj, t));
	else if (!ft_strncmp(obj->type, "cy", 2))
		return (bool_intersects_with_cylinder(ray, obj, t));
	// else if (!ft_strncmp(obj->type, "sq", 2))
	// 	return (bool_intersects_with_square(ray, obj, t));
	else
		return (0);
}

t_intersection	*get_closest_intersection(t_list *objects, t_ray ray)
{
	t_list			*objs;
	t_intersection	*closest;
	t_intersection	*inter;
	float			min_t;

	objs = objects;
	closest = NULL;
	inter = NULL;
	min_t = INFINITY;
	while (objs)
	{
		inter = test_intersection((t_obj *)objs->content, ray);
		if (inter && inter->t < min_t && inter->t > RAY_T_MIN)
		{
			min_t = inter->t;
			closest = inter;
		}
		objs = objs->next;
	}
	return (closest);
}

int		is_ray_blocked(t_ray shadow_ray, t_vector light_pos, t_list *objs)
{
	float	t;
	float	light_dist;

	light_dist = vec_len(vec_sub(shadow_ray.pos, light_pos));
	while (objs)
	{
		if (intersects_with_any((t_obj *)objs->content, shadow_ray, &t)
			&& t < light_dist)
			return (1);
		objs = objs->next;
	}
	return (0);
}

int		compute_pixel_color(t_intersection *closest, t_ray ray, t_list *lights)
{
	float		*color;
	t_ray		shadow_ray;
	t_light		*light;

	color = ft_calloc(4, sizeof(float));
	color[1] = get_ambient_color(closest);
	color[0] = color[1];
	while (lights)
	{
		light = ((t_light *)((t_obj *)(lights->content))->details);
		shadow_ray.pos = vec_add(vec_add(ray.pos, vec_mult(ray.dir, closest->t))
			, vec_mult(closest->normal, RAY_T_MIN));
		shadow_ray.dir = vec_normalize(vec_sub(light->pos, shadow_ray.pos));
		if (!is_ray_blocked(shadow_ray, light->pos, g_rt.objects))
		{
			color[2] = add_colors(color[2],
				get_diffuse_color(closest, shadow_ray, light));
			color[3] = add_colors(color[3],
				get_specular_color(closest, ray, shadow_ray, light));
		}
		lights = lights->next;
	}
	color[0] = add_colors(color[2], color[1]);
	color[0] = add_colors(color[0], color[3]);
	return (color[0]);
}

t_ray	cast_ray(int x, int y, t_cam *cam, float zoom)
{
	t_ray	ray;
	float	ndc[2];
	float	screen[2];
	float	world[2];

	ndc[0] = (x + 0.5) / g_rt.g_res.x;
	ndc[1] = (y + 0.5) / g_rt.g_res.y;
	screen[0] = 2 * ndc[0] - 1;
	screen[1] = -(2 * ndc[1] - 1);
	world[0] = screen[0] * tan(cam->fov / 2 * M_PI / 180)
					* g_rt.g_res.x / g_rt.g_res.y;
	world[1] = screen[1] * tan(cam->fov / 2 * M_PI / 180);
	ray.pos = cam->pos;
	ray.dir.x = world[0];
	ray.dir.y = world[1];
	ray.dir.z = zoom;
	ray.dir = vec_rotate(vec_normalize(ray.dir), cam->rot);
	return (ray);
}

int	put_menu(int menu)
{
	if (!menu)
	{
		if (!g_saving)
			mlx_put_image_to_window(g_rt.data.mlx_ptr, g_rt.data.mlx_win,
				g_rt.data.img_ptr, 0, 0);
		menu_toggle_msg();
		show_menu();
		selected_objects_msg();
	}
	g_saving = 0;
	return (1);
}

int		render(int x, int y, int w, int h)
{
	t_ray			ray;
	float			color;
	int				menu;
	t_intersection	*i;

	menu = 0;
	y = -1;
	if (!x && !y && w == g_rt.g_res.x && h == g_rt.g_res.y)
		menu = 1;
	while (++y < h)
	{
		x = -1;
		while (++x < w)
		{
			color = 0;
			ray = cast_ray(x, y, (t_cam *)((t_obj *)g_rt.curr_cam->content)
				->details, -1);
			i = get_closest_intersection(g_rt.objects, ray);
			color = (i ? compute_pixel_color(i, ray, g_rt.lights) : 0);
			g_tmp_y = (g_saving ? h - y - 1 : y);
			(g_rt.data.img_data)[g_tmp_y * w + x] = (int)mult_colors(color,
			(g_rt.g_menu.on && x < g_rt.g_menu.w ? g_rt.g_menu.opacity : 1));
		}
	}
	return (put_menu(menu));
}

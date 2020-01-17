/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lighting.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youkhart <youkhart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/25 22:10:46 by youkhart          #+#    #+#             */
/*   Updated: 2020/01/17 19:48:12 by youkhart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

extern struct s_minirt	g_rt;

int						get_ambient_color(t_intersection *i)
{
	return (add_colors(
		mult_colors(g_rt.g_ambient_light.color,
			g_rt.g_ambient_light.brightness),
		mult_colors(i->object_color,
			g_rt.g_ambient_light.brightness)));
}

int						get_diffuse_color(t_intersection *i,
							t_ray shadow_ray, t_light *light)
{
	t_vector	light_dir;
	float		dot;

	light_dir = vec_normalize(vec_sub(light->pos, shadow_ray.pos));
	dot = fmax(vec_dot(i->normal, light_dir), 0);
	return (mult_colors(light->color, dot * i->diffuse * light->brightness));
}

int						get_specular_color(t_intersection *i,
							t_ray ray, t_ray shadow_ray, t_light *light)
{
	t_vector	light_dir;
	t_vector	reflection_dir;
	t_vector	view_dir;
	float		dot;

	light_dir = vec_normalize(vec_sub(light->pos, shadow_ray.pos));
	reflection_dir = vec_sub(ray.dir,
		vec_mult(i->normal, 2 * vec_dot(ray.dir, i->normal)));
	view_dir = vec_mult(ray.dir, -1);
	dot = fmax(vec_dot(reflection_dir, light_dir), 0);
	return (mult_colors(light->color,
		i->specular * pow(dot, i->s_power) * light->brightness));
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracing_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youkhart <youkhart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/25 22:06:48 by youkhart          #+#    #+#             */
/*   Updated: 2019/12/25 22:46:50 by youkhart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

extern struct s_minirt	g_rt;
extern int				g_saving;

int				put_menu(int menu)
{
	if (!g_saving)
		mlx_put_image_to_window(g_rt.data.mlx_ptr, g_rt.data.mlx_win,
			g_rt.data.img_ptr, 0, 0);
	if (!g_saving && !menu)
	{
		menu_toggle_msg();
		show_menu();
		selected_objects_msg();
	}
	g_saving = 0;
	return (1);
}

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

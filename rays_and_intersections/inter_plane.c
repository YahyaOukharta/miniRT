/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inter_plane.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youkhart <youkhart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/26 07:37:43 by youkhart          #+#    #+#             */
/*   Updated: 2020/01/25 22:19:58 by youkhart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray.h"

int				bool_intersects_with_plane(t_ray ray, t_obj *obj, float *t)
{
	t_plane		*plane;
	float		d;
	float		denom;
	t_vector	p_origin_dir;
	t_vector	p_normal;

	plane = (t_plane *)obj->details;
	p_normal = vec_normalize(plane->orientation);
	denom = vec_dot(p_normal, ray.dir);
	if (denom < 1e-6)
		return (0);
	p_origin_dir = vec_sub(plane->pos, ray.pos);
	d = vec_dot(p_origin_dir, p_normal) / denom;
	if (d < RAY_T_MIN)
		return (0);
	if (t)
		*t = d;
	return (1);
}

t_intersection	*intersects_with_plane(t_ray ray, t_obj *obj)
{
	t_intersection	*inter;
	t_plane			*plane;
	float			t;

	if (!bool_intersects_with_plane(ray, obj, &t))
		return (0);
	inter = (t_intersection *)malloc(sizeof(t_intersection));
	plane = (t_plane *)obj->details;
	inter->obj = obj;
	inter->point = vec_add(ray.pos, vec_mult(ray.dir, t));
	inter->t = t;
	inter->object_color = plane->color;
	inter->normal = vec_mult(vec_normalize(plane->orientation), 1);
	inter->diffuse = 0.4;
	inter->specular = 0.1;
	inter->s_power = 2;
	return (inter);
}

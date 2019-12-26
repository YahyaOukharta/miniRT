/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inter_triangle.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youkhart <youkhart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/26 07:38:18 by youkhart          #+#    #+#             */
/*   Updated: 2019/12/26 07:38:19 by youkhart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray.h"

int				bool_intersects_with_triangle(t_ray ray, t_obj *obj, float *t)
{
	float		d;
	t_triangle	*tri;
	t_vector	edge[2];
	t_vector	helper[2];
	float		vars[3];

	tri = (t_triangle *)obj->details;
	edge[0] = vec_sub(tri->p2, tri->p1);
	edge[1] = vec_sub(tri->p3, tri->p1);
	helper[0] = vec_cross(ray.dir, edge[1]);
	if (fabs((vars[0] = vec_dot(edge[0], helper[0]))) < RAY_T_MIN)
		return (0);
	vars[1] = (1.0 / vars[0]) * vec_dot(vec_sub(ray.pos, tri->p1), helper[0]);
	if (vars[1] < 0.0 || vars[1] > 1.0)
		return (0);
	helper[1] = vec_cross(vec_sub(ray.pos, tri->p1), edge[0]);
	vars[2] = (1.0 / vars[0]) * vec_dot(ray.dir, helper[1]);
	if (vars[2] < 0.0 || vars[1] + vars[2] > 1.0)
		return (0);
	if ((d = (1.0 / vars[0]) * vec_dot(edge[1], helper[1])) < RAY_T_MIN
		&& d > 1 / RAY_T_MIN)
		return (0);
	if (t)
		*t = d;
	return (1);
}

t_intersection	*intersects_with_triangle(t_ray ray, t_obj *obj)
{
	float			t;
	t_triangle		*tri;
	t_intersection	*inter;

	if (!bool_intersects_with_triangle(ray, obj, &t))
		return (0);
	inter = (t_intersection *)malloc(sizeof(t_intersection));
	tri = (t_triangle *)obj->details;
	inter->obj = obj;
	inter->point = vec_add(ray.pos, vec_mult(ray.dir, t));
	inter->normal = vec_cross(vec_sub(tri->p2, tri->p1),
						vec_sub(tri->p3, tri->p1));
	inter->t = t;
	inter->object_color = tri->color;
	inter->diffuse = 0.4;
	inter->specular = 0.2;
	inter->s_power = 4;
	return (inter);
}

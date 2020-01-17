/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inter_cylinder.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youkhart <youkhart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/26 07:39:53 by youkhart          #+#    #+#             */
/*   Updated: 2020/01/17 20:12:10 by youkhart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray.h"

t_vector		cylinder_normal_at(t_vector point, t_cylinder *cy)
{
	t_vector vec;

	vec = vec_sub(point, cy->pos);
	return ((fabs(vec.y) < cy->height)
		? (vec_normalize(vec_create(vec.x, 0, vec.z)))
		: vec_normalize(vec));
}

int				solve_quadratic_cy(float coeffs[3], float *t1, float *t2)
{
	float	discr;

	discr = coeffs[1] * coeffs[1] - coeffs[0] * coeffs[2];
	if (discr < 0)
		return (0);
	else
	{
		*t2 = (-coeffs[1] - sqrt(discr)) / coeffs[0];
		*t1 = (-coeffs[1] + sqrt(discr)) / coeffs[0];
	}
	return (1);
}

int				bool_intersects_with_cylinder(t_ray ray,
	t_obj *obj, float *dist)
{
	float		t[3];
	t_cylinder	*cy;
	t_vector	p0;
	float		coeffs[3];

	cy = (t_cylinder *)obj->details;
	p0 = vec_sub(ray.pos, cy->pos);
	coeffs[0] = ray.dir.x * ray.dir.x + ray.dir.z * ray.dir.z;
	coeffs[1] = ray.dir.x * p0.x + ray.dir.z * p0.z;
	coeffs[2] = p0.x * p0.x + p0.z * p0.z - pow(cy->diameter / 2, 2);
	if (!solve_quadratic_cy(coeffs, &t[1], &t[2]))
		return (0);
	if (t[1] > RAY_T_MIN && t[1] < RAY_T_MAX)
		t[0] = t[1];
	if (t[2] < t[1] && t[2] > RAY_T_MIN && t[2] < RAY_T_MAX)
		t[0] = t[2];
	else
		return (0);
	p0 = vec_add(ray.pos, vec_mult(ray.dir, t[0]));
	if (p0.y - cy->pos.y > cy->height || p0.y - cy->pos.y < 0)
		return (0);
	if (dist)
		*dist = t[0];
	return (1);
}

t_intersection	*intersects_with_cylinder(t_ray ray, t_obj *obj)
{
	float			t;
	t_cylinder		*cy;
	t_intersection	*inter;

	if (!bool_intersects_with_cylinder(ray, obj, &t))
		return (0);
	inter = (t_intersection *)malloc(sizeof(t_intersection));
	cy = (t_cylinder *)obj->details;
	inter->point = vec_add(ray.pos, vec_mult(ray.dir, t));
	inter->t = t;
	inter->diffuse = 0.4;
	inter->specular = 0.2;
	inter->s_power = 16;
	inter->obj = obj;
	inter->object_color = cy->color;
	inter->normal = cylinder_normal_at(inter->point, cy);
	return (inter);
}

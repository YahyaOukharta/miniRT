/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inter_cylinder.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youkhart <youkhart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/26 07:39:53 by youkhart          #+#    #+#             */
/*   Updated: 2020/01/27 21:36:58 by youkhart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray.h"

static int		rotate_cy(t_ray *ray, t_vector *vec, t_cylinder *cy, int dir)
{
	t_vector	tmp;
	t_vector	rot;

	tmp = vec_normalize(cy->orientation);
	tmp.x = 0;
	rot.x = -acos(vec_dot(vec_create(0, 1, 0), vec_normalize(tmp)));
	tmp = vec_normalize(cy->orientation);
	tmp.z = 0;
	rot.z = acos(vec_dot(vec_create(0, 1, 0), vec_normalize(tmp)));
	rot.y = 0;
	if (vec)
		*vec = vec_rotate(*vec, vec_mult(rot, dir));
	if (ray)
	{
		ray->pos = vec_rotate(ray->pos, vec_mult(rot, dir));
		ray->dir = vec_rotate(ray->dir, vec_mult(rot, dir));
	}
	return (0);
}

static t_vector	cylinder_normal_at(t_vector point, t_cylinder *cy)
{
	t_vector vec;

	rotate_cy(NULL, &point, cy, -1);
	vec = vec_sub(point, cy->pos);
	vec = vec_normalize(vec_create(vec.x, 0, vec.z));
	return (vec);
}

static int		solve_quadratic_cy(float coeffs[3], float *t0,
	float *t1, float *t2)
{
	float	discr;
	float	q;

	discr = coeffs[1] * coeffs[1] - 4 * coeffs[0] * coeffs[2];
	if (discr < 0)
		return (0);
	else if (!discr)
	{
		*t1 = -0.5 * (float)(coeffs[1] / coeffs[0]);
		*t2 = *t1;
	}
	else
	{
		q = (coeffs[1] > 0) ?
			(-0.5 * (coeffs[1] + sqrt(discr)))
			: (-0.5 * (coeffs[1] - sqrt(discr)));
		*t1 = q / coeffs[0];
		*t2 = coeffs[2] / q;
	}
	*t0 = 0;
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
	rotate_cy(&ray, NULL, cy, -1);
	p0 = vec_sub(ray.pos, cy->pos);
	coeffs[0] = ray.dir.x * ray.dir.x + ray.dir.z * ray.dir.z;
	coeffs[1] = 2 * (ray.dir.x * p0.x + ray.dir.z * p0.z);
	coeffs[2] = p0.x * p0.x + p0.z * p0.z - pow(cy->diameter / 2, 2);
	if (!solve_quadratic_cy(coeffs, &t[0], &t[1], &t[2]))
		return (0);
	if (t[1] > RAY_T_MIN)
		t[0] = t[1];
	if (t[2] < t[1] && t[2] > RAY_T_MIN)
		t[0] = t[2];
	if (!t[0])
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

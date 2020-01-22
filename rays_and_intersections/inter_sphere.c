/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inter_sphere.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youkhart <youkhart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/26 07:37:03 by youkhart          #+#    #+#             */
/*   Updated: 2020/01/22 01:01:37 by youkhart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray.h"

int				solve_quadratic_sp(float coeffs[3], float *t1, float *t2)
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
	return (1);
}

int				bool_intersects_with_sphere(t_ray ray, t_obj *obj, float *dist)
{
	t_sphere	*sphere;
	t_ray		tmp_ray;
	float		t[3];
	float		coeffs[3];

	sphere = (t_sphere *)obj->details;
	tmp_ray = ray;
	tmp_ray.pos = vec_sub(ray.pos, sphere->pos);
	coeffs[0] = vec_len2(tmp_ray.dir);
	coeffs[1] = 2 * vec_dot(tmp_ray.dir, tmp_ray.pos);
	coeffs[2] = vec_len2(tmp_ray.pos) - sphere->diameter * sphere->diameter;
	if (!(solve_quadratic_sp(coeffs, &t[1], &t[2])))
		return (0);
	t[0] = 0;
	if (t[1] > RAY_T_MIN)
		t[0] = t[1];
	if (t[2] < t[1] && t[2] > RAY_T_MIN)
		t[0] = t[2];
	if (!t[0])
		return (0);
	if (dist)
		*dist = t[0];
	return (1);
}

t_intersection	*intersects_with_sphere(t_ray ray, t_obj *obj)
{
	t_intersection	*inter;
	t_sphere		*sphere;
	float			t;

	if (!bool_intersects_with_sphere(ray, obj, &t))
		return (0);
	inter = (t_intersection *)malloc(sizeof(t_intersection));
	inter->obj = obj;
	sphere = (t_sphere *)obj->details;
	inter->point = vec_add(ray.pos, vec_mult(ray.dir, t));
	inter->t = t;
	inter->object_color = sphere->color;
	inter->normal = vec_normalize(
		vec_sub(vec_add(ray.pos, vec_mult(ray.dir, t)), sphere->pos));
	inter->diffuse = 0.4;
	inter->specular = 0.4;
	inter->s_power = 20;
	return (inter);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inter_square.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youkhart <youkhart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/26 07:40:04 by youkhart          #+#    #+#             */
/*   Updated: 2020/01/17 20:04:27 by youkhart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray.h"

extern struct s_minirt g_rt;

t_vector		*get_square_vertices(float side_size, t_vector orientation)
{
	t_vector *out;

	out = (t_vector *)malloc(sizeof(t_vector) * 4);
	out[0] = vec_rotate(vec_create(-side_size / 2, side_size / 2, 0),
		orientation);
	out[1] = vec_rotate(vec_create(side_size / 2, side_size / 2, 0),
		orientation);
	out[2] = vec_rotate(vec_create(side_size / 2, -side_size / 2, 0),
		orientation);
	out[3] = vec_rotate(vec_create(-side_size / 2, -side_size / 2, 0),
		orientation);
	return (out);
}

float			orient(t_vector a, t_vector b, t_vector c, t_vector n)
{
	return (vec_dot(vec_cross(vec_sub(b, a), vec_sub(c, a)), n));
}

int				is_point_inside_square(t_vector p, t_vector *vxs, t_vector n)
{
	int		sign;
	float	o[4];

	o[0] = orient(p, vxs[0], vxs[1], n);
	sign = o[0] / fabs(o[0]);
	o[1] = orient(p, vxs[1], vxs[2], n);
	if (o[1] / fabs(o[1]) != sign)
		return ((int)free_and_return(vxs, 0));
	o[2] = orient(p, vxs[2], vxs[3], n);
	if (o[2] / fabs(o[2]) != sign)
		return ((int)free_and_return(vxs, 0));
	o[3] = orient(p, vxs[3], vxs[0], n);
	if (o[3] / fabs(o[3]) != sign)
		return ((int)free_and_return(vxs, 0));
	free(vxs);
	return (1);
}

int				bool_intersects_with_square(t_ray ray, t_obj *obj, float *t)
{
	float			d;
	t_square		*sq;
	t_ray			tmp_ray;
	t_vector		sq_normal;
	float			denom;

	sq = (t_square *)obj->details;
	sq_normal = vec_rotate(vec_create(0, 0, -1), sq->orientation);
	tmp_ray = ray;
	tmp_ray.pos = vec_sub(ray.pos, sq->pos);
	denom = vec_dot(sq_normal, ray.dir);
	if (denom < 1e-6)
		return (0);
	d = vec_dot(vec_sub(sq->pos, ray.pos), sq_normal) / denom;
	if (d < RAY_T_MIN)
		return (0);
	if (!is_point_inside_square(vec_add(tmp_ray.pos, vec_mult(ray.dir, d)),
		get_square_vertices(sq->side_size, sq->orientation), sq_normal))
		return (0);
	else if (t)
		*t = d;
	return (1);
}

t_intersection	*intersects_with_square(t_ray ray, t_obj *obj)
{
	float			t;
	t_square		*sq;
	t_intersection	*inter;
	t_vector		sq_normal;

	sq = (t_square *)obj->details;
	sq_normal = vec_rotate(vec_create(0, 0, 1), sq->orientation);
	if (!bool_intersects_with_square(ray, obj, &t))
		return (0);
	inter = (t_intersection *)malloc(sizeof(t_intersection));
	inter->point = vec_add(ray.pos, vec_mult(ray.dir, t));
	inter->t = t;
	inter->diffuse = 0.4;
	inter->specular = 0.2;
	inter->s_power = 4;
	inter->obj = obj;
	inter->object_color = sq->color;
	inter->normal = sq_normal;
	return (inter);
}

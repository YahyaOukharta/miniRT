/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inter_square.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youkhart <youkhart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/26 07:40:04 by youkhart          #+#    #+#             */
/*   Updated: 2019/12/26 07:40:58 by youkhart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray.h"

t_intersection	*intersects_with_square(t_ray ray, t_obj *obj)
{
	float			t;
	t_square		*sq;
	t_intersection	*inter;
	t_vector		p_normal;
	float			denom;
	t_vector		p_origin,p;
	float l,r,u,d;

	inter = (t_intersection *)malloc(sizeof(t_intersection));
	sq = (t_square *)obj->details;
	p_normal = vec_normalize(sq->orientation);
	denom = vec_dot(p_normal, ray.dir);
	if (fabs(denom) < RAY_T_MIN)
		return (0);
	t_vector p_origin_dir = vec_sub(sq->pos, ray.pos);
	t = vec_dot(p_origin_dir, p_normal) / denom;
	if (t < RAY_T_MIN)
		return (0);
	p = vec_add(ray.pos, vec_mult(ray.dir, t));
	l = (sq->pos.x - sq->side_size / 2);
	r = (sq->pos.x + sq->side_size / 2);
	u = (sq->pos.y + sq->side_size / 2);
	d = (sq->pos.y - sq->side_size / 2);
	if (p.x < l || p.x > r || p.y < d || p.y > u)
		return (0);
	inter->point = vec_add(ray.pos, vec_mult(ray.dir, t));
	inter->t = t;
	inter->diffuse = 0.4;
	inter->specular = 0.2;
	inter->s_power = 4;
	inter->obj = obj;
	inter->object_color = sq->color;
	inter->normal = sq->orientation;
	return (inter);
}

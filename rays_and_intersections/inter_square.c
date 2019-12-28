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


void		place_points(t_square **new)
{
	t_vector	*vector[4];

	vector[0] = new_vector((*new)->size / 2, (*new)->size / 2, 0);
	vector[1] = new_vector(-(*new)->size / 2, (*new)->size / 2, 0);
	vector[2] = new_vector((*new)->size / 2, -(*new)->size / 2, 0);
	vector[3] = new_vector(-(*new)->size / 2, -(*new)->size / 2, 0);
	rot(vector[0], (*new)->orientation);
	rot(vector[1], (*new)->orientation);
	rot(vector[2], (*new)->orientation);
	rot(vector[3], (*new)->orientation);
	(*new)->a = add_vectors(*vector[0], *(*new)->center);
	(*new)->b = add_vectors(*vector[1], *(*new)->center);
	(*new)->c = add_vectors(*vector[2], *(*new)->center);
	(*new)->d = add_vectors(*vector[3], *(*new)->center);
}

// float		intersect_square2(float t, t_vector origin, t_vector direction,
// t_square *object)
// {
// 	t_vector	*point;
// 	t_vector	*temp;
// 	t_vector	*ap;
// 	float		alpha;
// 	float		beta;

// 	temp = multiply_vectors(t, direction);
// 	point = add_vectors(origin, *temp);
// 	free(temp);
// 	ap = subtract_vectors(*point, *object->a);
// 	alpha = product_vectors(*ap, *object->ab) /
// product_vectors(*object->ab, *object->ab);
// 	beta = product_vectors(*ap, *object->ac) /
// product_vectors(*object->ac, *object->ac);
// 	free(ap);
// 	free(point);
// 	if (alpha >= 0 && alpha <= 1 && beta >= 0 && beta <= 1)
// 		return (t);
// 	return (0);
// }

// float		intersect_square(t_vector origin, t_vector direction,
// t_square *object)
// {
// 	float denom;
// 	float alpha;
// 	float beta;

// 	beta = 0;
// 	if (!object->prev_origin || !is_equal(object->prev_origin, &origin))
// 	{
// 		if (object->prev_origin)
// 			free(object->prev_origin);
// 		denom = -(product_vectors(*object->normal, *object->center));
// 		object->calcul_a = product_vectors(origin, *object->normal) + denom;
// 		object->prev_origin = cpy_vector(&origin);
// 	}
// 	alpha = product_vectors(direction, *object->normal);
// 	beta = -(object->calcul_a / alpha);
// 	if (beta <= 0)
// 		return (0);
// 	return (intersect_square2(beta, origin, direction, object));
// }

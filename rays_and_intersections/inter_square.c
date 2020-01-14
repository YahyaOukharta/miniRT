/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inter_square.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youkhart <youkhart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/26 07:40:04 by youkhart          #+#    #+#             */
/*   Updated: 2020/01/14 18:20:34 by youkhart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray.h"

int				bool_intersects_with_square(t_ray ray, t_obj *obj, float *t)
{
	return (0);
}
t_vector		*get_square_vertices(float side_size, t_vector orientation)
{
	t_vector *out;
	out = (t_vector *)malloc(sizeof(t_vector) * 4);

	out[0] = vec_rotate(vec_create(-side_size/2, side_size/2, 0), orientation);
	out[1] = vec_rotate(vec_create(side_size/2, side_size/2, 0), orientation);
	out[2] = vec_rotate(vec_create(side_size/2, -side_size/2, 0), orientation);
	out[3] = vec_rotate(vec_create(-side_size/2, -side_size/2, 0), orientation);
	return (out);
}

	// o1=orient(q,p1,p2,n)
	// o2=orient(q,p2,p3,n)
	// o3=orient(q,p3,p4,n)
	// o4=orient(q,p4,p1,n)
	// where
	// orient(a,b,c,n) =  [(b-a) x (c-a)] . n
	// x: cross product; . : dot product

float 			orient(t_vector a, t_vector b, t_vector c, t_vector n)
{
	return (vec_dot(vec_cross(vec_sub(b, a), vec_sub(c, a)), n));
}

int				is_point_inside_square(t_vector p,
	t_vector *vertices, t_vector n)
{
	int		sign;
	int		tmp_sign;
	float	o[4];

	o[0] = orient(p, vertices[0], vertices[1], n);
	sign = o[0] / fabs(o[0]);
	o[1] = orient(p, vertices[1], vertices[2], n);
	tmp_sign = o[1] / fabs(o[1]);
	if (tmp_sign != sign)
		return (0);
	o[2] = orient(p, vertices[2], vertices[3], n);
	tmp_sign = o[2] / fabs(o[2]);
	if (tmp_sign != sign)
		return (0);
	o[3] = orient(p, vertices[3], vertices[0], n);
	tmp_sign = o[3] / fabs(o[3]);
	if (tmp_sign != sign)
		return (0);
	return (1);
}

t_intersection	*intersects_with_square(t_ray ray, t_obj *obj)
{
	float			t;
	t_square		*sq;
	t_intersection	*inter;
	t_ray			tmp_ray;
	t_vector		sq_normal;
	t_vector		*sq_vs;

	sq = (t_square *)obj->details;
	sq_normal = vec_rotate(vec_create(0, 0, -1), sq->orientation);
	tmp_ray = ray;
	tmp_ray.pos = vec_sub(ray.pos, sq->pos);
	//check if intersects with plane
	float denom = vec_dot(sq_normal, ray.dir);
	if (fabs(denom) < 1e-6)
		return (0);
	t_vector p_origin_dir = vec_sub(sq->pos, ray.pos);
	t = vec_dot(p_origin_dir, sq_normal) / denom;
	if (t < RAY_T_MIN)
		return (0);
	//test if intersection is inside the square
	sq_vs = get_square_vertices(sq->side_size, sq->orientation);
	if (!is_point_inside_square(vec_add(tmp_ray.pos, vec_mult(ray.dir, t)), sq_vs, sq_normal))
	{
		free(sq_vs);
		return (0);
	}
	free(sq_vs);
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


// void		place_points(t_square **new)
// {
// 	t_vector	*vector[4];

// 	vector[0] = new_vector((*new)->size / 2, (*new)->size / 2, 0);
// 	vector[1] = new_vector(-(*new)->size / 2, (*new)->size / 2, 0);
// 	vector[2] = new_vector((*new)->size / 2, -(*new)->size / 2, 0);
// 	vector[3] = new_vector(-(*new)->size / 2, -(*new)->size / 2, 0);
// 	rot(vector[0], (*new)->orientation);
// 	rot(vector[1], (*new)->orientation);
// 	rot(vector[2], (*new)->orientation);
// 	rot(vector[3], (*new)->orientation);
// 	(*new)->a = add_vectors(*vector[0], *(*new)->center);
// 	(*new)->b = add_vectors(*vector[1], *(*new)->center);
// 	(*new)->c = add_vectors(*vector[2], *(*new)->center);
// 	(*new)->d = add_vectors(*vector[3], *(*new)->center);
// }

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

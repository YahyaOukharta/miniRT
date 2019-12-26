/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_math_one.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youkhart <youkhart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/26 07:32:28 by youkhart          #+#    #+#             */
/*   Updated: 2019/12/26 07:33:16 by youkhart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector_math.h"

t_vector	vec_create(float x, float y, float z)
{
	t_vector v;

	v.x = x;
	v.y = y;
	v.z = z;
	return (v);
}

t_vector	vec_add(t_vector v1, t_vector v2)
{
	t_vector res;

	res.x = v1.x + v2.x;
	res.y = v1.y + v2.y;
	res.z = v1.z + v2.z;
	return (res);
}

t_vector	vec_sub(t_vector v1, t_vector v2)
{
	t_vector res;

	res.x = v1.x - v2.x;
	res.y = v1.y - v2.y;
	res.z = v1.z - v2.z;
	return (res);
}

t_vector	vec_mult(t_vector v1, float value)
{
	t_vector res;

	res.x = v1.x * value;
	res.y = v1.y * value;
	res.z = v1.z * value;
	return (res);
}

t_vector	vec_div(t_vector v1, float value)
{
	t_vector res;

	res.x = v1.x / value;
	res.y = v1.y / value;
	res.z = v1.z / value;
	return (res);
}

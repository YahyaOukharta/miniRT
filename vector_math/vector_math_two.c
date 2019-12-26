/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_math_two.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youkhart <youkhart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/26 07:32:26 by youkhart          #+#    #+#             */
/*   Updated: 2019/12/26 07:33:23 by youkhart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector_math.h"

float		vec_dot(t_vector v1, t_vector v2)
{
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}

t_vector	vec_cross(t_vector v1, t_vector v2)
{
	t_vector res;

	res.x = v1.y * v2.z - v1.z * v2.y;
	res.y = v1.z * v2.x - v1.x * v2.z;
	res.z = v1.x * v2.y - v1.y * v2.x;
	return (res);
}

float		vec_len2(t_vector v)
{
	return (v.x * v.x + v.y * v.y + v.z * v.z);
}

float		vec_len(t_vector v)
{
	return (sqrt(vec_len2(v)));
}

t_vector	vec_normalize(t_vector v)
{
	float	len;

	len = vec_len(v);
	return (vec_div(v, len));
}

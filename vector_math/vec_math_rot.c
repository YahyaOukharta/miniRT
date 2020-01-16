/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_math_rot.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youkhart <youkhart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/26 07:30:49 by youkhart          #+#    #+#             */
/*   Updated: 2020/01/15 21:21:09 by youkhart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector_math.h"

void		rotate_x(float *y, float *z, float angle)
{
	float previous_y;

	previous_y = *y;
	*y = previous_y * cos(angle) + *z * sin(angle);
	*z = -previous_y * sin(angle) + *z * cos(angle);
}

void		rotate_y(float *x, float *z, float angle)
{
	float previous_x;

	previous_x = *x;
	*x = previous_x * cos(angle) + *z * sin(angle);
	*z = -previous_x * sin(angle) + *z * cos(angle);
}

void		rotate_z(float *x, float *y, float angle)
{
	float previous_x;
	float previous_y;

	previous_x = *x;
	previous_y = *y;
	*x = previous_x * cos(angle) - previous_y * sin(angle);
	*y = previous_x * sin(angle) + previous_y * cos(angle);
}

t_vector	vec_rotate(t_vector vec, t_vector rot)
{
	rotate_x(&vec.y, &vec.z, rot.x);
	rotate_y(&vec.x, &vec.z, rot.y);
	rotate_z(&vec.x, &vec.y, rot.z);
	return (vec);
}

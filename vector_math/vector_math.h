/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_math.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youkhart <youkhart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/26 07:32:53 by youkhart          #+#    #+#             */
/*   Updated: 2020/01/15 21:39:19 by youkhart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_MATH_H
# define VECTOR_MATH_H
# include "../objects/objects.h"
# include <math.h>

t_vector	vec_add(t_vector v1, t_vector v2);
t_vector	vec_sub(t_vector v1, t_vector v2);
t_vector	vec_mult(t_vector v1, float value);
t_vector	vec_div(t_vector v1, float value);
float		vec_dot(t_vector v1, t_vector v2);
t_vector	vec_cross(t_vector v1, t_vector v2);
float		vec_len2(t_vector v);
float		vec_len(t_vector v);
t_vector	vec_normalize(t_vector v);
t_vector	vec_rotate(t_vector vec, t_vector rot);
t_vector	vec_create(float x, float y, float z);
void		rotate_x(float *y, float *z, float alpha);
void		rotate_y(float *x, float *z, float beta);
void		rotate_z(float *x, float *y, float gamma);

#endif

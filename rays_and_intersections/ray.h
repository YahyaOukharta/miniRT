/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youkhart <youkhart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/26 07:41:17 by youkhart          #+#    #+#             */
/*   Updated: 2019/12/26 07:41:18 by youkhart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAY_H
# define RAY_H
# include "../minirt.h"
# define RAY_T_MIN 0.00000001
# define RAY_T_MAX 1000000

typedef struct	s_ray
{
	t_vector	pos;
	t_vector	dir;
}				t_ray;

typedef struct	s_intersection
{
	t_vector	point;
	t_vector	normal;
	t_obj		*obj;
	float		t;
	int			object_color;
	float		diffuse;
	float		specular;
	float		s_power;
}				t_intersection;

int				bool_intersects_with_sphere(t_ray ray, t_obj *obj, float *t);
t_intersection	*intersects_with_sphere(t_ray ray, t_obj *obj);
int				bool_intersects_with_plane(t_ray ray, t_obj *obj, float *t);
t_intersection	*intersects_with_plane(t_ray ray, t_obj *obj);
int				bool_intersects_with_triangle(t_ray ray, t_obj *obj, float *t);
t_intersection	*intersects_with_triangle(t_ray ray, t_obj *obj);
int				bool_intersects_with_square(t_ray ray, t_obj *obj, float *t);
t_intersection	*intersects_with_square(t_ray ray, t_obj *obj);
int				bool_intersects_with_cylinder(t_ray ray, t_obj *obj, float *t);
t_intersection	*intersects_with_cylinder (t_ray ray, t_obj *obj);

#endif

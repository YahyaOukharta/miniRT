#ifndef VECTOR_MATH_H
# define VECTOR_MATH_H
# include "../objects/objects.h"

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
t_vector	vec_create(float x,float y,float z);
void		rotate_x(float *y, float *z, double alpha);
void		rotate_y(float *x, float *z, double beta);
void		rotate_z(float *x, float *y, double gamma);

#endif
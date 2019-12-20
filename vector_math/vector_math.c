#include "vector_math.h"
#include "../minirt.h"

t_vector vec_add(t_vector v1, t_vector v2)
{
	t_vector res;

	res.x = v1.x + v2.x;
	res.y = v1.y + v2.y;
	res.z = v1.z + v2.z;
	
	return res;
}
t_vector vec_sub(t_vector v1, t_vector v2)
{
	t_vector res;

	res.x = v1.x - v2.x;
	res.y = v1.y - v2.y;
	res.z = v1.z - v2.z;
	
	return res;
}
t_vector vec_mult(t_vector v1, float value)
{
	t_vector res;

	res.x = v1.x * value;
	res.y = v1.y * value;
	res.z = v1.z * value;
	
	return res;
}
t_vector vec_div(t_vector v1, float value)
{
	t_vector res;

	res.x = v1.x / value;
	res.y = v1.y / value;
	res.z = v1.z / value;
	
	return res;
}

float vec_dot(t_vector v1, t_vector v2)
{
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}

t_vector vec_cross(t_vector v1, t_vector v2)
{
	t_vector res;

	res.x = v1.y * v2.z - v1.z * v2.y;
	res.y = v1.z * v2.x - v1.x * v2.z;
	res.z = v1.x * v2.y - v1.y * v2.x;
	
	return res;
}

float vec_len2(t_vector v)
{
	return (v.x * v.x + v.y * v.y + v.z * v.z);
}
float vec_len(t_vector v)
{
	return (sqrt(vec_len2(v)));
}
t_vector vec_normalize(t_vector v)
{
	float len;

	len = vec_len(v);
	return (vec_div(v, len));
}

t_vector vec_create(float x,float y, float z)
{
	t_vector v;
	v.x = x;
	v.y = y;
	v.z = z;
	return v;
}

void	rotate_x(float *y, float *z, double alpha)
{
	float previous_y;

	previous_y = *y;
	*y = previous_y * cos(alpha) + *z * sin(alpha);
	*z = -previous_y * sin(alpha) + *z * cos(alpha);
}

void	rotate_y(float *x, float *z, double beta)
{
	float previous_x;

	previous_x = *x;
	*x = previous_x * cos(beta) + *z * sin(beta);
	*z = -previous_x * sin(beta) + *z * cos(beta);
}

void	rotate_z(float *x, float *y, double gamma)
{
	float previous_x;
	float previous_y;

	previous_x = *x;
	previous_y = *y;
	*x = previous_x * cos(gamma) - previous_y * sin(gamma);
	*y = previous_x * sin(gamma) + previous_y * cos(gamma);
}

t_vector vec_rotate(t_vector vec, t_vector rot)
{
	rotate_x(&vec.y,&vec.z,rot.x);
	rotate_y(&vec.x,&vec.z,rot.y);
	rotate_z(&vec.x,&vec.y,rot.z);
	return (vec);
}
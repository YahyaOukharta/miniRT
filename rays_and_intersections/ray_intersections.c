#include "ray.h"

int	solve_quadratic_sp(float coeffs[3], float *t1, float *t2)
{
	float	discr;
	float	q;

	discr = coeffs[1] * coeffs[1] - 4 * coeffs[0] * coeffs[2];
	if (discr < 0)
		return (0);
	else if (discr == 0)
		*t1 = -0.5 * (float)(coeffs[1] / coeffs[0]);
	else
	{
		q = (coeffs[1] > 0) ?
			(-0.5 * (coeffs[1] + sqrt(discr)))
			: (-0.5 * (coeffs[1] - sqrt(discr)));
		*t1 = q / coeffs[0];
		*t2 = coeffs[2] / q;
	}
	return (1);
}

int	bool_intersects_with_sphere(t_ray ray, t_obj *obj, float *dist)
{
	t_sphere	*sphere;
	t_ray		tmp_ray;
	float		t[3];
	float		coeffs[3];

	sphere = (t_sphere *)obj->details;
	tmp_ray = ray;
	tmp_ray.pos = vec_sub(ray.pos, sphere->pos);
	coeffs[0] = vec_len2(tmp_ray.dir);
	coeffs[1] = 2 * vec_dot(tmp_ray.dir, tmp_ray.pos);
	coeffs[2] = vec_len2(tmp_ray.pos) - sphere->diameter * sphere->diameter;
	if (!(solve_quadratic_sp(coeffs, &t[1], &t[2])))
		return (0);
	t[0] = 0;
	if (t[1] > RAY_T_MIN)
		t[0] = t[1];
	if (t[2] < t[1] && t[2] > RAY_T_MIN)
		t[0] = t[2];
	if (!t[0])
		return (0);
	if (dist)
		*dist = t[0];
	return (1);
}

t_intersection*	intersects_with_sphere(t_ray ray,	t_obj *obj)
{
	t_intersection	*inter;
	t_sphere		*sphere;
	t_ray			tmp_ray;
	float			t;

	if (!bool_intersects_with_sphere(ray, obj, &t))
		return (0);
	inter = (t_intersection *)malloc(sizeof(t_intersection));
	inter->obj = obj;
	sphere = (t_sphere *)obj->details;
	inter->point = vec_add(ray.pos, vec_mult(ray.dir, t));
	inter->t = t;
	inter->object_color = sphere->color;
	inter->normal = vec_mult(vec_normalize(
		vec_sub(vec_add(ray.pos, vec_mult(ray.dir, t)), sphere->pos)), 1);
	inter->diffuse = 0.4;
	inter->specular = 0.4;
	inter->s_power = 20;
	return inter;
}

int				bool_intersects_with_plane(t_ray ray, t_obj *obj, float *t)
{
	t_plane		*plane;
	float		d;
	float		denom;
	t_vector	p_origin_dir;
	t_vector	p_normal;

	plane = (t_plane *)obj->details;
	p_normal = vec_normalize(plane->orientation);
	denom = vec_dot(p_normal, ray.dir);
	if (fabs(denom) < 1e-6)
		return (0);
	p_origin_dir = vec_sub(plane->pos, ray.pos);
	d = vec_dot(p_origin_dir, p_normal) / denom;
	if (d < RAY_T_MIN)
		return (0);
	if (t)
		*t = d;
	return (1);
}

t_intersection	*intersects_with_plane(t_ray ray, t_obj *obj)
{
	t_intersection	*inter;
	t_plane			*plane;
	float			t;

	if (!bool_intersects_with_plane(ray, obj, &t))
		return (0);
	inter = (t_intersection *)malloc(sizeof(t_intersection));
	plane = (t_plane *)obj->details;
	inter->obj = obj;
	inter->point = vec_add(ray.pos, vec_mult(ray.dir, t));
	inter->t = t;
	inter->object_color = plane->color;
	inter->normal = vec_normalize(plane->orientation);
	inter->diffuse = 0.4;
	inter->specular = 0.4;
	inter->s_power = 2;
	return inter;
}

int				bool_intersects_with_triangle(t_ray ray, t_obj *obj, float *t)
{
	float		d;
	t_triangle	*tri;
	t_vector	edge[2];
	t_vector	helper[2];
	float		vars[3];

	tri = (t_triangle *)obj->details;
	edge[0] = vec_sub(tri->p2, tri->p1);
	edge[1] = vec_sub(tri->p3, tri->p1);
	helper[0] = vec_cross(ray.dir, edge[1]);
	if (fabs((vars[0] = vec_dot(edge[0], helper[0]))) < RAY_T_MIN)
		return (0);
	vars[1] = (1.0 / vars[0]) * vec_dot(vec_sub(ray.pos, tri->p1), helper[0]);
	if (vars[1] < 0.0 || vars[1] > 1.0)
		return (0);
	helper[1] = vec_cross(vec_sub(ray.pos, tri->p1), edge[0]);
	vars[2] = (1.0 / vars[0]) * vec_dot(ray.dir, helper[1]);
	if (vars[2] < 0.0 || vars[1] + vars[2] > 1.0)
		return (0);
	if ((d = (1.0 / vars[0]) * vec_dot(edge[1], helper[1])) < RAY_T_MIN
		&& d > 1 / RAY_T_MIN)
		return (0);
	if (t)
		*t = d;
	return (1);
}

t_intersection	*intersects_with_triangle(t_ray ray, t_obj *obj)
{
	float			t;
	t_triangle		*tri;
	t_intersection	*inter;

	if (!bool_intersects_with_triangle(ray, obj, &t))
		return (0);
	inter = (t_intersection *)malloc(sizeof(t_intersection));
	tri = (t_triangle *)obj->details;
	inter->obj = obj;
	inter->point = vec_add(ray.pos, vec_mult(ray.dir, t));
	inter->normal = vec_cross(vec_sub(tri->p2, tri->p1),
						vec_sub(tri->p3, tri->p1));
	inter->t = t;
	inter->object_color = tri->color;
	inter->diffuse = 0.4;
	inter->specular = 0.2;
	inter->s_power = 4;
	return inter;
}

t_intersection *intersects_with_square(t_ray ray, t_obj *obj)
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
	inter->point = vec_add(ray.pos, vec_mult(ray.dir, t));;
	inter->t = t;
	inter->diffuse = 0.4;
	inter->specular = 0.2;
	inter->s_power = 4;
	inter->obj = obj;
	inter->object_color = sq->color;
	inter->normal = sq->orientation;
	return inter;
}

t_vector	cylinder_normal_at(t_vector point, t_cylinder *cy)
{
	t_vector vec;

	vec = vec_sub(point, cy->pos);
	return ((fabs(vec.y) < cy->height)
		? (vec_normalize(vec_create(vec.x, 0, vec.z)))
		: vec_normalize(vec));
}

int	solve_quadratic_cy(float coeffs[3], float *t1, float *t2)
{
	float	discr;
	float	q;

	discr = coeffs[1] * coeffs[1] - coeffs[0] * coeffs[2];
	if (discr < 0)
		return (0);
	else
	{
		*t2 = (-coeffs[1] - sqrt(discr)) / coeffs[0];
		*t1 = (-coeffs[1] + sqrt(discr)) / coeffs[0];
	}
	return (1);
}

int				bool_intersects_with_cylinder(t_ray ray,
	t_obj *obj, float *dist)
{
	float		t[3];
	t_cylinder	*cy;
	t_vector	p0;
	float		coeffs[3];

	cy = (t_cylinder *)obj->details;
	p0 = vec_sub(ray.pos, cy->pos);
	coeffs[0] = ray.dir.x * ray.dir.x + ray.dir.z * ray.dir.z;
	coeffs[1] = ray.dir.x * p0.x + ray.dir.z * p0.z;
	coeffs[2] = p0.x * p0.x + p0.z * p0.z - pow(cy->diameter / 2, 2);
	if (!solve_quadratic_cy(coeffs, &t[1], &t[2]))
		return (0);
	if (t[1] > RAY_T_MIN && t[1] < RAY_T_MAX)
		t[0] = t[1];
	if (t[2] < t[1] && t[2] > RAY_T_MIN && t[2] < RAY_T_MAX)
		t[0] = t[2];
	else
		return (0);
	p0 = vec_add(ray.pos, vec_mult(ray.dir, t[0]));
	if (p0.y - cy->pos.y > cy->height || p0.y - cy->pos.y < 0)
		return (0);
	if (dist)
		*dist = t[0];
	return (1);
}

t_intersection	*intersects_with_cylinder(t_ray ray, t_obj *obj)
{
	float			t;
	t_cylinder		*cy;
	t_intersection	*inter;

	if (!bool_intersects_with_cylinder(ray, obj, &t))
		return (0);
	inter = (t_intersection *)malloc(sizeof(t_intersection));
	cy = (t_cylinder *)obj->details;
	inter->point = vec_add(ray.pos, vec_mult(ray.dir, t));
	inter->t = t;
	inter->diffuse = 0.4;
	inter->specular = 0.2;
	inter->s_power = 16;
	inter->obj = obj;
	inter->object_color = cy->color;
	inter->normal = cylinder_normal_at(inter->point, cy);
	return inter;
}


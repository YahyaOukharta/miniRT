#include "ray.h"

int intersects_with_sphere(t_ray ray, t_object *obj)
{
    t_sphere *sphere;
    t_ray tmp_ray;
    sphere = (t_sphere *)obj;
    	// Transform ray so we can consider origin-centred sphere
	tmp_ray = ray;
	//tmp_ray.pos = vec_sub(ray.pos,sphere->pos);;

	// Calculate quadratic coefficients
	float a = vec_len2(tmp_ray.dir); //tmp_ray.direction.length2();
	float b = 2 * vec_dot(tmp_ray.dir, tmp_ray.pos);
	float c = vec_len2(tmp_ray.pos) - sphere->diameter * sphere->diameter;

	// Check whether we intersect
	float discriminant = b * b - 4 * a * c;

	if (discriminant < 0.0)
		return 0;
	// Find two points of intersection, t1 close and t2 far
	float t1 = (-b - sqrt(discriminant)) / (2 * a); // distance
	if (t1 > RAY_T_MIN && t1 < RAY_T_MAX)
		return 1;

	float t2 = (-b + sqrt(discriminant)) / (2 * a);
	if (t2 > RAY_T_MIN && t2 < RAY_T_MAX)
		return 1;
	return 0;
}
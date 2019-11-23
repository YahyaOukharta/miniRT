#include "ray.h"

int solveQuadratic(float a,float b,float c, float *t1, float *t2) 
{ 
    float discr = b * b - 4 * a * c; 
    if (discr < 0) return 0; 
    else if (discr == 0) 
		*t1  = - 0.5 * (float)(b / a); 
    else { 
        float q = (b > 0) ? (-0.5 * (b + sqrt(discr))) : (-0.5 * (b - sqrt(discr))); 
        *t1 = q / a; 
        *t2 = c / q; 
    } 
    return 1; 
}

float intersects_with_sphere(t_ray ray, t_object *obj)
{
    t_sphere *sphere;
    t_ray tmp_ray;
	float t1,t2;
    sphere = (t_sphere *)obj->details;
    	// Transform ray so we can consider origin-centred sphere
	tmp_ray = ray;
	tmp_ray.pos = vec_sub(ray.pos,sphere->pos);;
	//printf("(%.4f,%.4f,%.4f)\t",tmp_ray.dir.x,tmp_ray.dir.y,tmp_ray.dir.z);
	// Calculate quadratic coefficients
	float a = vec_len2(tmp_ray.dir); //tmp_ray.direction.length2();
	float b = 2 * vec_dot(tmp_ray.dir, tmp_ray.pos);
	float c = vec_len2(tmp_ray.pos) - sphere->diameter * sphere->diameter;

	if (!(solveQuadratic(a,b,c, &t1,&t2)))
		return (0);
	// Find two points of intersection, t1 close and t2 far
	if (t1 > RAY_T_MIN && t1 < RAY_T_MAX)
		return t1;
	if (t2 > RAY_T_MIN && t2 < RAY_T_MAX)
		return t2;
	return 0;
}

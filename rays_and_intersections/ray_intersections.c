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

t_intersection* intersects_with_sphere(t_ray ray, t_object *obj)
{
	t_intersection *inter;
    t_sphere *sphere;
    t_ray tmp_ray;
	float t1,t2,t;
	inter = (t_intersection *)malloc(sizeof(t_intersection));
    sphere = (t_sphere *)obj->details;
    // Transform ray so we can consider origin-centred sphere
	tmp_ray = ray;
	tmp_ray.pos = vec_sub(ray.pos,sphere->pos);
	//printf("(%.4f,%.4f,%.4f)\t",tmp_ray.dir.x,tmp_ray.dir.y,tmp_ray.dir.z);
	// Calculate quadratic coefficients
	float a = vec_len2(tmp_ray.dir); //tmp_ray.direction.length2();
	float b = 2 * vec_dot(tmp_ray.dir, tmp_ray.pos);
	float c = vec_len2(tmp_ray.pos) - sphere->diameter * sphere->diameter;

	
	if (!(solveQuadratic(a,b,c, &t1,&t2)))
		return (0);
	// Find two points of intersection, t1 close and t2 far
	if (t1 > RAY_T_MIN && t1 < RAY_T_MAX)
		t = t1;
	if (t2 < t1 && t2 > RAY_T_MIN && t2 < RAY_T_MAX)
		t = t2;
	else
		return (0);
	inter->point = vec_add(ray.pos,vec_mult(ray.dir , t));
	inter->t = t;
	inter->object_color = sphere->color;
	inter->normal = vec_normalize(vec_sub(vec_add(ray.pos,vec_mult(ray.dir, t)), sphere->pos));
	inter->diffuse = 0.4;
	inter->specular = 0.2;
	inter->s_power = 4;
	return inter;
}

t_intersection *intersects_with_plane(t_ray ray, t_object *obj) 
{ 

	t_intersection *inter;
    t_plane *plane;
	float t;
	inter = (t_intersection *)malloc(sizeof(t_intersection));
    plane = (t_plane *)obj->details;

    // assuming vectors are all normalized
    float denom = vec_dot(plane->orientation, ray.dir); 
    if (denom > 1e-6) { 
        t_vector p_origin_dir = vec_sub(plane->pos, ray.pos); //plane origin
        t = vec_dot(p_origin_dir, plane->orientation) / denom; 
		if (t < RAY_T_MIN)
			return (0);
	}
	inter->point = vec_add(ray.pos,vec_mult(ray.dir , t));
	inter->t = t;
	inter->object_color = plane->color;
	inter->normal = plane->orientation;
	inter->diffuse = 0.4;
	inter->specular = 0.2;
	inter->s_power = 4;
	return inter;
} 
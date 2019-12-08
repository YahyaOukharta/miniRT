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

	inter->obj = obj;
	inter->point = vec_add(ray.pos,vec_mult(ray.dir , t));
	inter->t = t;
	inter->object_color = sphere->color;
	inter->normal = vec_normalize(vec_sub(vec_add(ray.pos,vec_mult(ray.dir, t)), sphere->pos));
	inter->diffuse = 0.4;
	inter->specular = 0.4;
	inter->s_power = 40;
	return inter;
}

t_intersection *intersects_with_plane(t_ray ray, t_object *obj) 
{ 

	t_intersection *inter;
    t_plane *plane;
	float t;
	inter = (t_intersection *)malloc(sizeof(t_intersection));
    plane = (t_plane *)obj->details;
	t_vector p_normal = vec_normalize(plane->orientation);
    // assuming vectors are all normalized
    float denom = vec_dot(p_normal, ray.dir); 
    if (fabs(denom) < RAY_T_MIN)
		return (0);
	t_vector p_origin_dir = vec_sub(plane->pos, ray.pos); //plane origin
	t = vec_dot(p_origin_dir, p_normal) / denom; 
	if (t < RAY_T_MIN)
		return (0);
	inter->obj = obj;
	inter->point = vec_add(ray.pos,vec_mult(ray.dir , t));
	inter->t = t;
	inter->object_color = plane->color;
	inter->normal = p_normal;
	inter->diffuse = 0.4;
	inter->specular = 0.4;
	inter->s_power = 2;
	return inter;
}

t_intersection *intersects_with_square(t_ray ray, t_object *obj) 
{
	t_intersection *inter;
    t_square *square;
	float t;
	inter = (t_intersection *)malloc(sizeof(t_intersection));
    square = (t_square *)obj->details;
	t_vector p_normal = vec_normalize(square->orientation);
    // assuming vectors are all normalized
    float denom = vec_dot(p_normal, ray.dir); 
    if (denom > 1e-6)
	{ 
        t_vector p_origin_dir = vec_sub(square->pos, ray.pos); //square origin
        t = vec_dot(p_origin_dir, p_normal) / denom; 
		if (t < RAY_T_MIN)
			return (0);
	}
	t_vector p = vec_add(ray.pos,vec_mult(ray.dir,t));
	float left = square->pos.x - square->side_size / 2;
	float right = square->pos.x + square->side_size / 2;
	float top = square->pos.y + square->side_size / 2;
	float bot = square->pos.y - square->side_size / 2;

	if (p.x < left || p.x > right || p.y < bot || p.y > top)
		return (0);
	inter->obj = obj;
	inter->point = p;
	inter->t = t;
	inter->object_color = square->color;
	inter->normal = p_normal;
	inter->diffuse = 0.4;
	inter->specular = 0.4;
	inter->s_power = 2;
	return inter;
} 
t_intersection *intersects_with_triangle(t_ray ray, t_object *obj)
{
	float t;
	t_triangle *tri;
	t_intersection* inter;
	inter = (t_intersection *)malloc(sizeof(t_intersection));
	tri = (t_triangle *)obj->details;
    // compute plane's normal
    t_vector edge1 = vec_sub(tri->p2 , tri->p1);
    t_vector edge2 = vec_sub(tri->p3 , tri->p1);
    t_vector h, s, q;
    float a,f,u,v;
    h = vec_cross(ray.dir,edge2);
    a = vec_dot(edge1,h);
    if (a > -RAY_T_MIN && a < RAY_T_MIN)
        return 0;    // This ray is parallel to this triangle.
    f = 1.0/a;
    s = vec_sub(ray.pos,  tri->p1);
    u = f * vec_dot(s,h);
    if (u < 0.0 || u > 1.0)
        return 0;
    q = vec_cross(s, edge1);
    v = f * vec_dot(ray.dir,q);
    if (v < 0.0 || u + v > 1.0)
        return 0;
    // At this stage we can compute t to find out where the intersection point is on the line.
    t = f * vec_dot(edge2, q);
    if (t < RAY_T_MIN && t > 1/RAY_T_MIN) // ray intersection
        return 0;

	inter->obj = obj;
	inter->point = vec_add(ray.pos, vec_mult(ray.dir, t));
	inter->normal = vec_cross(edge1, edge2);
	inter->t = t;
	inter->object_color = tri->color;
	inter->diffuse = 0.4;
	inter->specular = 0.2;
	inter->s_power = 4;
    return inter; // this ray hits the triangle 
}
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
    if (denom > 1e-6)
	{ 
        t_vector p_origin_dir = vec_sub(plane->pos, ray.pos); //plane origin
        t = vec_dot(p_origin_dir, p_normal) / denom; 
		if (t < RAY_T_MIN)
			return (0);
	}
	inter->point = vec_add(ray.pos,vec_mult(ray.dir , t));
	inter->t = t;
	inter->object_color = plane->color;
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
    t_vector p1p2 = vec_sub(tri->p2 , tri->p1);
    t_vector p1p3 = vec_sub(tri->p3 , tri->p1);
    // no need to normalize
    t_vector N = vec_cross(p1p2, p1p3); // N
    float area2 = vec_len(N); 
 
    // Step 1: finding P
 
    // check if ray and plane are parallel ?
    float NdotRayDirection = vec_dot(N, ray.dir); 
    if (fabs(NdotRayDirection) < RAY_T_MIN) // almost 0 
        return 0; // they are parallel so they don't intersect ! 
 
    // compute d parameter using equation 2
    float d = vec_dot(N,tri->p1); 
 
    // compute t (equation 3)
    t = (vec_dot(N,ray.pos) + d) / NdotRayDirection; 
    // check if the triangle is in behind the ray
    if (fabs(t) < RAY_T_MIN)return 0; // the triangle is behind 
 
    // compute the intersection point using equation 1
    t_vector P = vec_add(ray.pos , vec_mult(ray.dir, t)); 
 
    // Step 2: inside-outside test
    t_vector C; // vector perpendicular to triangle's plane 

    // edge 0
    t_vector edge0 = vec_sub(tri->p2 , tri->p1); 
    t_vector vp0 = vec_sub(P , tri->p1); 
    C = vec_cross(edge0, vp0); 
    if (vec_dot(N,C) < 0) return 0; // P is on the right side 

    // edge 1
    t_vector edge1 = vec_sub(tri->p3 , tri->p2); 
    t_vector vp1 = vec_sub(P , tri->p2); 
    C = vec_cross(edge1, vp1); 
    if (vec_dot(N,C) < 0)  return 0; // P is on the right side 

    // edge 2
    t_vector edge2 = vec_sub(tri->p1 , tri->p3); 
    t_vector vp2 = vec_sub(P , tri->p3); 
    C = vec_cross(edge2, vp2); 
    if (vec_dot(N,C) < 0) return 0; // P is on the right side; 
 

	inter->point = P;
	inter->normal = N;
	inter->t = t;
	inter->object_color = tri->color;
	inter->diffuse = 0.4;
	inter->specular = 0.2;
	inter->s_power = 4;
    return inter; // this ray hits the triangle 
} 
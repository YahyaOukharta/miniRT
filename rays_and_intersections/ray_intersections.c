#include "ray.h"

int solveQuadraticSp(float a,float b,float c, float *t1, float *t2) 
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

int bool_intersects_with_sphere(t_ray ray, t_obj *obj, float *t)
{
    t_sphere *sphere;
    t_ray tmp_ray;
	float t1,t2,d;

    sphere = (t_sphere *)obj->details;
	tmp_ray = ray;
	tmp_ray.pos = vec_sub(ray.pos,sphere->pos);
	float a = vec_len2(tmp_ray.dir);
	float b = 2 * vec_dot(tmp_ray.dir, tmp_ray.pos);
	float c = vec_len2(tmp_ray.pos) - sphere->diameter * sphere->diameter;
	if (!(solveQuadraticSp(a,b,c, &t1,&t2)))
		return (0);	
	d = 0;
	if (t1 > RAY_T_MIN)
		d = t1;
	if (t2 < t1 && t2 > RAY_T_MIN)
		d = t2;
	if (!d)
		return (0);
	if (t)
		*t = d;
	return (1);
}

t_intersection* intersects_with_sphere(t_ray ray, t_obj *obj)
{
	t_intersection *inter;
    t_sphere *sphere;
    t_ray tmp_ray;
	float t1,t2,t;
	if (!bool_intersects_with_sphere(ray,obj,&t))
		return (0);
	inter = (t_intersection *)malloc(sizeof(t_intersection));
	inter->obj = obj;
	sphere = (t_sphere *)obj->details;
	inter->point = vec_add(ray.pos,vec_mult(ray.dir , t));
	inter->t = t;
	inter->object_color = sphere->color;
	inter->normal = vec_mult(vec_normalize(vec_sub(vec_add(ray.pos,vec_mult(ray.dir, t)), sphere->pos)),1);//,(t1 < RAY_T_MIN && t2 > RAY_T_MIN ? -1 : 1 ));
	inter->diffuse = 0.4;
	inter->specular = 0.4;
	inter->s_power = 20;
	return inter;
}

int				bool_intersects_with_plane(t_ray ray, t_obj *obj, float *t) 
{
    t_plane *plane;
	float d;
    plane = (t_plane *)obj->details;
	t_vector p_normal = vec_normalize(plane->orientation);
    float denom = vec_dot(p_normal, ray.dir); 
    if (fabs(denom) < 1e-6)
		return (0);
	t_vector p_origin_dir = vec_sub(plane->pos, ray.pos);
	d = vec_dot(p_origin_dir, p_normal) / denom; 
	if (d < RAY_T_MIN)
		return (0);
	if (t)
		*t = d;
	return (1);
}
t_intersection *intersects_with_plane(t_ray ray, t_obj *obj) 
{
	t_intersection *inter;
    t_plane *plane;
	float t;

	if (!bool_intersects_with_plane(ray, obj, &t))
		return (0);
	inter = (t_intersection *)malloc(sizeof(t_intersection));
    plane = (t_plane *)obj->details;	
	inter->obj = obj;
	inter->point = vec_add(ray.pos,vec_mult(ray.dir , t));
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
	float d;
	t_triangle *tri;
	tri = (t_triangle *)obj->details;
    t_vector edge1 = vec_sub(tri->p2 , tri->p1);
    t_vector edge2 = vec_sub(tri->p3 , tri->p1);
    t_vector h, s, q;
    float a,f,u,v;
    h = vec_cross(ray.dir,edge2);
    a = vec_dot(edge1,h);
    if (fabs(a) < RAY_T_MIN)
        return 0;
    f = 1.0/a;
    s = vec_sub(ray.pos,  tri->p1);
    u = f * vec_dot(s,h);
    if (u < 0.0 || u > 1.0)
        return 0;
    q = vec_cross(s, edge1);
    v = f * vec_dot(ray.dir,q);
    if (v < 0.0 || u + v > 1.0)
        return 0;
    d = f * vec_dot(edge2, q);
    if (d < RAY_T_MIN && d > 1 / RAY_T_MIN)
        return 0;
	if (t)
		*t = d;
	return (1);
}
t_intersection *intersects_with_triangle(t_ray ray, t_obj *obj)
{
	float t;
	t_triangle *tri;
	t_intersection* inter;

	if (!bool_intersects_with_triangle(ray, obj, &t))
		return (0);
	inter = (t_intersection *)malloc(sizeof(t_intersection));
	tri = (t_triangle *)obj->details;
	inter->obj = obj;
	inter->point = vec_add(ray.pos, vec_mult(ray.dir, t));
	inter->normal = vec_cross(vec_sub(tri->p2 , tri->p1), vec_sub(tri->p3 , tri->p1));
	inter->t = t;
	inter->object_color = tri->color;
	inter->diffuse = 0.4;
	inter->specular = 0.2;
	inter->s_power = 4;
    return inter;
}

t_intersection *intersects_with_square(t_ray ray, t_obj *obj)
{
	float t;
	t_square *sq;
	t_intersection* inter;
	inter = (t_intersection *)malloc(sizeof(t_intersection));
	sq = (t_square *)obj->details;
	t_vector tmp;

	// float Rx,Ry;
	// tmp = vec_normalize(sq->orientation);
	// tmp.x = 0;
	// tmp = vec_normalize(tmp);
	// Rx = acos(vec_dot(vec_create(0,0,1),tmp));
	// tmp = vec_normalize(sq->orientation);
	// tmp.y = 0;
	// tmp = vec_normalize(tmp);
	// Ry = acos(vec_dot(vec_create(0,0,1),tmp));
	// ray.dir = vec_rotate(ray.dir,vec_create(Rx,Ry,0));

	t_vector p_normal = vec_normalize(sq->orientation);
    // assuming vectors are all normalized
    float denom = vec_dot(p_normal, ray.dir);
    if (fabs(denom) < RAY_T_MIN)
		return (0);
	t_vector p_origin_dir = vec_sub(sq->pos, ray.pos); //sq origin
	t = vec_dot(p_origin_dir, p_normal) / denom;
	if (t < RAY_T_MIN)
		return (0);

	t_vector p = vec_add(ray.pos , vec_mult(ray.dir, t));

	float l,r,u,d;
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
t_vector cylinder_normal_at(t_vector point ,t_cylinder *cy)
{
	t_vector normalIntersectionPoint = vec_sub(point ,cy->pos);
	return ((fabs(normalIntersectionPoint.y) < cy->height)
		? (vec_normalize(vec_create(normalIntersectionPoint.x, 0, normalIntersectionPoint.z)))
		: vec_normalize(normalIntersectionPoint));
		
}

int				bool_intersects_with_cylinder (t_ray ray, t_obj *obj, float *t)
{
	float d,t1,t2;
	t_cylinder *cy;
	cy = (t_cylinder *)obj->details;
	t_vector p0 = vec_sub(ray.pos,cy->pos);
	double a = ray.dir.x*ray.dir.x+ray.dir.z*ray.dir.z;
	double b = ray.dir.x*p0.x +ray.dir.z*p0.z;
	double c = p0.x * p0.x + p0.z * p0.z - pow(cy->diameter / 2, 2);
	double delta = b * b - a * c;
	if (delta < RAY_T_MIN)
			return 0;
	t2 = (-b - sqrt (delta)) /a;
	t1 = (-b + sqrt (delta)) /a;

	if (t1 > RAY_T_MIN && t1 < RAY_T_MAX)
		d = t1;
	if (t2 < t1 && t2 > RAY_T_MIN && t2 < RAY_T_MAX)
		d = t2;
	else
		return (0);
	t_vector point = vec_add(ray.pos,vec_mult(ray.dir,d));
	if (point.y - cy->pos.y > cy->height || point.y - cy->pos.y < 0)
		return(0);
	if (t)
		*t = d;
	return (1);
}

t_intersection *intersects_with_cylinder (t_ray ray, t_obj *obj)
{
	float t;
	t_cylinder *cy;
	t_intersection* inter;

	if(!bool_intersects_with_cylinder(ray, obj, &t))
		return (0);
	inter = (t_intersection *)malloc(sizeof(t_intersection));
	cy = (t_cylinder *)obj->details;	
	inter->point = vec_add(ray.pos,vec_mult(ray.dir,t));
	inter->t = t;
	inter->diffuse = 0.4;
	inter->specular = 0.2;
	inter->s_power = 16;
	inter->obj = obj;
	inter->object_color = cy->color;
	inter->normal = cylinder_normal_at(inter->point,cy);
	return inter;
}

t_intersection *intersects_with_cyelinder (t_ray ray, t_obj *obj)
{
	t_cylinder *cy;
	t_intersection* inter;
	inter = (t_intersection *)malloc(sizeof(t_intersection));
	cy = (t_cylinder *)obj->details;
	t_vector intersectionPoint = vec_sub(ray.pos, cy->pos);
	float t;
	int isBelongToCylinderBase = 0;
	float ts1 = (cy->height - ray.pos.y + cy->pos.y) / ray.dir.y;
	t_vector point = vec_add(intersectionPoint ,vec_mult( ray.dir ,ts1));

	if (point.x * point.x + point.z * point.z - pow(cy->diameter/2,2) < RAY_T_MIN)
		isBelongToCylinderBase = 1;

	float ts2 = (-cy->height - ray.pos.y + cy->pos.y) / ray.dir.y;
	point = vec_add(intersectionPoint ,vec_mult( ray.dir ,ts2));
	if (point.x * point.x + point.z * point.z - pow(cy->diameter/2,2) < RAY_T_MIN)
		isBelongToCylinderBase = 1;

	float a = ray.dir.x * ray.dir.x + ray.dir.z * ray.dir.z;
	float b = (ray.pos.x * ray.dir.x - ray.dir.x * cy->pos.x + ray.pos.z * ray.dir.z - ray.dir.z * cy->pos.z);
	float c = ray.pos.x * ray.pos.x + cy->pos.x * cy->pos.x + ray.pos.z * ray.pos.z + cy->pos.z * cy->pos.z -
			2 * (ray.pos.x * cy->pos.x + ray.pos.z * cy->pos.z) - pow(cy->diameter/2, 2);

	float delta = b * b - a * c;

	if (delta < RAY_T_MIN)
		return 0;
	else {
		float  t1 = (-b - sqrt(delta)) / a;
		float  t2 = (-b + sqrt(delta)) / a;

		t = 0;
		if (t1 > RAY_T_MIN)
			t = t1;
		if (t2 < t1 && t2 > RAY_T_MIN)
			t = t2;
		if (!t)
			return (0);
		//if (!(fabs(ray.pos.y + t * ray.dir.y - cy->pos.y) > cy->pos.z)) ///////
		//	return 0;
		if (isBelongToCylinderBase) 
			t = fmin(fmin(ts1, ts2),t);
	}
	inter->point = vec_add(ray.pos,vec_mult(ray.dir,t));
	inter->t = t;
	inter->diffuse = 0.4;
	inter->specular = 0.2;
	inter->s_power = 4;
	inter->obj = obj;
	inter->object_color = cy->color;
	inter->normal = cylinder_normal_at(inter->point, cy);
	return inter;
}

void init_obj_intersector(void)
{
    g_obj_inter[0] = intersects_with_sphere;
    //g_obj_inter[1] = intersects_with_plane;
    //g_obj_inter[2] = intersects_with_triangle;
    //g_obj_inter[3] = intersects_with_square;
    //g_obj_inter[4] = intersects_with_cylinder;
}


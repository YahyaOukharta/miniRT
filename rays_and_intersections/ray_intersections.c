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
	float a = vec_len2(tmp_ray.dir); //tmp_ray.ray.dir.length2();
	float b = 2 * vec_dot(tmp_ray.dir, tmp_ray.pos);
	float c = vec_len2(tmp_ray.pos) - sphere->diameter * sphere->diameter;
	if (!(solveQuadraticSp(a,b,c, &t1,&t2)))
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
	inter->normal = vec_mult(vec_normalize(vec_sub(vec_add(ray.pos,vec_mult(ray.dir, t)), sphere->pos)),(t1 < RAY_T_MIN && t2 > RAY_T_MIN ? -1 : 1 ));
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
    if (denom < 1e-6)
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
    if (t < RAY_T_MIN && t > 1 / RAY_T_MIN) // ray intersection
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



t_intersection *intersects_with_square(t_ray ray, t_object *obj)
{
	float t;
	t_square *sq;
	t_intersection* inter;
	inter = (t_intersection *)malloc(sizeof(t_intersection));
	sq = (t_square *)obj->details;
	t_vector tmp;

	float Rx,Ry;
	tmp = vec_normalize(sq->orientation);
	tmp.x = 0;
	tmp = vec_normalize(tmp);
	Rx = acos(vec_dot(vec_create(0,0,1),tmp));
	tmp = vec_normalize(sq->orientation);
	tmp.y = 0;
	tmp = vec_normalize(tmp);
	Ry = acos(vec_dot(vec_create(0,0,1),tmp));
	ray.dir = vec_rotate(ray.dir,vec_create(Rx,Ry,0));

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
	l = (p.x - sq->side_size / 2);
	r = (p.x + sq->side_size / 2);
	u = (p.y + sq->side_size / 2);
	d = (p.y - sq->side_size / 2);

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
		
}t_intersection *intersects_with_cyelinder (t_ray ray, t_object *obj)
{
	float t,t1,t2;
	t_cylinder *cy;
	t_intersection* inter;
	inter = (t_intersection *)malloc(sizeof(t_intersection));
	cy = (t_cylinder *)obj->details;
	// translate the ray origin
	t_vector tmp;
	float Rx,Rz;
	tmp = vec_normalize(cy->orientation);
	tmp.x = 0;
	tmp = vec_normalize(tmp);
	Rx = acos(vec_dot(vec_create(0,1,0),tmp));
	tmp = vec_normalize(cy->orientation);
	tmp.z = 0;
	tmp = vec_normalize(tmp);
	Rz = acos(vec_dot(vec_create(0,1,0),tmp));
	ray.dir = vec_rotate(ray.dir,vec_create(Rx,0,Rz));
	//ray.pos = vec_rotate(ray.pos,vec_create(Rx,0,Rz));
	t_vector p0 = vec_sub(ray.pos,cy->pos);
	//vec_create(ray.pos.x - cy->pos.x, ray.pos.y - cy->pos.y, ray.pos.z - cy->pos.z);

	// coefficients for the intersection equation
	// got them mathematically intersecting the line equation with the cylinder equation
	double a = ray.dir.x*ray.dir.x+ray.dir.z*ray.dir.z;
	double b = ray.dir.x*p0.x +ray.dir.z*p0.z;
	double c = p0.x * p0.x + p0.z * p0.z - pow(cy->diameter / 2, 2);

	double delta = b * b - a * c;

	//delta < 0 means no intersections
	if (delta < RAY_T_MIN)
			return 0;
	// nearest intersection
	t2 = (-b - sqrt (delta)) /a;
	t1 = (-b + sqrt (delta)) /a;

	if (t1 > RAY_T_MIN && t1 < RAY_T_MAX)
		t = t1;
	if (t2 < t1 && t2 > RAY_T_MIN && t2 < RAY_T_MAX)
		t = t2;
	else
		return (0);
	t_vector point = vec_add(ray.pos,vec_mult(ray.dir,t));
	if (point.y - cy->pos.y > cy->height || point.y - cy->pos.y < 0)
		return(0);
	inter->point = point;
	inter->t = t;
	inter->diffuse = 0.4;
	inter->specular = 0.2;
	inter->s_power = 16;
	inter->obj = obj;
	inter->object_color = cy->color;
	inter->normal = cylinder_normal_at(inter->point,cy);
	return inter;
}

t_intersection *intersects_with_cylinder (t_ray ray, t_object *obj)
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

	float discriminant = b * b - a * c;

	if (discriminant < RAY_T_MIN)
	{
		return 0;
	}else {
		float  t1 = (-b - sqrt(discriminant)) / a;
		float  t2 = (-b + sqrt(discriminant)) / a;

		t = t1;
		if (t1 < RAY_T_MIN)
			t = t2;
		if (t < RAY_T_MIN)
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



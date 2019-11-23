#ifndef RAY_H
# define RAY_H
#include "../minirt.h"
// In order to prevent bouncing rays self-intersecting
#define RAY_T_MIN 0.0001

// 'Infinite' distance, used as a default value
#define RAY_T_MAX 1.0e30

typedef struct s_ray
{
    t_vector pos;
    t_vector dir;
}               t_ray;
float intersects_with_sphere(t_ray ray, t_object *obj);
#endif
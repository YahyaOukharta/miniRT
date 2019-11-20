/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youkhart <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/17 02:30:54 by youkhart          #+#    #+#             */
/*   Updated: 2019/11/17 02:49:24 by youkhart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef __OBJECTS_H__
# define __OBJECTS_H__
#include "minirt.h"
typedef struct	s_vector
{
	float x;
	float y;
	float z;
}				t_vector;

typedef struct s_object
{
	char *type;
	void *details;
}				t_object;

typedef struct	s_ambient_light
{
	float		brightness;
	int			color;
}				t_ambient_light;

typedef struct	s_camera
{
	t_vector pos;
	t_vector dir;

	int		fov; //probably
}				t_camera;

typedef struct	s_light
{
	t_vector pos;
	
	float	brightness;
	int		color;
}				t_light;

typedef struct	s_sphere
{
	t_vector pos;
	
	float	diameter;
	int		color;
}				t_sphere;

typedef struct	s_plane
{
	t_vector pos;
	t_vector orientation;

	int		color;
}				t_plane;

typedef struct	s_square
{
	t_vector pos;
	t_vector orientation;

	float side_size;
	int		color;
}				t_square;

typedef struct	s_cylinder
{
	t_vector pos;
	t_vector orientation;

	float diameter;
	float height;

	int		color;
}				t_cylinder;

typedef struct	s_triangle
{
	t_vector p1;
	t_vector p2;
	t_vector p3;

	int		color;
}				t_triangle;

struct g_resolution
{
	int x;
	int y;
};

char		*g_supported_objects = "R;A;c;l;pl;sp;sq;cy;tr";
t_object	*g_objects;



#endif
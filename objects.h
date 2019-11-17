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

typedef struct	s_ambient_light
{
	float		brightness;
	int			color;
}				t_ambient_light;

typedef struct	s_camera
{
	float x;
	float y;
	float z;
	
	float dx;
	float dy;
	float dz;
	
	int		fov; //probably
}				t_camera;

typedef struct	s_light
{
	float	x;
	float	y;
	float	z;
	
	float	brightness;
	int		color;
}				t_light;

typedef struct	s_sphere
{
	float	x;
	float	y;
	float	z;
	
	float	diameter;
	int		color;
}				t_sphere;

typedef struct	s_plane
{
	float	x;
	float	y;
	float	z;
	
	float dx;
	float dy;
	float dz;

	int		color;
}				t_plane;

typedef struct	s_square
{
	float	x;
	float	y;
	float	z;
	
	float dx;
	float dy;
	float dz;

	float side_size;

	int		color;
}				t_square;

typedef struct	s_cylinder
{
	float	x;
	float	y;
	float	z;
	
	float dx;
	float dy;
	float dz;

	float diameter;
	float height;

	int		color;
}				t_cylinder;

typedef struct	s_triangle
{
	float	x1;
	float	y1;
	float	z1;
	
	float	x2;
	float	y2;
	float	z2;

	float	x3;
	float	y3;
	float	z3;

	int		color;
}				t_triangle;

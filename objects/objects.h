/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youkhart <youkhart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/25 22:00:16 by youkhart          #+#    #+#             */
/*   Updated: 2019/12/25 22:02:14 by youkhart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJECTS_H
# define OBJECTS_H
# define TRANS_VEL 0.1
# define ROT_VEL 0.1

typedef struct	s_vector
{
	float		x;
	float		y;
	float		z;
}				t_vector;

typedef struct	s_object
{
	char		*type;
	void		*details;
}				t_obj;

typedef struct	s_camera
{
	t_vector	pos;
	t_vector	dir;
	t_vector	rot;
	int			fov;
}				t_cam;

typedef struct	s_light
{
	t_vector	pos;
	float		brightness;
	int			color;
}				t_light;

typedef struct	s_sphere
{
	t_vector	pos;
	float		diameter;
	int			color;
}				t_sphere;

typedef struct	s_plane
{
	t_vector	pos;
	t_vector	orientation;
	int			color;
}				t_plane;

typedef struct	s_square
{
	t_vector	pos;
	t_vector	orientation;
	float		side_size;
	int			color;
}				t_square;

typedef struct	s_cylinder
{
	t_vector	pos;
	t_vector	orientation;
	float		diameter;
	float		height;
	int			color;
}				t_cylinder;

typedef struct	s_triangle
{
	t_vector	p1;
	t_vector	p2;
	t_vector	p3;
	int			color;
}				t_triangle;

struct			s_resolution
{
	int			is_set;
	int			x;
	int			y;
};

struct			s_ambient_light
{
	int			is_set;
	float		brightness;
	int			color;
};

void			init_obj_constructor(void);
void			init_obj_transformer(void);
t_cam			*new_camera(char **info);
int				add_camera(char **tab);
t_light			*new_light(char **info);
int				add_light(char **tab);
int				transform_light(int key, void *param);
t_sphere		*new_sphere(char **info);
int				add_sphere(char **tab);
int				transform_sphere(int key, void *param);
t_square		*new_square(char **info);
int				add_square(char **tab);
int				transform_square(int key, void *param);
t_plane			*new_plane(char **info);
int				add_plane(char **tab);
int				transform_plane(int key, void *param);
t_plane			*new_plane(char **info);
int				add_plane(char **tab);
int				transform_plane(int key, void *param);
t_cylinder		*new_cylinder(char **info);
int				add_cylinder(char **tab);
int				transform_cylinder(int key, void *param);
t_triangle		*new_triangle(char **info);
int				add_triangle(char **tab);
int				transform_triangle(int key, void *param);
typedef	int(*t_obj_constr)(char **);
t_obj_constr g_obj_constructor[10];
typedef	int(*t_obj_trans)(int, void *);
t_obj_trans g_obj_transformer[10];
#endif

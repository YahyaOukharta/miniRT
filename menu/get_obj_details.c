/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_obj_details.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youkhart <youkhart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/26 08:01:56 by youkhart          #+#    #+#             */
/*   Updated: 2019/12/26 08:09:11 by youkhart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "menu.h"

extern struct s_minirt g_rt;

char	**get_sphere_details(t_obj *obj)
{
	t_sphere	*sph;
	char		**tab;

	sph = (t_sphere *)obj->details;
	tab = (char **)malloc(sizeof(char *) * (4 + 1));
	tab[0] = ft_strdup("Type = Sphere");
	tab[1] = ft_strjoin_va(7, "Pos = (", ft_ftoa(sph->pos.x, PRECISION),
		",", ft_ftoa(sph->pos.y, PRECISION), ",",
		ft_ftoa(sph->pos.z, PRECISION), ")");
	tab[2] = ft_strjoin_va(2, "Radius = ",
		ft_ftoa(sph->diameter / 2, PRECISION));
	tab[3] = ft_strjoin_va(2, "Color = ", ft_itoa(sph->color));
	tab[4] = 0;
	return (tab);
}

char	**get_plane_details(t_obj *obj)
{
	t_plane		*plane;
	char		**tab;

	plane = (t_plane *)obj->details;
	tab = (char **)malloc(sizeof(char *) * (4 + 1));
	tab[0] = ft_strdup("Type = Plane");
	tab[1] = ft_strjoin_va(7, "Pos = (", ft_ftoa(plane->pos.x, PRECISION),
		",", ft_ftoa(plane->pos.y, PRECISION), ",",
		ft_ftoa(plane->pos.z, PRECISION), ")");
	tab[2] = ft_strjoin_va(7, "Dir = (", ft_ftoa(plane->orientation.x,
		PRECISION), ",", ft_ftoa(plane->orientation.y, PRECISION), ",",
		ft_ftoa(plane->orientation.z, PRECISION), ")");
	tab[3] = ft_strjoin_va(2, "Color = ", ft_itoa(plane->color));
	tab[4] = 0;
	return (tab);
}

char	**get_cylinder_details(t_obj *obj)
{
	t_cylinder	*cylinder;
	char		**tab;

	cylinder = (t_cylinder *)obj->details;
	tab = (char **)malloc(sizeof(char *) * (6 + 1));
	tab[0] = ft_strdup("Type = cylinder");
	tab[1] = ft_strjoin_va(7, "Pos = (", ft_ftoa(cylinder->pos.x, PRECISION),
	",", ft_ftoa(cylinder->pos.y, PRECISION), ",",
		ft_ftoa(cylinder->pos.z, PRECISION), ")");
	tab[2] = ft_strjoin_va(7, "Dir = (", ft_ftoa(cylinder->orientation.x,
		PRECISION), ",", ft_ftoa(cylinder->orientation.y, PRECISION), ",",
		ft_ftoa(cylinder->orientation.z, PRECISION), ")");
	tab[3] = ft_strjoin_va(4, "Radius = ", ft_ftoa(cylinder->diameter / 2,
	PRECISION), " Height = ", ft_ftoa(cylinder->height, PRECISION));
	tab[4] = ft_strjoin_va(2, "Color = ", ft_itoa(cylinder->color));
	tab[5] = 0;
	return (tab);
}

char	**get_triangle_details(t_obj *obj)
{
	t_triangle	*tri;
	char		**tab;

	tri = (t_triangle *)obj->details;
	tab = (char **)malloc(sizeof(char *) * (5 + 1));
	tab[0] = ft_strdup("Type = Triangle");
	tab[1] = ft_strjoin_va(7, "P1 = (", ft_ftoa(tri->p1.x, PRECISION), ",",
		ft_ftoa(tri->p1.y, PRECISION), ",", ft_ftoa(tri->p1.z, PRECISION), ")");
	tab[2] = ft_strjoin_va(7, "P2 = (", ft_ftoa(tri->p2.x, PRECISION), ",",
		ft_ftoa(tri->p2.y, PRECISION), ",", ft_ftoa(tri->p2.z, PRECISION), ")");
	tab[3] = ft_strjoin_va(7, "P3 = (", ft_ftoa(tri->p3.x, PRECISION), ",",
		ft_ftoa(tri->p3.y, PRECISION), ",", ft_ftoa(tri->p3.z, PRECISION), ")");
	tab[4] = ft_strjoin_va(2, "Color = ", ft_itoa(tri->color));
	tab[5] = 0;
	return (tab);
}

char	**get_square_details(t_obj *obj)
{
	t_square	*square;
	char		**tab;

	square = (t_square *)obj->details;
	tab = (char **)malloc(sizeof(char *) * (5 + 1));
	tab[0] = ft_strdup("Type = Square");
	tab[1] = ft_strjoin_va(7, "Pos = (", ft_ftoa(square->pos.x, PRECISION), ",",
		ft_ftoa(square->pos.y, PRECISION), ",",
		ft_ftoa(square->pos.z, PRECISION), ")");
	tab[2] = ft_strjoin_va(7, "Dir = (", ft_ftoa(square->orientation.x,
		PRECISION), ",", ft_ftoa(square->orientation.y, PRECISION), ",",
		ft_ftoa(square->orientation.z, PRECISION), ")");
	tab[3] = ft_strjoin_va(2, "Side size = ",
		ft_ftoa(square->side_size, PRECISION));
	tab[4] = ft_strjoin_va(2, "Color = ", ft_itoa(square->color));
	tab[5] = 0;
	return (tab);
}

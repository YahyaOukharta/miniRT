/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_obj_details_two.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youkhart <youkhart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/26 08:08:43 by youkhart          #+#    #+#             */
/*   Updated: 2019/12/26 08:08:44 by youkhart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "menu.h"

extern struct s_minirt g_rt;

int		init_menu(void)
{
	g_rt.g_menu.w = 300;
	g_rt.g_menu.opacity = 0.6;
	init_obj_details();
	return (1);
}

void	init_obj_details(void)
{
	g_obj_details[0] = get_cam_details;
	g_obj_details[1] = get_light_details;
	g_obj_details[2] = get_sphere_details;
	g_obj_details[3] = get_plane_details;
	g_obj_details[4] = get_square_details;
	g_obj_details[5] = get_cylinder_details;
	g_obj_details[6] = get_triangle_details;
}

char	**get_light_details(t_obj *obj)
{
	t_light	*light;
	char	**tab;

	light = (t_light *)obj->details;
	tab = (char **)malloc(sizeof(char *) * (4 + 1));
	tab[0] = ft_strdup("Type = Light");
	tab[1] = ft_strjoin_va(7, "Pos = (", ft_ftoa(light->pos.x, PRECISION), ",",
		ft_ftoa(light->pos.y, PRECISION), ",",
		ft_ftoa(light->pos.z, PRECISION), ")");
	tab[2] = ft_strjoin_va(2, "brightness = (",
		ft_ftoa(light->brightness, PRECISION));
	tab[3] = ft_strjoin_va(2, "Color = ", ft_itoa(light->color));
	tab[4] = 0;
	return (tab);
}

char	**get_cam_details(t_obj *obj)
{
	t_cam		*cam;
	t_vector	dir;
	char		**tab;

	cam = (t_cam *)obj->details;
	dir = vec_rotate(vec_create(0, 0, -1), cam->rot);
	tab = (char **)malloc(sizeof(char *) * (4 + 1));
	tab[0] = ft_strdup("Type = Camera");
	tab[1] = ft_strjoin_va(7, "Pos = (", ft_ftoa(cam->pos.x, PRECISION), ",",
		ft_ftoa(cam->pos.y, PRECISION), ",",
		ft_ftoa(cam->pos.z, PRECISION), ")");
	tab[2] = ft_strjoin_va(7, "Dir = (", ft_ftoa(dir.x, PRECISION), ",",
		ft_ftoa(dir.y, PRECISION), ",", ft_ftoa(dir.z, PRECISION), ")");
	tab[3] = ft_strjoin_va(2, "FOV = ", ft_itoa(cam->fov));
	tab[4] = 0;
	return (tab);
}

char	**get_obj_details(t_obj *obj)
{
	int	index;

	index = index_of_in_tab(obj->type,
		ft_split(g_rt.g_supported_objects, ';')) - 2;
	return (g_obj_details[index](obj));
}

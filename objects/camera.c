/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youkhart <youkhart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/25 21:59:57 by youkhart          #+#    #+#             */
/*   Updated: 2020/01/23 19:42:08 by youkhart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects.h"
#include "../minirt.h"

extern struct s_minirt g_rt;

t_cam		*new_camera(char **info)
{
	t_cam		*new_cam;
	char		**tab;
	t_vector	tmp;

	new_cam = (t_cam *)malloc(sizeof(t_cam));
	tab = ft_split(info[1], ',');
	new_cam->pos.x = ft_atof(tab[0]);
	new_cam->pos.y = ft_atof(tab[1]);
	new_cam->pos.z = ft_atof(tab[2]);
	free_s_tab(tab);
	tab = ft_split(info[2], ',');
	new_cam->dir.x = ft_atof(tab[0]);
	new_cam->dir.y = ft_atof(tab[1]);
	new_cam->dir.z = (!ft_atof(tab[2]) ? -0.001 : ft_atof(tab[2]));
	free_s_tab(tab);
	new_cam->fov = ft_atof(info[3]);
	new_cam->rot = vec_create(0, 0, 0);
	tmp = vec_normalize(new_cam->dir);
	tmp.x = 0;
	new_cam->rot.x = acos(vec_dot(vec_create(0, 0, -1), vec_normalize(tmp)));
	tmp = vec_normalize(new_cam->dir);
	tmp.y = 0;
	new_cam->rot.y = acos(vec_dot(vec_create(0, 0, -1), vec_normalize(tmp)));
	return (new_cam);
}

int			add_camera(char **tab)
{
	t_obj *obj;

	obj = (t_obj *)malloc(sizeof(t_obj));
	obj->type = ft_strdup(tab[0]);
	obj->details = (void *)new_camera(tab);
	ft_lstadd_back(&g_rt.cameras, ft_lstnew(obj));
	return (1);
}

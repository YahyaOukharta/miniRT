/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youkhart <youkhart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/25 22:00:00 by youkhart          #+#    #+#             */
/*   Updated: 2019/12/25 22:00:50 by youkhart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects.h"
#include "../minirt.h"

extern struct s_minirt g_rt;

t_cylinder	*new_cylinder(char **info)
{
	t_cylinder	*new_cylinder;
	char		**tab;

	new_cylinder = (t_cylinder *)malloc(sizeof(t_cylinder));
	tab = ft_split(info[1], ',');
	new_cylinder->pos.x = ft_atof(tab[0]);
	new_cylinder->pos.y = ft_atof(tab[1]);
	new_cylinder->pos.z = ft_atof(tab[2]);
	free_s_tab(tab);
	tab = ft_split(info[2], ',');
	new_cylinder->orientation.x = ft_atof(tab[0]);
	new_cylinder->orientation.y = ft_atof(tab[1]);
	new_cylinder->orientation.z = ft_atof(tab[2]);
	free_s_tab(tab);
	new_cylinder->diameter = ft_atof(info[3]);
	new_cylinder->height = ft_atof(info[4]);
	new_cylinder->color = rgb_to_int(info[5]);
	return (new_cylinder);
}

int			add_cylinder(char **tab)
{
	t_obj *obj;

	obj = (t_obj *)malloc(sizeof(t_obj));
	obj->type = ft_strdup(tab[0]);
	obj->details = (void *)new_cylinder(tab);
	ft_lstadd_back(&g_rt.objects, ft_lstnew(obj));
	return (1);
}

int			transform_cylinder(int key, void *param)
{
	t_cylinder	*cy;
	t_cam		*cam;

	(void)param;
	cy = (t_cylinder *)g_rt.selected_object->details;
	cam = (t_cam *)((t_obj *)g_rt.curr_cam->content)->details;
	if (key == KEY_D || key == KEY_A)
		cy->pos = vec_add(cy->pos, vec_mult(vec_rotate(vec_create(1, 0, 0),
				cam->rot), (key == KEY_D ? 1 : -1) * TRANS_VEL));
	if (key == KEY_W || key == KEY_S)
		cy->pos = vec_add(cy->pos, vec_mult(vec_rotate(vec_create(0, 1, 0),
				cam->rot), (key == KEY_W ? 1 : -1) * TRANS_VEL));
	if (key == KEY_RIGHT)
		cy->orientation = vec_rotate(cy->orientation,
			vec_create(0, 0, ROT_VEL));
	if (key == KEY_LEFT)
		cy->orientation = vec_rotate(cy->orientation,
			vec_create(0, 0, -ROT_VEL));
	if (key == KEY_UP)
		cy->orientation = vec_rotate(cy->orientation,
			vec_create(ROT_VEL, 0, 0));
	if (key == KEY_DOWN)
		cy->orientation = vec_rotate(cy->orientation,
			vec_create(-ROT_VEL, 0, 0));
	return (0);
}

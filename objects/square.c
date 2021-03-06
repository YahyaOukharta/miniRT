/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   square.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youkhart <youkhart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/25 22:00:25 by youkhart          #+#    #+#             */
/*   Updated: 2020/01/14 18:47:43 by youkhart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects.h"
#include "../minirt.h"

extern struct s_minirt g_rt;

t_square	*new_square(char **info)
{
	t_square	*new_square;
	char		**tab;

	new_square = (t_square *)malloc(sizeof(t_square));
	tab = ft_split(info[1], ',');
	new_square->pos.x = ft_atof(tab[0]);
	new_square->pos.y = ft_atof(tab[1]);
	new_square->pos.z = ft_atof(tab[2]);
	free_s_tab(tab);
	tab = ft_split(info[2], ',');
	new_square->orientation.x = ft_atof(tab[0]) * M_PI;
	new_square->orientation.y = ft_atof(tab[1]) * M_PI;
	new_square->orientation.z = ft_atof(tab[2]) * M_PI;
	free_s_tab(tab);
	new_square->side_size = ft_atof(info[3]);
	new_square->color = rgb_to_int(info[4]);
	return (new_square);
}

int			add_square(char **tab)
{
	t_obj *obj;

	obj = (t_obj *)malloc(sizeof(t_obj));
	obj->type = ft_strdup(tab[0]);
	obj->details = (void *)new_square(tab);
	ft_lstadd_back(&g_rt.objects, ft_lstnew(obj));
	return (1);
}

int			transform_square(int key, void *param)
{
	t_square	*square;
	t_cam		*cam;

	(void)param;
	square = (t_square *)g_rt.selected_object->details;
	cam = (t_cam *)((t_obj *)g_rt.curr_cam->content)->details;
	if (key == KEY_D || key == KEY_A)
		square->pos = vec_add(square->pos,
			vec_mult(vec_rotate(vec_create(1, 0, 0), cam->rot),
				(key == KEY_D ? 1 : -1) * TRANS_VEL));
	if (key == KEY_W || key == KEY_S)
		square->pos = vec_add(square->pos,
			vec_mult(vec_rotate(vec_create(0, 1, 0), cam->rot),
				(key == KEY_W ? 1 : -1) * TRANS_VEL));
	if (key == KEY_RIGHT)
		square->orientation.y = square->orientation.y + ROT_VEL;
	if (key == KEY_LEFT)
		square->orientation.y = square->orientation.y - ROT_VEL;
	if (key == KEY_UP)
		square->orientation.x = square->orientation.x + ROT_VEL;
	if (key == KEY_DOWN)
		square->orientation.x = square->orientation.x - ROT_VEL;
	return (0);
}

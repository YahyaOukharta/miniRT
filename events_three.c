/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_three.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youkhart <youkhart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/25 22:20:42 by youkhart          #+#    #+#             */
/*   Updated: 2020/01/16 22:11:53 by youkhart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

extern struct s_minirt	g_rt;

int	rotate_camera(int key, void *param)
{
	t_cam *cam;

	(void)param;
	cam = (t_cam *)((t_obj *)g_rt.curr_cam->content)->details;
	if (key == KEY_RIGHT)
		cam->rot.y -= 0.1;
	if (key == KEY_LEFT)
		cam->rot.y += 0.1;
	if (key == KEY_UP)
		cam->rot.x -= 0.1;
	if (key == KEY_DOWN)
		cam->rot.x += 0.1;
	re_render(key, NULL);
	return (0);
}

int	move_camera(int key, void *param)
{
	t_cam *cam;
	float vel;

	vel = 0.8;
	cam = (t_cam *)((t_obj *)g_rt.curr_cam->content)->details;
	if (key == KEY_D)
		cam->pos = vec_add(cam->pos,
			vec_mult(vec_rotate(vec_create(1, 0, 0), cam->rot), vel));
	if (key == KEY_A)
		cam->pos = vec_add(cam->pos,
			vec_mult(vec_rotate(vec_create(1, 0, 0), cam->rot), -vel));
	if (key == KEY_W)
		cam->pos = vec_add(cam->pos,
			vec_mult(vec_rotate(vec_create(0, 0, -1), cam->rot), vel));
	if (key == KEY_S)
		cam->pos = vec_add(cam->pos,
			vec_mult(vec_rotate(vec_create(0, 0, -1), cam->rot), -vel));
	re_render(key, param);
	return (0);
}

int	change_camera(int key, void *param)
{
	if (g_rt.curr_cam->next)
		g_rt.curr_cam = g_rt.curr_cam->next;
	else
		g_rt.curr_cam = g_rt.cameras;
	re_render(key, param);
	return (0);
}

int	transform_object(int key, void *param)
{
	t_obj	*obj;
	int		index;

	obj = g_rt.selected_object;
	index = index_of_in_tab(obj->type,
		ft_split(g_rt.g_supported_objects, ';')) - 3;
	g_obj_transformer[index](key, param);
	re_render(key, param);
	return (0);
}

int	edit_lights(int key, void *param)
{
	if (g_rt.current_light)
		g_rt.current_light = (g_rt.current_light->next ?
			g_rt.current_light->next : g_rt.lights);
	else
		g_rt.current_light = g_rt.lights;
	g_rt.selected_object = ((t_obj *)g_rt.current_light ?
		(t_obj *)g_rt.current_light->content : NULL);
	return (re_render(key, param));
}

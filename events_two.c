/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_two.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youkhart <youkhart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/25 22:21:31 by youkhart          #+#    #+#             */
/*   Updated: 2020/01/24 18:36:37 by youkhart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

extern struct s_minirt	g_rt;

int	select_obj(int button, int x, int y, void *param)
{
	t_cam			*cam;
	t_ray			ray;
	t_intersection	*closest;
	t_obj			*tmp;

	(void)param;
	cam = (t_cam *)((t_obj *)g_rt.curr_cam->content)->details;
	ray = cast_ray(x, y, cam, -1);
	closest = get_closest_intersection(g_rt.objects, ray);
	tmp = (closest ? closest->obj : NULL);
	if (button == 1 && g_rt.selected_object != tmp)
	{
		g_rt.selected_object = tmp;
		re_render(0, NULL);
	}
	return (1);
}

int	resize_object(int btn, int x, int y, void *param)
{
	float	ratio;
	char	*type;

	(void)param;
	(void)x;
	(void)y;
	ratio = 0.05;
	type = g_rt.selected_object->type;
	if (!ft_memcmp(type, "sp", max(ft_strlen(type), 2)))
		((t_sphere *)g_rt.selected_object->details)->diameter +=
			(btn == 4 ? -1 : 1) * ratio;
	if (!ft_memcmp(type, "sq", max(ft_strlen(type), 2)))
		((t_square *)g_rt.selected_object->details)->side_size +=
			(btn == 4 ? -1 : 1) * ratio;
	if (!ft_memcmp(type, "cy", max(ft_strlen(type), 2)))
		((t_cylinder *)g_rt.selected_object->details)->height +=
			(btn == 4 ? -1 : 1) * ratio * 2;
	re_render(btn, param);
	return (1);
}

int	move_light_z(int btn, int x, int y, void *param)
{
	float	vel;
	t_light	*light;

	(void)x;
	(void)y;
	vel = 0.05;
	light = (t_light *)(((t_obj *)g_rt.current_light->content)->details);
	light->pos = vec_add(light->pos,
		vec_mult(vec_create(0, 0, 1), (btn == 4 ? -1 : 1) * vel));
	re_render(btn, param);
	return (1);
}

int	add_new_light(int button, int x, int y, void *param)
{
	t_cam			*cam;
	t_ray			ray;
	t_intersection	*closest;
	char			*data;
	char			**vec;

	(void)param;
	cam = (t_cam *)((t_obj *)g_rt.curr_cam->content)->details;
	ray = cast_ray(x, y, cam, -1);
	closest = get_closest_intersection(g_rt.objects, ray);
	if (closest)
	{
		vec = vec_to_ascii(vec_add(closest->point,
			vec_mult(closest->normal, 0.08)));
		data = ft_strjoin_va(7, "l ", vec[0], ",", vec[1],
			",", vec[2], " 0.7 255,255,180");
		add_light(ft_split(data, ' '));
		free(data);
		free_s_tab(vec);
		return (re_render(button, NULL));
	}
	return (1);
}

int	cross_button(int key, void *param)
{
	(void)param;
	(void)key;
	exit_program(0);
	return (0);
}

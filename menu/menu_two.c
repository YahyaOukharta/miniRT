/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_two.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youkhart <youkhart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/26 08:33:37 by youkhart          #+#    #+#             */
/*   Updated: 2020/01/22 21:12:57 by youkhart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "menu.h"

extern struct s_minirt g_rt;

int		put_camera_info(void)
{
	int		i;
	char	**cam_details;

	i = 1;
	mlx_string_put(g_rt.data.mlx_ptr, g_rt.data.mlx_win, g_rt.g_menu.w / 7, 300,
		rgb_to_int("255,255,255"), "Current camera details:");
	cam_details = get_obj_details((t_obj *)g_rt.curr_cam->content);
	while (cam_details[i])
	{
		mlx_string_put(g_rt.data.mlx_ptr, g_rt.data.mlx_win, g_rt.g_menu.w / 4,
			320 + (i - 1) * 20, rgb_to_int("255,255,255"), cam_details[i]);
		i++;
	}
	free_s_tab(cam_details);
	return (1);
}

int		show_menu(void)
{
	char	*light;

	light = (g_rt.current_light ?
		"-> Press L to edit next light" : "-> Press L to edit lights");
	if (g_rt.g_menu.on)
	{
		if (g_rt.current_light)
			print_light_instructions();
		else
			print_cam_obj_instructions();
		put_selected_obj_info();
		put_camera_info();
		mlx_string_put(g_rt.data.mlx_ptr, g_rt.data.mlx_win, g_rt.g_menu.w / 8,
			400, rgb_to_int("255,255,255"), light);
		mlx_string_put(g_rt.data.mlx_ptr, g_rt.data.mlx_win, g_rt.g_menu.w / 8,
			420, rgb_to_int("255,255,255"), "-> Press P to save as bitmap");
		mlx_string_put(g_rt.data.mlx_ptr, g_rt.data.mlx_win, g_rt.g_menu.w / 8,
			440, rgb_to_int("255,255,255"), "-> Press ESC to quit");
	}
	return (1);
}

int		menu_toggle_msg(void)
{
	mlx_string_put(g_rt.data.mlx_ptr, g_rt.data.mlx_win, g_rt.g_res.x - 150,
		g_rt.g_res.y - 22, rgb_to_int("255,255,255"), (g_rt.g_menu.on ?
		"Press M to hide menu" : "Press M to show menu"));
	mlx_string_put(g_rt.data.mlx_ptr, g_rt.data.mlx_win, g_rt.g_res.x - 150,
		g_rt.g_res.y - 10, rgb_to_int("255,255,255"), "Press ESC to quit");
	return (1);
}

int		selected_objects_msg(void)
{
	char	*str;
	char	*tmp;

	str = (g_rt.selected_object ? g_rt.selected_object->type : "(null)");
	if (g_rt.selected_object && !ft_memcmp(g_rt.selected_object->type,
		"l", max(ft_strlen(g_rt.selected_object->type), 1)))
	{
		tmp = ft_itoa(ft_lstsize(g_rt.lights) -
			ft_lstsize(g_rt.current_light) + 1);
		str = ft_strjoin("Selected light = L", tmp);
		free(tmp);
	}
	else
		str = ft_strjoin("Selected object = ", str);
	mlx_string_put(g_rt.data.mlx_ptr, g_rt.data.mlx_win, g_rt.g_res.x - 180,
		34, rgb_to_int("255,255,255"), str);
	free(str);
	tmp = ft_itoa(ft_lstsize(g_rt.cameras) - ft_lstsize(g_rt.curr_cam) + 1);
	str = ft_strjoin("Current camera  = C", tmp);
	mlx_string_put(g_rt.data.mlx_ptr, g_rt.data.mlx_win, g_rt.g_res.x - 180,
		20, rgb_to_int("255,255,255"), str);
	free(str);
	free(tmp);
	return (1);
}

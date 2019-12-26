/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youkhart <youkhart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/26 08:33:20 by youkhart          #+#    #+#             */
/*   Updated: 2019/12/26 08:33:21 by youkhart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "menu.h"

extern struct s_minirt g_rt;

int		print_cam_obj_instructions(void)
{
	char	*title;
	int		i;

	title = "// Instructions //";
	i = 0;
	if (g_rt.g_menu.on)
	{
		mlx_string_put(g_rt.data.mlx_ptr, g_rt.data.mlx_win,
		g_rt.g_menu.w / 2 - ft_strlen(title) * FONT_WIDTH / 3,
		40, rgb_to_int("255,255,255"), title);
		mlx_string_put(g_rt.data.mlx_ptr, g_rt.data.mlx_win, g_rt.g_menu.w / 8,
		90, rgb_to_int("255,255,255"), (g_rt.selected_object ?
			"-> Press C to unselect object" : "-> Press C to change camera"));
		mlx_string_put(g_rt.data.mlx_ptr, g_rt.data.mlx_win, g_rt.g_menu.w / 8,
		110, rgb_to_int("255,255,255"), ft_strjoin("-> Press WASD to move ",
			(g_rt.selected_object ? "object" : "camera")));
		mlx_string_put(g_rt.data.mlx_ptr, g_rt.data.mlx_win, g_rt.g_menu.w / 8,
		130, rgb_to_int("255,255,255"),
			ft_strjoin("-> Press Arrow keys to rotate ",
				(g_rt.selected_object ? "object" : "camera")));
		mlx_string_put(g_rt.data.mlx_ptr, g_rt.data.mlx_win, g_rt.g_menu.w / 8,
		150, rgb_to_int("255,255,255"), (g_rt.selected_object ?
			"-> Scroll mouse to resize object" : ""));
	}
	return (0);
}

int		print_light_instructions(void)
{
	int	i;

	i = 0;
	if (g_rt.g_menu.on)
	{
		mlx_string_put(g_rt.data.mlx_ptr, g_rt.data.mlx_win,
		g_rt.g_menu.w / 2 - ft_strlen("// Instructions //") * FONT_WIDTH / 3,
		40, rgb_to_int("255,255,255"), "// Instructions //");
		mlx_string_put(g_rt.data.mlx_ptr, g_rt.data.mlx_win, g_rt.g_menu.w / 8,
		90, rgb_to_int("255,255,255"), "-> Press C to exit light edit mode");
		mlx_string_put(g_rt.data.mlx_ptr, g_rt.data.mlx_win, g_rt.g_menu.w / 8,
		110, rgb_to_int("255,255,255"), "-> Press WASD to move light");
		mlx_string_put(g_rt.data.mlx_ptr, g_rt.data.mlx_win, g_rt.g_menu.w / 8,
		130, rgb_to_int("255,255,255"), "-> Scroll to move light along Z axis");
		mlx_string_put(g_rt.data.mlx_ptr, g_rt.data.mlx_win, g_rt.g_menu.w / 8,
			150, rgb_to_int("255,255,255"), "-> Click on objects to add light");
	}
	return (0);
}

int		put_selected_obj_info(void)
{
	int		i;
	char	**obj_details;
	char	*obj_select;

	obj_select = (g_rt.selected_object ?
		"Selected object details: " : "Click to select object from scene");
	mlx_string_put(g_rt.data.mlx_ptr, g_rt.data.mlx_win, g_rt.g_menu.w / 7,
		180, rgb_to_int("255,255,255"), obj_select);
	if (g_rt.selected_object)
	{
		obj_details = get_obj_details(g_rt.selected_object);
		while (obj_details[i])
		{
			mlx_string_put(g_rt.data.mlx_ptr, g_rt.data.mlx_win,
				g_rt.g_menu.w / 4, 200 + i * 20, rgb_to_int("255,255,255"),
				obj_details[i]);
			i++;
		}
		free_s_tab(obj_details);
	}
	return (1);
}

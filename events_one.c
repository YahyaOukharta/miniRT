/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_one.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youkhart <youkhart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/25 22:23:24 by youkhart          #+#    #+#             */
/*   Updated: 2019/12/25 22:56:24 by youkhart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <time.h>
#include "save_bmp/bmp.h"

extern struct s_minirt	g_rt;
extern int				g_saving;

int	re_render(int key, void *param)
{
	clock_t t[2];

	mlx_clear_window(g_rt.data.mlx_ptr, g_rt.data.mlx_win);
	t[0] = clock();
	render(0, 0, g_rt.g_res.x, g_rt.g_res.y);
	t[1] = clock();
	ft_printf("Rendering time (s) : %s\n",
		ft_ftoa((double)(t[1] - t[0]) / (double)CLOCKS_PER_SEC, 3));
	return (1);
}

int	toggle_menu(int key, void *param)
{
	g_rt.g_menu.on = !g_rt.g_menu.on;
	re_render(key, NULL);
	return (0);
}

int	save_frame(int key, void *param)
{
	clock_t t[2];

	ft_printf(" [~] Saving...\n");
	g_saving = 1;
	t[0] = clock();
	render(0, 0, g_rt.g_res.x, g_rt.g_res.y);
	t[1] = clock();
	save_bmp("img.bmp", g_rt.g_res.x, g_rt.g_res.y,
			(int *)g_rt.data.img_data);
	ft_printf(" [+] Saved frame\n");
	ft_printf("Rendering time (s) : %s\n",
		ft_ftoa((double)(t[1] - t[0]) / (double)CLOCKS_PER_SEC, 3));
	return (0);
}

int	handle_keys(int key, void *param)
{
	if (key == KEY_RIGHT || key == KEY_LEFT || key == KEY_UP || key == KEY_DOWN)
		return ((g_rt.selected_object ?
			transform_object(key, param) : rotate_camera(key, param)));
	else if (key == KEY_D || key == KEY_A || key == KEY_W || key == KEY_S)
		return ((g_rt.selected_object ?
			transform_object(key, param) : move_camera(key, param)));
	else if (key == KEY_C)
		return (g_rt.selected_object ?
			((g_rt.selected_object = NULL)
				|| (g_rt.current_light = NULL)
				|| re_render(key, param))
				: change_camera(key, param));
	else if (key == KEY_M)
		return (toggle_menu(key, param));
	else if (key == KEY_L)
		return (edit_lights(key, param));
	else if (key == KEY_P)
		return (save_frame(key, param));
	else if (key == KEY_ESC)
		return (exit_program());
	return (0);
}

int	handle_mouse(int button, int x, int y, void *param)
{
	if (button == 1 && y >= 0)
		return ((g_rt.current_light ?
			add_new_light(button, x, y, param)
			: select_obj(button, x, y, param)));
	else if ((button == 4 || button == 5) && y >= 0)
		return ((g_rt.current_light ?
			move_light_z(button, x, y, param)
			: (g_rt.selected_object
			&& resize_object(button, x, y, param))));
	else
		return (0);
}

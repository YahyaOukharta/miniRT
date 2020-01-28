/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youkhart <youkhart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/16 21:37:07 by youkhart          #+#    #+#             */
/*   Updated: 2020/01/28 04:06:59 by youkhart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

struct s_minirt g_rt;
int				g_saving;

int		exit_program(int argc)
{
	ft_lstclear(&(g_rt.objects), free_object);
	mlx_destroy_image(g_rt.data.mlx_ptr, g_rt.data.img_ptr);
	if (argc != 3)
		mlx_destroy_window(g_rt.data.mlx_ptr, g_rt.data.mlx_win);
	exit(0);
	return (0);
}

void	init_objs(void)
{
	g_rt.g_res.is_set = 0;
	g_rt.g_ambient_light.is_set = 0;
	g_rt.g_supported_objects = "R;A;c;l;sp;pl;sq;cy;tr";
	init_obj_constructor();
}

int		init_minirt(int argc)
{
	g_rt.curr_cam = g_rt.cameras;
	if (!(g_rt.data.mlx_ptr = mlx_init()))
		return (EXIT_FAILURE);
	if (argc != 3)
		if (!(g_rt.data.mlx_win = mlx_new_window(g_rt.data.mlx_ptr,
			g_rt.g_res.x, g_rt.g_res.y, "miniRT")))
			return (EXIT_FAILURE);
	g_rt.data.img_ptr = mlx_new_image(g_rt.data.mlx_ptr,
		g_rt.g_res.x, g_rt.g_res.y);
	g_rt.data.img_data = (int *)mlx_get_data_addr(g_rt.data.img_ptr,
		&(g_rt.data.bpp),
		&(g_rt.data.size_line),
		&(g_rt.data.endian));
	g_rt.skybox.img_ptr = mlx_xpm_file_to_image(g_rt.data.mlx_ptr,
		"./skybox.xpm", &(g_rt.skybox.width), &(g_rt.skybox.height));
	g_rt.skybox.img_data = (int *)mlx_get_data_addr(g_rt.skybox.img_ptr,
		&(g_rt.skybox.bpp),
		&(g_rt.skybox.size_line),
		&(g_rt.skybox.endian));
	init_menu();
	init_obj_transformer();
	return (1);
}

int		print_argc_error(void)
{
	char *tmp;

	tmp = take_out(ft_strdup("Error\n \
		[!] Wrong numbers of arguments, \
		Enter path for scene file as first argument, \
		and --save as second argument (optional) \
		to save rendered image as .bmp\n"), '\t');
	ft_printf(tmp);
	free(tmp);
	return (0);
}

int		main(int argc, char **argv)
{
	init_objs();
	if (argc < 2 || argc > 3)
		return (print_argc_error());
	if (!process_file(argc, argv))
		return (0);
	init_minirt(argc);
	if (argc == 3)
	{
		save_frame(0, 0);
		exit_program(argc);
		return (EXIT_SUCCESS);
	}
	if (!render(0, 0, g_rt.g_res.x, g_rt.g_res.y))
		return (0);
	mlx_key_hook(g_rt.data.mlx_win, handle_keys, NULL);
	mlx_mouse_hook(g_rt.data.mlx_win, handle_mouse, NULL);
	mlx_hook(g_rt.data.mlx_win, 17, 1L << 0, cross_button, NULL);
	mlx_loop(g_rt.data.mlx_ptr);
	return (EXIT_SUCCESS);
}

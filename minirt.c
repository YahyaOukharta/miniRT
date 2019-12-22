/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youkhart <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/16 21:37:07 by youkhart          #+#    #+#             */
/*   Updated: 2019/11/17 09:10:37 by youkhart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <pthread.h>

struct s_minirt g_rt;
int				g_saving;

void	init_objs(void)
{
	g_rt.g_res.is_set = 0;
	g_rt.g_ambient_light.is_set = 0;
	g_rt.g_supported_objects = "R;A;c;l;sp;pl;sq;cy;tr";
	init_obj_constructor();
}

int		init_minirt(void)
{
	g_rt.curr_cam = g_rt.cameras;
	if (!(g_rt.data.mlx_ptr = mlx_init()))
		return (EXIT_FAILURE);
	if (!(g_rt.data.mlx_win = mlx_new_window(g_rt.data.mlx_ptr,
		g_rt.g_res.x, g_rt.g_res.y, "miniRT")))
		return (EXIT_FAILURE);
	g_rt.data.img_ptr = mlx_new_image(g_rt.data.mlx_ptr,
		g_rt.g_res.x, g_rt.g_res.y);
	g_rt.data.img_data = (int *)mlx_get_data_addr(g_rt.data.img_ptr,
		&(g_rt.data.bpp),
		&(g_rt.data.size_line),
		&(g_rt.data.endian));
	init_menu();
	init_obj_transformer();
	return (1);
}

int		main(int argc, char **argv)
{
	init_objs();
	if (argc < 2 || argc > 3)
		return (ft_printf(take_out(ft_strdup("Error\n \
		[!] Wrong numbers of arguments, \
		Enter path for scene file as first argument, \
		and --save as second argument (optional) \
		to save rendered image as .bmp\n"), '\t')) ? 0 : 0);
	if (!process_file(argc, argv))
		return (0);
	init_minirt();
	if (argc == 3)
		return (save_frame(0, 0));
	if (!render(0, 0, g_rt.g_res.x, g_rt.g_res.y))
		return (0);
	mlx_key_hook(g_rt.data.mlx_win, handle_keys, NULL);
	mlx_mouse_hook(g_rt.data.mlx_win, handle_mouse, NULL);
	mlx_loop(g_rt.data.mlx_ptr);
	ft_lstclear(&(g_rt.objects), free_object);
	ft_printf("[ GOOD ]");
	return (EXIT_SUCCESS);
}

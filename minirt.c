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

struct s_minirt g_minirt;

void	init_objects(void)
{
	g_minirt.g_resolution.is_set = 0;
	g_minirt.g_ambient_light.is_set = 0;
	g_minirt.g_supported_objects = "R;A;c;l;sp;pl;sq;cy;tr";
	init_obj_constructor();
}

int		init_minirt(void)
{
	g_minirt.current_camera = g_minirt.cameras;
	if (!(g_minirt.data.mlx_ptr = mlx_init()))
		return (EXIT_FAILURE);
	if (!(g_minirt.data.mlx_win = mlx_new_window(g_minirt.data.mlx_ptr,
		g_minirt.g_resolution.x, g_minirt.g_resolution.y, "miniRT")))
		return (EXIT_FAILURE);
	g_minirt.data.img_ptr = mlx_new_image(g_minirt.data.mlx_ptr,
		g_minirt.g_resolution.x, g_minirt.g_resolution.y);
	g_minirt.data.img_data = (int *)mlx_get_data_addr(g_minirt.data.img_ptr,
		&(g_minirt.data.bpp),
		&(g_minirt.data.size_line),
		&(g_minirt.data.endian));
	init_menu();
	init_obj_transformer();
	return (1);
}

int		main(int argc, char **argv)
{
	init_objects();
	if (argc < 2 || argc > 3)
		return (ft_printf(take_out("Error\n [!] Wrong numbers of arguments, \
		Enter path for scene file as first argument, \
		and --save as second argument (optional) \
		to save rendered image as .bmp\n", '\t')) ? 0 : 0);
	if (!process_file(argc, argv))
		return (0);
	init_minirt();
	if (argc == 3)
		return (save_frame(0, 0));
	if (!render(0))
		return (0);
	mlx_key_hook(g_minirt.data.mlx_win, handle_keys, NULL);
	mlx_mouse_hook(g_minirt.data.mlx_win, handle_mouse, NULL);
	mlx_loop(g_minirt.data.mlx_ptr);
	ft_lstclear(&(g_minirt.objects), free_object);
	ft_printf("[ GOOD ]");
	return (EXIT_SUCCESS);
}

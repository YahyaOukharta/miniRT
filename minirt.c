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
char	*g_supported_objects = "R;A;c;l;sp;pl;sq;cy;tr";
struct s_ambient_light g_ambient_light;
struct s_resolution g_resolution;
t_list *objects;
t_list *lights;
t_list *cameras;
t_list *current_camera;
t_list *current_light;
struct s_menu g_menu;
data_t        data; // mlx struct 
struct s_object *selected_object;
pthread_mutex_t mutex;

void init_objects(void)
{
    g_resolution.is_set = 0;
    g_ambient_light.is_set = 0;
	init_obj_constructor();
}

int main (int argc, char **argv)
{
	//file processing and scene objects storing
	if (argc < 2 || argc > 3)
		return (ft_printf("Error\n [!] Wrong numbers of arguments, Enter path for scene file as first argument, and --save as second argument (optional) to save rendered image as .bmp\n") ? 0 : 0);
	if (!process_file(argc, argv))
		return (0);
//	print_objects(objects);
//	print_objects(lights); 
//	print_objects(cameras);
	current_camera = cameras;
	init_menu();
	init_obj_transformer();

    if (!(data.mlx_ptr = mlx_init()))
        return (EXIT_FAILURE);
    if (!(data.mlx_win = mlx_new_window(data.mlx_ptr, g_resolution.x, g_resolution.y, "miniRT")))
        return (EXIT_FAILURE);

	data.img_ptr = mlx_new_image(data.mlx_ptr, g_resolution.x, g_resolution.y);
	data.img_data = (int *)mlx_get_data_addr(data.img_ptr,&data.bpp, &data.size_line, &data.endian);
	// RENDER HERE
	if (argc == 3) //save if the save option is on
		return (save_frame(0,0));
	if(!render(data,objects,lights,current_camera,0))
		return (0);

	mlx_key_hook(data.mlx_win, handle_keys, NULL);
	mlx_mouse_hook(data.mlx_win,handle_mouse,NULL);
	mlx_loop(data.mlx_ptr);

	ft_lstclear(&objects,free_object);
	ft_printf("[ GOOD ]");
    return (EXIT_SUCCESS);
}
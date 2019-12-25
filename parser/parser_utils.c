/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youkhart <youkhart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/25 21:59:27 by youkhart          #+#    #+#             */
/*   Updated: 2019/12/25 21:59:28 by youkhart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

extern struct s_minirt g_rt;

int		open_file(int ac, char **av)
{
	int		fd;
	char	**tab;

	tab = ft_split(av[1], '.');
	if (tab_len(tab) != 2 || ft_memcmp(tab[1], "rt", max(ft_strlen(tab[1]), 2)))
	{
		ft_printf("Error\n [!] Wrong argument format, must be *.rt\n");
		free_s_tab(tab);
		return (0);
	}
	free_s_tab(tab);
	if (ac == 3 && ft_memcmp(av[2], "--save", max(ft_strlen(av[2]), 6)))
	{
		ft_printf("Error\n [!] Wrong option '%s', \
use --save to save rendered image as .bmp\n", av[2]);
		return (0);
	}
	fd = open(av[1], O_RDONLY);
	if (fd < 0)
	{
		ft_printf("Error\n [!] Error opening the file '%s', \
it probably doesnt exit\n", av[1]);
		return (0);
	}
	return (fd);
}

int		check_element_details(char **tab, int n)
{
	int		index;
	char	**tmp;

	if (!exists_in_tab(tab[0], (tmp = ft_split(g_rt.g_supported_objects, ';'))))
	{
		ft_printf("Error\nWrong object identifier '%s'\n", tab[0]);
		free_s_tab(tmp);
		return (0);
	}
	else
	{
		index = index_of_in_tab(tab[0], tmp);
		free_s_tab(tmp);
		return (g_file_checker[index](tab, n));
	}
	return (1);
}

void	init_file_checker(void)
{
	g_file_checker[0] = check_info_resolution;
	g_file_checker[1] = check_info_ambient_light;
	g_file_checker[2] = check_info_camera;
	g_file_checker[3] = check_info_light;
	g_file_checker[4] = check_info_sphere;
	g_file_checker[5] = check_info_plane;
	g_file_checker[6] = check_info_square;
	g_file_checker[7] = check_info_cylinder;
	g_file_checker[8] = check_info_triangle;
}

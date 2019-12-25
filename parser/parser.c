/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youkhart <youkhart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/25 21:58:40 by youkhart          #+#    #+#             */
/*   Updated: 2019/12/25 21:58:44 by youkhart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

extern struct s_minirt g_rt;

static int		store_element(char **tab)
{
	int		index;
	char	**tmp;

	tmp = ft_split(g_rt.g_supported_objects, ';');
	index = index_of_in_tab(tab[0], tmp);
	free_s_tab(tmp);
	return (g_obj_constructor[index](tab));
}

static int		process_line(char *line, int n)
{
	char	**tab;

	if (ft_strlen(line))
	{
		tab = ft_split(line, ' ');
		if (!check_element_details(tab, n))
		{
			free_s_tab(tab);
			free(line);
			ft_lstclear(&g_rt.objects, free_object);
			return (0);
		}
		if (!store_element(tab))
		{
			free_s_tab(tab);
			free(line);
			return (0);
		}
		free_s_tab(tab);
	}
	return (1);
}

int				process_file(int ac, char **av)
{
	int		n;
	char	*line;
	char	**tab;
	int		fd;

	if (!(fd = open_file(ac, av)))
		return (0);
	n = 1;
	init_file_checker();
	init_objs();
	while (get_next_line(fd, &line))
	{
		if (!(process_line(line, n)))
			return (0);
		n++;
		free(line);
	}
	free(line);
	return (1);
}

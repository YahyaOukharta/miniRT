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

char	*g_supported_objects = "R;A;c;l;sp;pl;sq;cy;tr";
struct s_ambient_light g_ambient_light;
struct s_resolution g_resolution;
t_list *objects;

void init_objects(void)
{
    g_resolution.is_set = 0;
    g_ambient_light.is_set = 0;
	init_obj_constructor();
}

int check_element_details(char **tab, int n)
{
//	ft_printf("details of object %d : \n", n);
	int index;
	char **tmp;

	if (!exists_in_tab(tab[0], (tmp = ft_split(g_supported_objects,';'))))
	{
		ft_printf("Error\nWrong object identifier '%s'\n",tab[0]);
		free_s_tab(tmp);
		return (0);
	}else
	{
		index = index_of_in_tab(tab[0], tmp);
		free_s_tab(tmp);
		return (g_file_checker[index](tab, n));
	}
	//ft_printf("Object identifier :  '%s'  [ OK ]\n",tab[0]);
	return (1);
}

int store_element(char **tab)
{
	int index;
	char **tmp;

	tmp = ft_split(g_supported_objects, ';');
	index = index_of_in_tab(tab[0], tmp);
	free_s_tab(tmp);
	return (g_obj_constructor[index](tab));
}

int process_file(int fd)
{
	int		n;
	char	*line;
	char	**tab;

	n = 1;
	init_file_checker();
	init_objects();
	while (get_next_line(fd, &line))
	{
		if (ft_strlen(line))
		{
			tab = ft_split(line, ' ');
			if (!check_element_details(tab , n))
			{
				free_s_tab(tab);
				free(line);
				print_objects(objects);
				ft_lstclear(&objects,free_object);
				return(0);
			}
			if(!store_element(tab)) //treat malloc error cases 
			{	


				free_s_tab(tab);
				//free(line);
				return(0);
			}
			ft_printf("Stored element '%s' succefully!\n", tab[0]);
			free_s_tab(tab);
		}
		n++;
		free(line);
	}
	free(line);
	return (1);
}

int main (int argc, char **argv)
{
	char **tab;
	int fd;
	int n_lines;

	if (argc != 2)
	{
		ft_printf("Error\n [!] Wrong numbers of arguments, Enter only one argument\n");
		return (0);
	}		
	tab = ft_split(argv[1], '.');
	if (tab_len(tab) != 2 || ft_memcmp(tab[1], "rt", max(ft_strlen(tab[1]),2)))
	{
		ft_printf("Error\n [!] Wrong argument format, must be *.rt\n");
		free_s_tab(tab);
		return(0);
	}
	free_s_tab(tab);
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
	{
		ft_printf("Error\n [!] Error opening the file '%s', it probably doesnt exit\n", argv[1]);
		return (0);
	}
	if(!process_file(fd))
		return (0);
	if (g_resolution.is_set)
		ft_printf("resolution = %dx%d\t\t", g_resolution.x,g_resolution.y);
	if (g_ambient_light.is_set)
		printf("Ambient light =%.2f, %d\n\n", g_ambient_light.brightness, g_ambient_light.color);
	//ft_printf("num of objects %d\n",ft_lstsize(objects));
	print_objects(objects);

	//ft_lstclear(&objects,free_object);
	ft_printf("[ GOOD ]");
	return (0);
}

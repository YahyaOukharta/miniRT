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

char		*g_supported_objects = "R;A;c;l;sp;pl;sq;cy;tr";

int	print_file_content(int fd)
{
	int n;
	char *line;

	n = 0;
	while (get_next_line(fd, &line))
	{
		if (ft_strlen(line) > 0)
		{
			ft_printf("%s\n",line);
			free (line);
			n++;
		}
	}
	if (ft_strlen(line) > 0)
	{
		ft_printf("%s\n",line);
		free (line);
	}
	return (n);
}

int check_element_details(char **tab, int n)
{
//	ft_printf("details of object %d : \n", n);
	int index;
	char **tmp;

	if (!exists_in_tab(tab[0], (tmp = ft_split(g_supported_objects,';'))))
	{
		ft_printf("Error\nWrong object identifier '%s'\n",tab[0]);
		return (0);
	}else
	{
		index = index_of_in_tab(tab[0], tmp);
		return (g_file_checker[index](tab, n));
	}
	//ft_printf("Object identifier :  '%s'  [ OK ]\n",tab[0]);
	return (1);
}

int process_file(int fd)
{
	int n;
	char *line;
	char **tab;

	n = 1;
	init_file_checker();
	while (get_next_line(fd, &line))
	{
		if (ft_strlen(line))
		{
			tab = ft_split(line, ' ');
			if (!check_element_details(tab , n))
			{	
				return (0);
		//		store_element(tab);
			}	
		}
		n++;
	}
	return (1);
}

int main (int argc, char **argv)
{
	char **tab;
	int fd;
	int n_lines;


	if (argc != 2)
	{
		ft_printf("Error\nWrong numbers of arguments, Enter only one argument\n");
		return (0);
	}		
	tab = ft_split(argv[1], '.');
	if (tab_len(tab) != 2 || ft_memcmp(tab[1], "rt", ft_strlen(tab[1])))
	{
		ft_printf("Error\nWrong argument format, must be *.rt\n");
		return(0);
	}
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
	{
		ft_printf("Error\nError opening the file '%s', it probably doesnt exit\n", argv[1]);
		return (0);
	}

	if(!process_file(fd))
		return (0);

	//n_lines = print_file_content(fd);		
	//printf("n_lines = %d\ngood !\n",n_lines);
	printf("[ GOOD ]");
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youkhart <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/16 21:37:07 by youkhart          #+#    #+#             */
/*   Updated: 2019/11/17 02:30:26 by youkhart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include "gnl/get_next_line.h"
#include "ft_printf/ft_printf.h"
#include "objects.h"
int tab_len(char **tab)
{
	int i;
	
	i = 0;
	while (tab[i])
		i++;
	return (i);
}

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
	n_lines = print_file_content(fd);	
	n_lines = print_file_content(fd);	
	printf("n_lines = %d\ngood !\n",n_lines);
	return (0);
}

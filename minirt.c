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

int store_element(char **tab)
{
	int index;

	index = index_of_in_tab(tab[0], ft_split(g_supported_objects, ';'));
	return (g_obj_constructor[index](tab));
}

int process_file(int fd)
{
	int n;
	char *line;
	char **tab;

	n = 1;
	init_file_checker();
	init_objects();
	while (get_next_line(fd, &line))
	{
		if (ft_strlen(line))
		{
			tab = ft_split(line, ' ');
			if (!check_element_details(tab , n))
				return (0);
			if(!store_element(tab))
				return (0);
			ft_printf("Stored element '%s' succefully!\n", tab[0]);
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
		ft_printf("Error\n [!] Wrong numbers of arguments, Enter only one argument\n");
		return (0);
	}		
	tab = ft_split(argv[1], '.');
	if (tab_len(tab) != 2 || ft_memcmp(tab[1], "rt", ft_strlen(tab[1])))
	{
		ft_printf("Error\n [!] Wrong argument format, must be *.rt\n");
		return(0);
	}
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
	{
		ft_printf("Error\n [!] Error opening the file '%s', it probably doesnt exit\n", argv[1]);
		return (0);
	}
	if(!process_file(fd))
		return (0);
	if (g_resolution.is_set)
		ft_printf("resolution = %dx%d\n", g_resolution.x,g_resolution.y);
	if (g_ambient_light.is_set)
		printf("Ambient light =%.2f, %d\n", g_ambient_light.brightness, g_ambient_light.color);
	ft_printf("num of objects %d\n",ft_lstsize(objects));
	print_objects(objects);
	// if(objects)
	// {
	// 	t_camera *cam = (t_camera *)(((t_object *)objects->content)->details);
	// 	printf("camera pos %.2f %.2f %.2f fov %d\n",cam->pos.x,cam->pos.y,cam->pos.z,cam->fov);
	// 	objects = objects->next;
	// }
	// if(objects)
	// {
	// 	t_light *light = (t_light *)(((t_object *)objects->content)->details);
	// 	printf("light pos %.2f %.2f %.2f brightness %.2f color %d\n",light->pos.x,light->pos.y,light->pos.z, light->brightness, light->color);
	// 	objects = objects->next;
	// }
	// if(objects)
	// {
	// 	t_sphere *sphere = (t_sphere *)(((t_object *)objects->content)->details);
	// 	printf("sphere pos %.2f %.2f %.2f diameter %.2f color %d\n",sphere->pos.x,sphere->pos.y,sphere->pos.z, sphere->diameter, sphere->color);
	// 	objects = objects->next;
	// }
	// if(objects)
	// {
	// 	t_plane *plane = (t_plane *)(((t_object *)objects->content)->details);
	// 	printf("plane pos %.2f %.2f %.2f color %d\n",plane->pos.x,plane->pos.y,plane->pos.z, plane->color);
	// 	objects = objects->next;
	// }
	// if(objects)
	// {
	// 	t_square *square = (t_square *)(((t_object *)objects->content)->details);
	// 	printf("square pos %.2f %.2f %.2f side_size %.2f color %d\n",square->pos.x,square->pos.y,square->pos.z, square->side_size,square->color);
	// 	objects = objects->next;
	// }
	// if(objects)
	// {
	// 	t_cylinder *cylinder = (t_cylinder *)(((t_object *)objects->content)->details);
	// 	printf("cylinder pos %.2f %.2f %.2f diameter %.2f height %.2f color %d\n",cylinder->pos.x,cylinder->pos.y,cylinder->pos.z, cylinder->diameter,cylinder->height,cylinder->color);
	// 	objects = objects->next;
	// }
	// if(objects)
	// {
	// 	t_triangle *triangle = (t_triangle *)(((t_object *)objects->content)->details);
	// 	printf("triangle p1 %.2f %.2f %.2f p2 %.2f %.2f %.2f p3 %.2f %.2f %.2f color %d\n",triangle->p1.x,triangle->p1.y,triangle->p1.z, triangle->p2.x,triangle->p2.y,triangle->p2.z,triangle->p3.x,triangle->p3.y,triangle->p3.z,triangle->color);
	// 	objects = objects->next;
	// }
	ft_printf("[ GOOD ]");
	return (0);
}

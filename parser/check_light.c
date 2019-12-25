/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_light.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youkhart <youkhart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/25 21:59:11 by youkhart          #+#    #+#             */
/*   Updated: 2019/12/25 21:59:12 by youkhart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

extern struct s_minirt g_rt;

static int		check_light1(char **tab, int n)
{
	if (tab_len(tab) != 4)
	{
		ft_printf("Error in line %d:\n [!]\
	Incorrect number of arguments for light, \
correct format 'l -40,0,30 0.7 255,255,255'\n", n);
		return (0);
	}
	if (!is_pos_vector(tab[1]))
	{
		ft_printf("Error in line %d:\n\
	[!] Incorrect position vector, should be in format '-50,0,20'\n", n);
		return (0);
	}
	return (1);
}

static int		check_light2(char **tab, int n)
{
	if (!is_float(tab[2]) || ft_atof(tab[2]) < 0 || ft_atof(tab[2]) > 1)
	{
		ft_printf("Error in line %d:\n\
	[!] Incorrect value for brightness, should be float in range \
[0.0 , 1.0]\n", n);
		return (0);
	}
	if (!is_color(tab[3]))
	{
		ft_printf("Error in line %d:\n\
	[!] Incorrect color, should be RGB colors in range \
[0 , 255] in this format '255,255,255'\n", n);
		return (0);
	}
	return (1);
}

int				check_info_light(char **tab, int n)
{
	if (!check_light1(tab, n) || !check_light2(tab, n))
		return (0);
	return (1);
}

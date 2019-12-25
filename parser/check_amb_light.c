/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_amb_light.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youkhart <youkhart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/25 21:58:57 by youkhart          #+#    #+#             */
/*   Updated: 2019/12/25 21:59:00 by youkhart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

extern struct s_minirt g_rt;

static int		check_res1(char **tab, int n)
{
	if (g_rt.g_ambient_light.is_set)
	{
		ft_printf("Error in line %d:\n\
	[!] Ambient lightning can only be defined once\n", n);
		return (0);
	}
	if (tab_len(tab) != 3)
	{
		ft_printf("Error in line %d:\n\
	[!] Incorrect number of arguments for ambient lightning, \
correct format 'A 0.2 255,255,255'\n", n);
		return (0);
	}
	return (1);
}

static int		check_res2(char **tab, int n)
{
	if (!is_float(tab[1]) || ft_atof(tab[1]) < 0 || ft_atof(tab[1]) > 1)
	{
		ft_printf("Error in line %d:\n\
	[!] Incorrect value for brightness, \
should be float in range [0.0 , 1.0]\n", n);
		return (0);
	}
	if (!is_color(tab[2]))
	{
		ft_printf("Error in line %d:\n\
	[!] Incorrect color, should be RGB colors in range \
[0 , 255] in this format '255,255,255'\n", n);
		return (0);
	}
	return (1);
}

int				check_info_ambient_light(char **tab, int n)
{
	if (!check_res1(tab, n) || !check_res2(tab, n))
		return (0);
	return (1);
}

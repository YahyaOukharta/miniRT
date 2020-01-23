/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_res.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youkhart <youkhart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/25 21:59:16 by youkhart          #+#    #+#             */
/*   Updated: 2020/01/23 18:03:42 by youkhart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

extern struct s_minirt g_rt;

static int		check_res1(char **tab, int n)
{
	if (g_rt.g_res.is_set)
	{
		ft_printf("Error in line %d:\n\
	[!] Resolution can only be defined once\n", n);
		return (0);
	}
	if (tab_len(tab) != 3)
	{
		ft_printf("Error in line %d:\n\
	[!] Incorrect number of arguments for resolution, \
correct format 'R 1920 1080'\n", n);
		return (0);
	}
	return (1);
}

static int		check_res2(char **tab, int n)
{
	if (!is_int(tab[1]) || !is_int(tab[2]))
	{
		ft_printf("Error in line %d:\n\
	[!] Incorrect values for resolution, should be integers\n", n);
		return (0);
	}
	if (ft_atoi(tab[1]) <= 0 || ft_atoi(tab[2]) <= 0)
	{
		ft_printf("Error in line %d:\n\
	[!] Incorrect values for resolution, \
should be non-zero unsigned integers\n", n);
		return (0);
	}
	if (ft_atoi(tab[1]) > MAX_RES_X || ft_atoi(tab[2]) > MAX_RES_Y)
	{
		ft_printf("Error in line %d:\n\
	[!] Incorrect values for resolution, \
shouldn't be greater than (%d, %d)\n", n, MAX_RES_X, MAX_RES_Y);
		return (0);
	}
	return (1);
}

int				check_info_resolution(char **tab, int n)
{
	if (!check_res1(tab, n) || !check_res2(tab, n))
		return (0);
	return (1);
}

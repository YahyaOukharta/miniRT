/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cam.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youkhart <youkhart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/25 21:59:04 by youkhart          #+#    #+#             */
/*   Updated: 2019/12/25 21:59:05 by youkhart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

extern struct s_minirt g_rt;

static int		check_cam1(char **tab, int n)
{
	if (tab_len(tab) != 4)
	{
		ft_printf("Error in line %d:\n\
	[!] Incorrect number of arguments for camera, \
correct format 'c -50,0,20 0,0,0 70'\n", n);
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

static int		check_cam2(char **tab, int n)
{
	if (!is_norm_dir_vector(tab[2]))
	{
		ft_printf("Error in line %d:\n\
	[!] Incorrect normalized orientation vector, should be values in range \
[-1.0 , 1.0] in format '-0.1,0.0,0.8'\n", n);
		return (0);
	}
	if (!is_int(tab[3]) || ft_atoi(tab[3]) < 0 || ft_atoi(tab[3]) > 180)
	{
		ft_printf("Error in line %d:\n\
	[!] Incorrect field of view, should be in range [0, 180]\n", n);
		return (0);
	}
	return (1);
}

int				check_info_camera(char **tab, int n)
{
	if (!check_cam1(tab, n) || !check_cam2(tab, n))
		return (0);
	return (1);
}

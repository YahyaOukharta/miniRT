/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_plane.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youkhart <youkhart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/25 21:59:13 by youkhart          #+#    #+#             */
/*   Updated: 2019/12/25 21:59:14 by youkhart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

extern struct s_minirt g_rt;

static int		check_plane1(char **tab, int n)
{
	if (tab_len(tab) != 4)
	{
		ft_printf("Error in line %d:\n\
	[!] Incorrect number of arguments for plane, \
correct format 'pl 0.0,0.0,-10.0 0.0,1.0,0.0 0,0,225'\n", n);
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

static int		check_plane2(char **tab, int n)
{
	if (!is_norm_dir_vector(tab[2]))
	{
		ft_printf("Error in line %d:\n\
	[!] Incorrect normalized orientation vector, \
should be values in range [-1.0 , 1.0] in format '-0.1,0.0,0.8'\n", n);
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

int				check_info_plane(char **tab, int n)
{
	if (!check_plane1(tab, n) || !check_plane2(tab, n))
		return (0);
	return (1);
}

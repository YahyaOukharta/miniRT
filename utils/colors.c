/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youkhart <youkhart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/25 23:10:32 by youkhart          #+#    #+#             */
/*   Updated: 2019/12/25 23:21:22 by youkhart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

int		is_color(char *str)
{
	char	**tab;
	int		i;

	i = 0;
	if (how_many_in(',', str) != 2)
		return (0);
	tab = ft_split(str, ',');
	if (tab_len(tab) != 3)
	{
		free_s_tab(tab);
		return (0);
	}
	while (tab[i])
	{
		if (!is_int(tab[i]) || ft_atoi(tab[i]) < 0 || ft_atoi(tab[i]) > 255)
		{
			free_s_tab(tab);
			return (0);
		}
		i++;
	}
	free_s_tab(tab);
	return (1);
}

int		add_colors(int col1, int col2)
{
	unsigned char	c1[3];
	unsigned char	c2[3];
	unsigned char	c3[3];
	int				result;

	c1[2] = col1 % 256;
	col1 /= 256;
	c1[1] = col1 % 256;
	col1 /= 256;
	c1[0] = col1 % 256;
	c2[2] = col2 % 256;
	col2 /= 256;
	c2[1] = col2 % 256;
	col2 /= 256;
	c2[0] = col2 % 256;
	c3[0] = min((c1[0] + c2[0]), 255);
	c3[1] = min((c1[1] + c2[1]), 255);
	c3[2] = min((c1[2] + c2[2]), 255);
	result = c3[0] * 256;
	result = (result + c3[1]) * 256;
	result = result + c3[2];
	return (result);
}

int		mult_colors(int col1, float value)
{
	unsigned char	c1[3];
	int				result;

	c1[2] = (col1 % 256) * value;
	col1 /= 256;
	c1[1] = (col1 % 256) * value;
	col1 /= 256;
	c1[0] = (col1 % 256) * value;
	result = c1[0] * 256;
	result = (result + c1[1]) * 256;
	result = result + c1[2];
	return (result);
}

int		rgb_to_int(char *s)
{
	char	**tab;
	char	**tmp;
	int		res;

	tab = ft_split(s, ',');
	tmp = tab;
	res = 0;
	while (*tab)
	{
		res = res * 256 + ft_atoi(*tab);
		free(*tab);
		tab++;
	}
	free(tmp);
	return (res);
}

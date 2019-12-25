/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youkhart <youkhart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/25 23:13:59 by youkhart          #+#    #+#             */
/*   Updated: 2019/12/25 23:14:00 by youkhart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

int		is_int(char *str)
{
	if (*str == '-')
		str++;
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (0);
		str++;
	}
	return (1);
}

int		is_float(char *str)
{
	int f;

	if (!ft_strchr(str, '.'))
		return (is_int(str));
	f = 0;
	if (*str == '-')
		str++;
	while (*str)
	{
		if (!ft_isdigit(*str))
		{
			if (*str == '.' && !f)
				f = 1;
			else
				return (0);
		}
		str++;
	}
	return (1);
}

int		how_many_in(char c, char *str)
{
	int		i;

	i = 0;
	while (*str)
	{
		if (*str == c)
			i++;
		str++;
	}
	return (i);
}

int		is_pos_vector(char *str)
{
	char	**tab;
	int		i;

	i = 0;
	if (how_many_in(',', str) != 2)
		return (0);
	tab = ft_split(str, ',');
	if (tab_len(tab) != 3)
		return (0);
	while (tab[i])
	{
		if (!is_float(tab[i]))
		{
			free_s_tab(tab);
			return (0);
		}
		i++;
	}
	free_s_tab(tab);
	return (1);
}

int		is_norm_dir_vector(char *str)
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
		if (!is_float(tab[i]) || ft_atof(tab[i]) < -1.0
			|| ft_atof(tab[i]) > 1.0)
		{
			free_s_tab(tab);
			return (0);
		}
		i++;
	}
	free_s_tab(tab);
	return (1);
}

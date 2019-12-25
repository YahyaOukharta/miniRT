/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_array.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youkhart <youkhart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/25 23:12:32 by youkhart          #+#    #+#             */
/*   Updated: 2019/12/25 23:14:34 by youkhart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

int		tab_len(char **tab)
{
	int i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}

int		exists_in_tab(char *s, char **tab)
{
	while (*tab)
	{
		if (!ft_strncmp(s, *tab, max(ft_strlen(s), ft_strlen(*tab))))
			return (1);
		tab++;
	}
	return (0);
}

int		index_of_in_tab(char *s, char **tab)
{
	int i;

	i = 0;
	while (tab[i])
	{
		if (!ft_strncmp(s, tab[i], max(ft_strlen(s), ft_strlen(tab[i]))))
			return (i);
		i++;
	}
	return (-1);
}

int		free_s_tab(char **tab)
{
	int		i;

	i = 0;
	if (tab)
	{
		while (tab[i])
		{
			free(tab[i]);
			i++;
		}
		free(tab);
	}
	return (0);
}

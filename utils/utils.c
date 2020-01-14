/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youkhart <youkhart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/25 23:14:10 by youkhart          #+#    #+#             */
/*   Updated: 2019/12/27 16:07:24 by youkhart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

int		min(int a, int b)
{
	return (a < b ? a : b);
}

int		max(int a, int b)
{
	return (a > b ? a : b);
}

void	free_object(void *object)
{
	t_obj	*obj;
	char	**tmp;
	int		index;

	obj = (t_obj *)object;
	free(obj->details);
	free(obj->type);
	free(obj);
}

void	*free_and_return(void *ptr, void *ret)
{
	free(ptr);
	return (ret);
}

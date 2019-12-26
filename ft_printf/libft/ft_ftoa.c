/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ftoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youkhart <youkhart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/26 16:22:20 by youkhart          #+#    #+#             */
/*   Updated: 2019/12/26 16:22:21 by youkhart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "math.h"

char	*ft_ftoa(float n, size_t precision)
{
	char	*res;
	int		i_part;
	float	f_part;
	char	*sign;

	i_part = (int)n;
	f_part = (float)i_part - (float)n;
	if (i_part < 0)
		i_part *= -1;
	if (f_part < 0)
		f_part *= -1.0;
	if (n < 0)
		sign = ft_strdup("-");
	else
		sign = ft_strdup("");
	res = ft_itoa(i_part);
	if (precision)
		res = ft_strjoin_va(4, sign, res, ".",
		ft_itoa((int)(f_part * pow(10, precision))));
	return (res);
}

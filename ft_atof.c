/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youkhart <youkhart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 15:36:56 by youkhart          #+#    #+#             */
/*   Updated: 2019/12/26 08:46:30 by youkhart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>

static int	count_digits(const char *str)
{
	int i;
	int flag;

	i = 0;
	while (ft_isdigit(*str))
	{
		i++;
		str++;
	}
	if (*str == '.')
		str++;
	else
		return (i);
	while (ft_isdigit(*str))
	{
		i++;
		str++;
	}
	return (i);
}

float		ft_atof(const char *str)
{
	float	res;
	int		sign;
	int		n_digits;
	int		expo;
	int		i;

	i = 0;
	sign = 1;
	res = 0;
	while ((*str > 8 && *str < 14) || *str == 32)
		str++;
	if (*str == '+')
		str++;
	else if (*str == '-')
	{
		sign = -1;
		str++;
	}
	if (!ft_strchr(str, '.'))
		return ((float)(ft_atoi(str) * sign));
	n_digits = count_digits(str);
	while (ft_isdigit(*str))
	{
		res = (res * 10) + *str - '0';
		i++;
		str++;
		if (*str == '.')
		{
			expo = n_digits - i;
			str++;
		}
	}
	if (res * sign > 0 && sign < 0)
		return (0);
	else if (res * sign < 0 && sign > 0)
		return (-1);
	else
		return ((float)(res / (float)pow(10, expo)) * sign);
}

float	ft_set_precision(float n, int prec)
{
	return (floor(pow(10, prec) * n) / pow(10, prec));
}

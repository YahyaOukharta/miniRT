/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skybox.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youkhart <youkhart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 22:04:57 by youkhart          #+#    #+#             */
/*   Updated: 2020/01/21 01:35:52 by youkhart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

extern struct s_minirt	g_rt;

int			get_sky_color(int x, int y)
{
	int			index;
	float		ry;

	ry = ((t_cam *)((t_obj *)g_rt.curr_cam->content)->details)->rot.y;
	index = (int)floor(y * g_rt.skybox.width + x);
	return (mult_colors(g_rt.skybox.img_data[index], 0.3));
}

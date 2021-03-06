/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skybox.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youkhart <youkhart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 22:04:57 by youkhart          #+#    #+#             */
/*   Updated: 2020/01/23 19:47:29 by youkhart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

extern struct s_minirt	g_rt;

int			sky(int x, int y)
{
	int			index;
	float		ry;
	int			sb_x;
	int			sb_y;

	ry = -fmod(((t_cam *)((t_obj *)g_rt.curr_cam->content)->details)->rot.y,
		2 * M_PI) * 0.002;
	sb_x = (int)floor(((float)(x + ry * (float)g_rt.g_res.x) /
		(float)g_rt.g_res.x) * (float)g_rt.skybox.width);
	sb_y = (int)floor(((float)y / (float)g_rt.g_res.y) *
		(float)g_rt.skybox.height);
	if (sb_x < 0)
		sb_x += g_rt.skybox.width;
	if (sb_y < 0)
		sb_y += g_rt.skybox.height;
	index = (int)floor(sb_y * g_rt.skybox.width + sb_x);
	return (mult_colors(g_rt.skybox.img_data[index], 0.4));
}

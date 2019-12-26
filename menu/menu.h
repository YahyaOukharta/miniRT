/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youkhart <youkhart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/26 08:34:09 by youkhart          #+#    #+#             */
/*   Updated: 2019/12/26 08:36:28 by youkhart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MENU_H
# define MENU_H
# include "../minirt.h"
# define PRECISION 2

int		init_menu(void);
int		show_menu(void);
int		put_camera_info(void);
int		menu_toggle_msg(void);
int		print_cam_obj_instructions(void);
int		print_light_instructions(void);
int		put_selected_obj_info(void);
int		selected_objects_msg(void);
char	**get_obj_details(t_obj *obj);
char	**get_cam_details(t_obj *obj);
char	**get_light_details(t_obj *obj);
char	**get_sphere_details(t_obj *obj);
char	**get_plane_details(t_obj *obj);
char	**get_square_details(t_obj *obj);
char	**get_cylinder_details(t_obj *obj);
char	**get_triangle_details(t_obj *obj);
void	init_obj_details(void);

typedef char**(*t_obj_details)(t_obj *);
t_obj_details g_obj_details[8];
#endif

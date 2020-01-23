/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youkhart <youkhart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/25 21:59:32 by youkhart          #+#    #+#             */
/*   Updated: 2020/01/23 18:11:11 by youkhart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H
# include "../minirt.h"
# define MAX_RES_X 2560
# define MAX_RES_Y 1320

int			open_file(int ac, char **av);
int			check_element_details(char **tab, int n);
int			process_file(int ac, char **av);
int			check_info_resolution(char **tab, int n);
int			check_info_ambient_light(char **tab, int n);
int			check_info_camera(char **tab, int n);
int			check_info_light(char **tab, int n);
int			check_info_sphere(char **tab, int n);
int			check_info_plane(char **tab, int n);
int			check_info_square(char **tab, int n);
int			check_info_cylinder(char **tab, int n);
int			check_info_triangle(char **tab, int n);
void		init_file_checker(void);
typedef int(*t_checker)(char **, int);
t_checker g_file_checker[10];
#endif

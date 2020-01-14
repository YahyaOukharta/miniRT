/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youkhart <youkhart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/25 23:15:34 by youkhart          #+#    #+#             */
/*   Updated: 2019/12/27 16:07:38 by youkhart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H
# include "../minirt.h"

int		min(int a, int b);
int		max(int a, int b);
int		is_int(char *s);
int		is_float(char *s);
int		is_color(char *s);
int		is_pos_vector(char *s);
int		is_norm_dir_vector(char *s);
int		tab_len(char **tab);
int		exists_in_tab(char *s, char **tab);
int		index_of_in_tab(char *s, char **tab);
int		how_many_in(char c, char *str);
int		free_s_tab(char **tab);
int		rgb_to_int(char *rgb);
int		add_colors(int c1, int c2);
int		mult_colors(int c1, float value);
void	free_object(void *object);
void    *free_and_return(void *ptr, void *ret);
#endif

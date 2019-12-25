/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youkhart <youkhart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/25 22:03:30 by youkhart          #+#    #+#             */
/*   Updated: 2019/12/25 22:03:31 by youkhart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SAVE_BMP_H
# define SAVE_BMP_H
# include <fcntl.h>

void			little_endian_fill_int(unsigned char *dest, int value);
unsigned char	*bmp_file_header(int filesize);
unsigned char	*bmp_info_header(int w, int h);
int				save_bmp(const char *filename, int w, int h, int *image);

#endif

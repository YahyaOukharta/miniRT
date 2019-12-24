#ifndef SAVE_BMP_H
# define SAVE_BMP_H
# include <fcntl.h>

void			little_endian_fill_int(unsigned char *dest, int value);
unsigned char	*bmp_file_header(int filesize);
unsigned char	*bmp_info_header(int w, int h);
int				save_bmp(const char *filename, int w, int h, int *image);

#endif

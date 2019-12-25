#include "bmp.h"
#include "../ft_printf/ft_printf.h"

void			little_endian_fill_int(unsigned char *dest, int value)
{
	int		i;

	i = 0;
	while (i < 4)
	{
		dest[i] = (unsigned char)(value >> (8 * i));
		i++;
	}
}

unsigned char	*bmp_file_header(int filesize)
{
	unsigned char *f_header;

	f_header = (unsigned char *)ft_calloc(14, sizeof(unsigned char));
	f_header[0] = 'B';
	f_header[1] = 'M';
	little_endian_fill_int(&f_header[2], filesize);
	f_header[10] = 54;
	return (f_header);
}

unsigned char	*bmp_info_header(int w, int h)
{
	unsigned char *i_header;

	i_header = (unsigned char *)ft_calloc(40, sizeof(unsigned char));
	i_header[0] = 40;
	little_endian_fill_int(&i_header[4], w);
	little_endian_fill_int(&i_header[8], h);
	i_header[12] = 1;
	i_header[14] = 24;
	little_endian_fill_int(&i_header[20], 4 * w * h);
	little_endian_fill_int(&i_header[24], 72 * (int)(39.375));
	little_endian_fill_int(&i_header[28], 72 * (int)(39.375));
	return (i_header);
}

int				save_bmp(const char *filename, int w, int h, int *image)
{
	int				fd;
	unsigned char	*header[2];
	int				i;
	unsigned char	color[3];

	if ((fd = open(filename, O_CREAT | O_WRONLY)) < 0)
	{
		ft_printf("Error opening file");
		return (0);
	}
	i = -1;
	header[0] = bmp_file_header(4 * w * h + 54);
	header[1] = bmp_info_header(w, h);
	write(fd, header[0], 14);
	free(header[0]);
	write(fd, header[1], 40);
	free(header[1]);
	while (++i < w * h)
	{
		little_endian_fill_int((unsigned char *)color, image[i]);
		write(fd, color, 3);
	}
	close(fd);
	return (1);
}
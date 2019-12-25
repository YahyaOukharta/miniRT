#include "parser.h"

extern struct s_minirt g_rt;

static int		check_sphere1(char **tab, int n)
{
	if (tab_len(tab) != 4)
	{
		ft_printf("Error in line %d:\n\
	[!] Incorrect number of arguments for sphere, \
correct format 'sp 0.0,0.0,20.6 12.6 10,0,255'\n", n);
		return (0);
	}
	if (!is_pos_vector(tab[1]))
	{
		ft_printf("Error in line %d:\n\
	[!] Incorrect position vector, should be in format '-50,0,20'\n", n);
		return (0);
	}
	return (1);
}

static int		check_sphere2(char **tab, int n)
{
	if (!is_float(tab[2]) || ft_atof(tab[2]) < 0)
	{
		ft_printf("Error in line %d:\n\
	[!] Incorrect value for sphere diameter, should be greater than zero\n", n);
		return (0);
	}
	if (!is_color(tab[3]))
	{
		ft_printf("Error in line %d:\n\
	[!] Incorrect color, should be RGB colors in range \
[0 , 255] in this format '255,255,255'\n", n);
		return (0);
	}
	return (1);
}

int				check_info_sphere(char **tab, int n)
{
	if (!check_sphere1(tab, n) || !check_sphere2(tab, n))
		return (0);
	return (1);
}

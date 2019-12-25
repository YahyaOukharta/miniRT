#include "parser.h"

extern struct s_minirt g_rt;

static int		check_triangle1(char **tab, int n)
{
	if (tab_len(tab) != 5)
	{
		ft_printf("Error in line %d:\n\
	[!] Incorrect number of arguments for triangle, correct format \
'tr 10.0,20.0,10.0 10.0,10.0,20.0 20.0,10.0,10.0 0,0,255'\n", n);
		return (0);
	}
	if (!is_pos_vector(tab[1]))
	{
		ft_printf("Error in line %d:\n\
	[!] Incorrect position vector, should be in format '-50,0,20'\n", n);
		return (0);
	}
	if (!is_pos_vector(tab[2]))
	{
		ft_printf("Error in line %d:\n\
	[!] Incorrect position vector, should be in format '-50,0,20'\n", n);
		return (0);
	}
	return (1);
}

static int		check_triangle2(char **tab, int n)
{
	if (!is_pos_vector(tab[3]))
	{
		ft_printf("Error in line %d:\n\
	[!] Incorrect position vector, should be in format '-50,0,20'\n", n);
		return (0);
	}
	if (!is_color(tab[4]))
	{
		ft_printf("Error in line %d:\n\
	[!] Incorrect color, should be RGB colors in range \
[0 , 255] in this format '255,255,255'\n", n);
		return (0);
	}
	return (1);
}

int				check_info_triangle(char **tab, int n)
{
	if (!check_triangle1(tab, n) || !check_triangle2(tab, n))
		return (0);
	return (1);
}

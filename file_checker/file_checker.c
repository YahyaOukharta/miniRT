#include "file_checker.h"
int check_info_resolution(char **tab)
{
	if (tab_len(tab) != 3)
	{
		ft_printf("Error\nIncorrect number of arguments for resolution, correct format 'R 1920 1080'\n");
		return (0);
	}
	if (!is_int(tab[1]) || !is_int(tab[2]))
	{
		ft_printf("Error\nIncorrect values for resolution, should be integers\n");
		return (0);
	}
	if (ft_atoi(tab[1])<= 0 || ft_atoi(tab[2]) <= 0)
	{
		ft_printf("Error\nIncorrect values for resolution, should be non-zero unsigned integers\n");
		return (0);
	}
	if (ft_atoi(tab[1]) > 1920 || ft_atoi(tab[2]) > 1080)
	{
		ft_printf("Error\nIncorrect values for resolution, shouldn't be greater than (1920, 1080)\n");
		return (0);
	}
	return (1);
}

int check_info_ambient_light(char **tab)
{
	if (tab_len(tab) != 3)
	{
		ft_printf("Error\nIncorrect number of arguments for ambient lightning, correct format 'A 0.2 255,255,255'\n");
		return (0);
	}
	if (!is_float(tab[1]) || ft_atof(tab[1]) < 0 || ft_atof(tab[1]) > 1)
	{
		ft_printf("Error\nIncorrect value for brightness, should be float in range [0.0 , 1.0]\n");
		return (0);
	}
	if (!is_color(tab[2]))
	{
		ft_printf("Error\nIncorrect color, should be RGB colors in range [0 , 255] in this format '255,255,255'\n");
		return (0);
	}
	return (1);
}
int check_info_camera(char **tab)
{
	if (tab_len(tab) != 4)
	{
		ft_printf("Error\nIncorrect number of arguments for camera, correct format 'c -50,0,20 0,0,0 70'\n");
		return (0);
	}
	if (!is_pos_vector(tab[1]))
	{
		ft_printf("Error\nIncorrect position vector, should be in format '-50,0,20'\n");
		return (0);
	}
	if (!is_norm_dir_vector(tab[2]))
	{
		ft_printf("Error\nIncorrect normalized orientation vector, should be values in range [-1.0 , 1.0] in format '-0.1,0.0,0.8'\n");
		return (0);
	}
	if (!is_int(tab[3]) || ft_atoi(tab[3]) < 0 || ft_atoi(tab[3]) > 180)
	{
		ft_printf("Error\nIncorrect field of view, should be in range [0, 180]\n");
		return (0);
	}
	return (1);
}

int check_info_light(char **tab)
{
	if (tab_len(tab) != 4)
	{
		ft_printf("Error\nIncorrect number of arguments for light, correct format 'l -40,0,30 0.7 255,255,255'\n");
		return (0);
	}
	if (!is_pos_vector(tab[1]))
	{
		ft_printf("Error\nIncorrect position vector, should be in format '-50,0,20'\n");
		return (0);
	}
	if (!is_float(tab[2]) || ft_atof(tab[2]) < 0 || ft_atof(tab[2]) > 1)
	{
		ft_printf("Error\nIncorrect value for brightness, should be float in range [0.0 , 1.0]\n");
		return (0);
	}
	if (!is_color(tab[3]))
	{
		ft_printf("Error\nIncorrect color, should be RGB colors in range [0 , 255] in this format '255,255,255'\n");
		return (0);
	}
	return (1);
}

int check_info_sphere(char **tab)
{
	if (tab_len(tab) != 4)
	{
		ft_printf("Error\nIncorrect number of arguments for sphere, correct format 'sp 0.0,0.0,20.6 12.6 10,0,255'\n");
		return (0);
	}
	if (!is_pos_vector(tab[1]))
	{
		ft_printf("Error\nIncorrect position vector, should be in format '-50,0,20'\n");
		return (0);
	}
	if (!is_float(tab[2]) || ft_atof(tab[2]) < 0)
	{
		ft_printf("Error\nIncorrect value for diameter, should be greater than zero\n");
		return (0);
	}
	if (!is_color(tab[3]))
	{
		ft_printf("Error\nIncorrect color, should be RGB colors in range [0 , 255] in this format '255,255,255'\n");
		return (0);
	}
	return (1);
}

int check_info_plane(char **tab)
{
	if (tab_len(tab) != 4)
	{
		ft_printf("Error\nIncorrect number of arguments for plane, correct format 'pl 0.0,0.0,-10.0 0.0,1.0,0.0 0,0,225'\n");
		return (0);
	}
	if (!is_pos_vector(tab[1]))
	{
		ft_printf("Error\nIncorrect position vector, should be in format '-50,0,20'\n");
		return (0);
	}
	if (!is_norm_dir_vector(tab[2]))
	{
		ft_printf("Error\nIncorrect normalized orientation vector, should be values in range [-1.0 , 1.0] in format '-0.1,0.0,0.8'\n");
		return (0);
	}
	if (!is_color(tab[3]))
	{
		ft_printf("Error\nIncorrect color, should be RGB colors in range [0 , 255] in this format '255,255,255'\n");
		return (0);
	}
	return (1);
}

int check_info_square(char **tab)
{
	if (tab_len(tab) != 5)
	{
		ft_printf("Error\nIncorrect number of arguments for square, correct format 'sq 0.0,0.0,20.6 1.0,0.0,0.0 12.6 255,0,255'\n");
		return (0);
	}
	if (!is_pos_vector(tab[1]))
	{
		ft_printf("Error\nIncorrect position vector, should be in format '-50,0,20'\n");
		return (0);
	}
	if (!is_norm_dir_vector(tab[2]))
	{
		ft_printf("Error\nIncorrect normalized orientation vector, should be values in range [-1.0 , 1.0] in format '-0.1,0.0,0.8'\n");
		return (0);
	}
	if (!is_float(tab[3]) || ft_atof(tab[3]) < 0)
	{
		ft_printf("Error\nIncorrect value for square side size, should be greater than zero\n");
		return (0);
	}
	if (!is_color(tab[4]))
	{
		ft_printf("Error\nIncorrect color, should be RGB colors in range [0 , 255] in this format '255,255,255'\n");
		return (0);
	}
	return (1);
}
int check_info_cylinder(char **tab)
{
	if (tab_len(tab) != 6)
	{
		ft_printf("Error\nIncorrect number of arguments for cylinder, correct format 'cy 50.0,0.0,20.6 0.0,0.0,1.0 10,0,255 14.2 21.42'\n");
		return (0);
	}
	if (!is_pos_vector(tab[1]))
	{
		ft_printf("Error\nIncorrect position vector, should be in format '-50,0,20'\n");
		return (0);
	}
	if (!is_norm_dir_vector(tab[2]))
	{
		ft_printf("Error\nIncorrect normalized orientation vector, should be values in range [-1.0 , 1.0] in format '-0.1,0.0,0.8'\n");
		return (0);
	}
	if (!is_color(tab[3]))
	{
		ft_printf("Error\nIncorrect color, should be RGB colors in range [0 , 255] in this format '255,255,255'\n");
		return (0);
	}
	if (!is_float(tab[4]) || ft_atof(tab[4]) < 0)
	{
		ft_printf("Error\nIncorrect value for cylinder diameter, should be greater than zero\n");
		return (0);
	}
	if (!is_float(tab[5]) || ft_atof(tab[5]) < 0)
	{
		ft_printf("Error\nIncorrect value for cylinder height, should be greater than zero\n");
		return (0);
	}
	return (1);
}
int check_info_triangle(char **tab)
{
	if (tab_len(tab) != 5)
	{
		ft_printf("Error\nIncorrect number of arguments for triangle, correct format 'tr 10.0,20.0,10.0 10.0,10.0,20.0 20.0,10.0,10.0 0,0,255'\n");
		return (0);
	}
	if (!is_pos_vector(tab[1]))
	{
		ft_printf("Error\nIncorrect position vector, should be in format '-50,0,20'\n");
		return (0);
	}
	if (!is_pos_vector(tab[2]))
	{
		ft_printf("Error\nIncorrect position vector, should be in format '-50,0,20'\n");
		return (0);
	}
	if (!is_pos_vector(tab[3]))
	{
		ft_printf("Error\nIncorrect position vector, should be in format '-50,0,20'\n");
		return (0);
	}
	if (!is_color(tab[4]))
	{
		ft_printf("Error\nIncorrect color, should be RGB colors in range [0 , 255] in this format '255,255,255'\n");
		return (0);
	}
	
	return (1);
}
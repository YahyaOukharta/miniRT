/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youkhart <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/16 21:37:07 by youkhart          #+#    #+#             */
/*   Updated: 2019/11/17 09:10:37 by youkhart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

char	*g_supported_objects = "R;A;c;l;sp;pl;sq;cy;tr";
struct s_ambient_light g_ambient_light;
struct s_resolution g_resolution;
t_list *objects;

void init_objects(void)
{
    g_resolution.is_set = 0;
    g_ambient_light.is_set = 0;
	init_obj_constructor();
}

int main (int argc, char **argv)
{
	if (argc != 2)
		return (ft_printf("Error\n [!] Wrong numbers of arguments, Enter only one argument\n") ? 0 : 0);
	if(!process_file(argv))
		return (0);
	print_objects(objects);

	// RENDER HERE
	int image[g_resolution.y][g_resolution.x];
	int x = 0;
	int y = 0;
	int aspect_ratio = g_resolution.x / g_resolution.y;
	int value;
	int fov = 70;
	t_ray ray;
	while (y < g_resolution.y)
	{
		x = 0;
		while (x < g_resolution.x)
		{
			//convert raster space to Normalized Device Coordinates (NDC)
			 float NDC_x = (x + 0.5) / g_resolution.x; //adding 0.5 to align with middle of the pixel ...
			 float NDC_y = (y + 0.5) / g_resolution.y;
			
			// //convert NDC to screen space // values from -1 to 1
			 float screen_x =   2 * NDC_x - 1;
			 float screen_y = -(2 * NDC_y - 1); // to make y values above x axis (screen space) positive .....
			
			// //convert screen space to camera space, 
			float Px = screen_x * tan(fov / 2 * M_PI / 180) * aspect_ratio;
			float Py = screen_y * tan(fov / 2 * M_PI / 180);

			//cast ray
			ray.pos.x = 0;
			ray.pos.y = 0;
			ray.pos.z = 0;
			ray.dir.x = Px;
			ray.dir.y = Py;
			ray.dir.z = -1;
			ray.dir = vec_normalize(ray.dir);
			//if( !(x))
				printf("(x %.4f y %.4f)\t",ray.dir.x,ray.dir.y);
			//compute intersection 
				//with sphere
			//set pixel to one or zero 
			//image[y][x] = value;
			x++;
		}
		printf("\n");
		y++;
	}
	ft_lstclear(&objects,free_object);
	ft_printf("[ GOOD ]");
	return (0);
}

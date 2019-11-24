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
#include "mlx.h"

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

typedef struct    data_s
{
    void          *mlx_ptr;
    void          *mlx_win;
}                 data_t;

int main (int argc, char **argv)
{
	//mlx 
	data_t        data;
	//
	if (argc != 2)
		return (ft_printf("Error\n [!] Wrong numbers of arguments, Enter only one argument\n") ? 0 : 0);
	if(!process_file(argv))
		return (0);
	//print_objects(objects);
    if (!(data.mlx_ptr = mlx_init()))
        return (EXIT_FAILURE);
    if (!(data.mlx_win = mlx_new_window(data.mlx_ptr, g_resolution.x, g_resolution.y, "Hello world !!!")))
        return (EXIT_FAILURE);
	// RENDER HERE
	int image[g_resolution.y][g_resolution.x];
	int x = 0;
	int y = 0;
	int aspect_ratio = g_resolution.x / g_resolution.y;
	int value;
	int fov = 45;
	t_ray ray;
	t_vector light = {0.2,1,-1};
	int light_color = rgb_to_int("255,255,255");
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
			ray.dir.z = -1; // ZOOM 
			ray.dir = vec_normalize(ray.dir);
			//if( !(x))
				//printf(" (x %.4f y %.4f) vs ",ray.dir.x,ray.dir.y);
			//compute intersection 
				//with sphere
			t_intersection* inter;
			int color = 0;
			float min_t = INFINITY;
			t_intersection* closest = NULL;

			t_list *objs = objects;
			while (objs)
			{
				t_object *sph = (t_object *)(objs->content);
				inter = intersects_with_sphere(ray, sph);
				// closest intersection
				if(inter && inter->t < min_t && inter->t > (float)0.0001)
				{	
					min_t = inter->t;
					closest = inter;
				}
				objs = objs->next;
			}
			if (closest)
			{
				color += closest->object_color * g_ambient_light.brightness;
				//ft_printf("closest color =%d\n",closest->object_color);
				//return (0);
				//cast shadow ray
				t_ray shadow_ray;
				shadow_ray.pos = vec_add(closest->point,vec_mult(closest->normal,0.0001));
				shadow_ray.dir = vec_sub(light , shadow_ray.pos);
				int blocked = 0;
				objs = objects;
				 while (objs)
				{
					t_object *sph = (t_object *)(objs->content);
					if (intersects_with_sphere(shadow_ray, sph))
					{
						//printf("shadow!");
						blocked = 1;
						//break;
						//objs->next = NULL;
					}
					objs = objs->next;
				}
				if(!blocked)
				{
					t_vector light_dir = vec_normalize(vec_sub(light,shadow_ray.pos));
					//printf("diffused (x %.4f y %.4f z %.4f)\n",light_dir.x,light_dir.y,light_dir.z);
					//printf("color %d\n",color);
					float  f = (float)fmax(0, vec_dot(closest->normal, light_dir));
					printf("f %.4f\n",f);

					color += closest->diffuse * light_color * f;
					color = min(0xFFFFFF, color);
					//printf("newcolor %d\n",color);
					//return (0);

				}
			}
			else 
				color = 0;
				
			mlx_pixel_put(data.mlx_ptr,data.mlx_win,x,y,color);
			//ft_printf("%d",inter);
			//set pixel to one or zero
			//image[y][x] = value;
			x++;
		}
		//printf("\n");
		y++;
	}
	ft_lstclear(&objects,free_object);
	ft_printf("[ GOOD ]");
		mlx_loop(data.mlx_ptr);

    return (EXIT_SUCCESS);
}
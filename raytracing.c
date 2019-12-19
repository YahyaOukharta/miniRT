#include "minirt.h"

extern t_list *objects;
extern struct s_menu g_menu;
t_intersection *get_closest_intersection(t_list *objects, t_ray ray)
{
	t_list *objs = objects;
	t_intersection *closest = NULL;
	t_intersection *inter = NULL;
	float min_t = INFINITY;

	while (objs)
	{
		t_object *sph = (t_object *)(objs->content);
		if (!ft_memcmp(sph->type,"sp",2))
		 	inter = intersects_with_sphere(ray, sph);
		else if (!ft_strncmp(sph->type,"pl",2))
			inter = intersects_with_plane(ray, sph);
		else if (!ft_strncmp(sph->type,"tr",2))
			inter = intersects_with_triangle(ray, sph);
		 else if (!ft_strncmp(sph->type,"cy",2))
		 	inter = intersects_with_cylinder(ray, sph);
		else if (!ft_strncmp(sph->type,"sq",2))
		 	inter = intersects_with_square(ray, sph);
		// closest intersection
		if(inter && inter->t < min_t && inter->t > 0.0000001)
		{
			min_t = inter->t;
			closest = inter;
		}
		objs = objs->next;
	}
	return (closest);
}

int is_ray_blocked(t_ray shadow_ray)
{
	t_list *objs = objects;
	while (objs)
	{
		t_object *obj = (t_object *)(objs->content);
	
		if((!ft_memcmp(obj->type,"sp",max(ft_strlen(obj->type),2)) && intersects_with_sphere(shadow_ray, obj))
			|| (!ft_memcmp(obj->type,"pl",max(ft_strlen(obj->type),2)) && intersects_with_sphere(shadow_ray, obj))
			|| (!ft_memcmp(obj->type,"tr",max(ft_strlen(obj->type),2)) && intersects_with_triangle(shadow_ray, obj))
			|| (!ft_memcmp(obj->type,"cy",max(ft_strlen(obj->type),2)) && intersects_with_cylinder(shadow_ray, obj))
			|| (!ft_memcmp(obj->type,"sq",max(ft_strlen(obj->type),2)) && intersects_with_square(shadow_ray, obj))
			)
		{
			return(1);
		}
		objs = objs->next;
	}
	return (0);
}

int compute_pixel_color(t_intersection *closest,t_ray ray, t_list *lights)
{
	int blocked = 0;
	float color,a_color,d_color,s_color = 0;
	t_ray shadow_ray;

	//ambient lighting
	a_color = get_ambient_color(closest);
	color = a_color;
	//cast shadow ray towards lights
	while (lights)
	{
		t_light* light = ((t_light *)((t_object *)(lights->content))->details);
		shadow_ray.pos = vec_add(vec_add(ray.pos,vec_mult(ray.dir, closest->t)),vec_mult(closest->normal, 0.00000001));
		shadow_ray.dir = vec_normalize(vec_sub(light->pos, shadow_ray.pos));
		if(!is_ray_blocked(shadow_ray))
		{
			//diffuse lighting
			d_color = add_colors(d_color, get_diffuse_color(closest, shadow_ray, light));
			//specular lighting
			s_color = add_colors(s_color, get_specular_color(closest, ray, shadow_ray, light));
		}
		lights = lights->next;
	}
	color = add_colors(d_color, a_color);
	color = add_colors(color ,s_color);
	return (color);
}
t_ray cast_ray(int x, int y, t_camera *cam, float zoom)
{
	t_ray ray;
	float NDC_x = (x + 0.5) / g_resolution.x; //adding 0.5 to align with middle of the pixel ...
	float NDC_y = (y + 0.5) / g_resolution.y;

	// //convert NDC to screen space   // values from -1 to 1
	float screen_x =   2 * NDC_x - 1;  
	float screen_y = -(2 * NDC_y - 1); // to make y values above x axis (screen space) positive .....

	// //convert screen space to camera space, 
	float Px = screen_x * tan(cam->fov / 2 * M_PI / 180) * g_resolution.x / g_resolution.y;
	float Py = screen_y * tan(cam->fov / 2 * M_PI / 180);

	//cast ray
	ray.pos = cam->pos;
	ray.dir.x = Px;
	ray.dir.y = Py;
	ray.dir.z = zoom; // ZOOM
	ray.dir = vec_normalize(ray.dir);

	ray.dir = vec_rotate(ray.dir, cam->rot);
	return (ray);
}
int render(data_t data,t_list *objects, t_list *lights, t_list* current_camera, int part)
{
	int aspect_ratio = g_resolution.x / g_resolution.y;
	t_ray ray;
	t_camera *current_cam = (t_camera *)((t_object *)current_camera->content)->details;	
	int fov = current_cam->fov;
	int w,h;
	int x = 0;
	int y = 0;
	w = g_resolution.x;
	h = g_resolution.y;
	if (part == 1)
	{
		w /= 2;
		h /= 2;
	}
	else if (part == 2)
	{
		x = w / 2 + 1;
		h /= 2;
	}
	else if (part == 3)
	{
		w /= 2;
		y = h / 2 + 1;
	}
	else if (part == 4)
	{
		x = w / 2 + 1;
		y = h / 2 + 1; 
	}
	//ft_printf("w %d h %d x %d y %d\n", w, h, x, y);
	int tmp = x;
	//mlx_clear_window(data.mlx_ptr, data.mlx_win);
	while (y < h)
	{
		x = tmp;
		while (x < w)
		{	
			//colors for different types of lighting
			float color,a_color,d_color,s_color = 0;
			//convert raster space to Normalized Device Coordinates (NDC)
			ray = cast_ray(x,y,current_cam, -1);
			t_intersection* closest = get_closest_intersection(objects, ray);
			if (closest)
				color = compute_pixel_color(closest,ray,lights);
			else
				color = 0;
			if (g_menu.on && x < g_menu.menu_w)
				color = mult_colors(color, g_menu.opacity);
			(data.img_data)[y * w + x] = (int)color;
			x++;
		}
		y++;
	}
	if (!part)
	{
		mlx_put_image_to_window(data.mlx_ptr,data.mlx_win, data.img_ptr, 0 ,0);
		menu_toggle_msg();
		show_menu();
		selected_objects_msg();
	}
	return (1);
}
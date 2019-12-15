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
#include <pthread.h>
char	*g_supported_objects = "R;A;c;l;sp;pl;sq;cy;tr";
struct s_ambient_light g_ambient_light;
struct s_resolution g_resolution;
t_list *objects;
t_list *lights;
t_list *cameras;
t_list *current_camera;
t_list *current_light;
struct s_menu g_menu;
data_t        data; // mlx struct 
struct s_object *selected_object;
static int *img;
pthread_mutex_t mutex;
void init_objects(void)
{
    g_resolution.is_set = 0;
    g_ambient_light.is_set = 0;
	init_obj_constructor();
}


//lighting function
int get_ambient_color(t_intersection *closest)
{
	return (add_colors(mult_colors(g_ambient_light.color, g_ambient_light.brightness), mult_colors(closest->object_color, g_ambient_light.brightness)));
}

int get_diffuse_color(t_intersection *closest, t_ray shadow_ray, t_light *light)
{	
	t_vector light_dir = vec_normalize(vec_sub(light->pos,shadow_ray.pos));
	float  dot = fmax(vec_dot(closest->normal, light_dir),0);
	return (mult_colors(light->color, dot * closest->diffuse * light->brightness));
}
int get_specular_color(t_intersection *closest, t_ray ray, t_ray shadow_ray, t_light *light)
{
	t_vector light_dir = vec_normalize(vec_sub(light->pos,shadow_ray.pos));
	t_vector reflection_dir = vec_sub(ray.dir, vec_mult(closest->normal, 2 * vec_dot(ray.dir,closest->normal)));
	t_vector view_dir = vec_mult(ray.dir,-1);
	float dot =  fmax(vec_dot(reflection_dir, light_dir), 0);
	return(mult_colors(light->color, closest->specular * pow(dot, closest->s_power) * light->brightness));
}
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
int render(data_t data,t_list *objects, t_list *lights, t_list* current_camera, int *save)
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
	int part = (int)save;
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
			if (!save && g_menu.on && x < g_menu.menu_w)
			{
				color = mult_colors(color, g_menu.opacity);
			}
			if ((int)save && (int)save > 4 )
				save[(w * h) - y * w + x] = color;
			else
			{
				mlx_pixel_put(data.mlx_ptr, data.mlx_win, x, y, (int)floor(color));
			}
			x++;
		}
		y++;
	}
	if (save == 0)
	{	menu_toggle_msg();
		show_menu();
		selected_objects_msg();
	}
	return (1);
}

void *render_thread(void *part)
{
	render(data,objects,lights,current_camera,part);
	printf("rendered from thread");
	pthread_exit(NULL);
}
//event handling
int	re_render(int key,void *param)
{
	pthread_t t1,t2,t3,t4;
	mlx_clear_window(data.mlx_ptr, data.mlx_win);
	// pthread_mutex_init(&mutex, NULL);
	// pthread_create(&t1, NULL, render_thread, (void *)1);
	//  pthread_create(&t2, NULL, render_thread, (void *)2);
	// pthread_create(&t3, NULL, render_thread, (void *)3);
	//  pthread_create(&t4, NULL, render_thread, (void *)4);
	//   pthread_join(t1,NULL); 	
	//   pthread_join(t2,NULL); 	
	//  pthread_join(t3,NULL); 	
	//   pthread_join(t4,NULL);
	//  pthread_mutex_destroy(&mutex);
	 render(data,objects,lights,current_camera,param);
	return (1);
}

//camera
int	rotate_camera(int key,void *param)
{
	t_camera *cam = (t_camera *)((t_object *)current_camera->content)->details;
	if (key == KEY_RIGHT)
		cam->rot.y -= 0.1;
	if (key == KEY_LEFT)
		cam->rot.y += 0.1;
	if (key == KEY_UP)
		cam->rot.x -= 0.1;
	if (key == KEY_DOWN)
		cam->rot.x += 0.1;
	re_render(key, NULL);
	return (0);
}
int	move_camera(int key,void *param)
{
	t_camera *cam = (t_camera *)((t_object *)current_camera->content)->details;
	float vel = 0.1;
	if (key == KEY_D)
		cam->pos = vec_add(cam->pos,vec_mult(vec_rotate(vec_create(1,0,0), cam->rot),vel));
	if (key == KEY_A)
		cam->pos = vec_add(cam->pos,vec_mult(vec_rotate(vec_create(1,0,0), cam->rot),-vel));
	if (key == KEY_W)
		cam->pos = vec_add(cam->pos,vec_mult(vec_rotate(vec_create(0,0,-1), cam->rot),vel));
	if (key == KEY_S)
		cam->pos = vec_add(cam->pos,vec_mult(vec_rotate(vec_create(0,0,-1), cam->rot),-vel));
	re_render(key, NULL);
	return (0);
}
int change_camera(int key, void *param)
{
	if (current_camera->next)
		current_camera = current_camera->next;
	else
		current_camera = cameras;
	re_render(key,NULL);
	return (0);
}

//objects
int	transform_object(int key,void *param)
{
	t_object *obj = selected_object;
	int index = index_of_in_tab(obj->type,ft_split(g_supported_objects,';')) - 3;
	printf("index %d\n",index);
	g_obj_transformer[index](key,param);
	re_render(key, NULL);
	return (0);
}
int toggle_menu(int key, void *param)
{
	g_menu.on = !g_menu.on;
	re_render(key,NULL);
	return (0);
}
int edit_lights(int key, void *param)
{
	if (current_light)
		current_light = (current_light->next ? current_light->next : lights);
	else
		current_light = lights;
	selected_object = (t_object *)current_light->content;
	return (re_render(key,NULL));
}
int save_frame(int key,void *param)
{
	ft_printf("saving frame");
	img = (int *)malloc( g_resolution.x * g_resolution.y * sizeof(int));
	render(data,objects,lights,current_camera, img);
	save_bmp("img.bmp",g_resolution.x,g_resolution.y,72,img);
	free(img);
	ft_printf("Saved img\n");
	return (0);
}
int handle_keys(int key, void *param)
{
	if (key == KEY_RIGHT || key == KEY_LEFT || key == KEY_UP || key == KEY_DOWN)
		return ((selected_object ? transform_object(key, param) : rotate_camera(key, param)));
	else if (key == KEY_D || key == KEY_A || key == KEY_W || key == KEY_S)
		return ((selected_object ? transform_object(key, param) : move_camera(key, param)));
	else if (key == KEY_C)
		return (selected_object ? ((selected_object = NULL) ||(current_light = NULL) || re_render(key , param)) : change_camera(key,param));
	else if (key == KEY_M)
		return (toggle_menu(key,param));
	else if (key == KEY_L)
		return (edit_lights(key,param));
	else if (key == KEY_P)
		return (save_frame(key,param));
	return (0);
}
int select_object(int button, int x, int y, void * param)
{
	t_camera *cam = (t_camera *)((t_object *)current_camera->content)->details;
	t_ray ray = cast_ray(x,y,cam, -1);
	t_intersection* closest = get_closest_intersection(objects, ray);
	t_object *tmp = (closest ? closest->obj : NULL);
	if (button == 1 && selected_object != tmp)
	{
		selected_object = tmp;
		re_render(0, NULL);
	}
	return (1);
}
int resize_object(int btn, int x, int y,void *param)
{
	float ratio = 0.05;
	char *type = selected_object->type;
	if (!ft_memcmp(type,"sp",max(ft_strlen(type),2)))
		((t_sphere *)selected_object->details)->diameter += (btn == 4 ? -1 : 1) * ratio;
	if (!ft_memcmp(type,"sq",max(ft_strlen(type),2)))
		((t_square *)selected_object->details)->side_size += (btn == 4 ? -1 : 1) * ratio;
	re_render(btn, param);
	return (1);
}
int move_light_z(int btn, int x, int y,void *param)
{
	float vel = 0.05;
	t_light *light = (t_light *)(((t_object *)current_light->content)->details);
	light->pos = vec_add(light->pos,vec_mult(vec_create(0,0,1), (btn == 4 ? -1 : 1) * vel));
	re_render(btn, param);
	return (1);
}
int add_new_light(int button, int x, int y, void * param)
{
	//printf("btn = %d x = %d y = %d \n",button,x,y);
	t_camera *cam = (t_camera *)((t_object *)current_camera->content)->details;
	t_ray ray = cast_ray(x,y,cam, -1);
	t_intersection* closest = get_closest_intersection(objects, ray);
	if (closest)
	{
		t_vector p = closest->point;
		char *data = ft_strjoin_va(7,"l ",ft_ftoa(p.x,2),",",ft_ftoa(p.y,2),",",ft_ftoa(p.z,2)," 0.4 255,255,180");
		add_light(ft_split(data,' '));
		return (re_render(button, NULL));
	}
	return (1);
}
int handle_mouse(int button, int x, int y, void *param)
{	
	if (button == 1 && y >= 0)
		return ((current_light ? add_new_light(button,x,y,param) : select_object(button,x,y,param)));
	if ((button == 4 || button == 5) && y >= 0)
		return ((current_light ? move_light_z(button, x,y,param) : (selected_object && resize_object(button,x,y,param))));
	return (0);
}

int main (int argc, char **argv)
{
	//file processing and scene objects storing
	if (argc < 2 || argc > 3)
		return (ft_printf("Error\n [!] Wrong numbers of arguments, Enter path for scene file as first argument, and --save as second argument (optional) to save rendered image as .bmp\n") ? 0 : 0);
	if (!process_file(argc, argv))
		return (0);

//	print_objects(objects);
//	print_objects(lights); 
//	print_objects(cameras);
	current_camera = cameras;
	init_menu();
	init_obj_transformer();

    if (!(data.mlx_ptr = mlx_init()))
        return (EXIT_FAILURE);
    if (!(data.mlx_win = mlx_new_window(data.mlx_ptr, g_resolution.x, g_resolution.y, "miniRT")))
        return (EXIT_FAILURE);
	// RENDER HERE

	if (argc == 3) //save if the save option is on
		return (save_frame(0,0));

	if(!render(data,objects,lights,current_camera,0))
		return (0);
	t_light *li  = (t_light *)((t_object *)lights->content)->details;
	t_sphere *sph = (t_sphere *)((t_object *)objects->content)->details;

	mlx_key_hook(data.mlx_win, handle_keys, NULL);
	mlx_mouse_hook(data.mlx_win,handle_mouse,NULL);
	mlx_loop(data.mlx_ptr);

	ft_lstclear(&objects,free_object);
	ft_printf("[ GOOD ]");
    return (EXIT_SUCCESS);
}
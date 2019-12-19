#include "minirt.h"
extern char     *g_supported_objects;
extern t_list   *objects;
extern t_list   *lights;
extern t_list   *cameras;
extern t_list   *current_camera;
extern t_list   *current_light;
extern struct s_object *selected_object;
extern data_t data;
extern struct s_menu g_menu;

//event handling
void *render_thread(void *part)
{
	render(data,objects,lights,current_camera,(int)part);
	//printf("rendered from thread");
	//pthread_exit(NULL);
    return (0);
}
int	re_render(int key,void *param)
{
	//pthread_t t1,t2,t3,t4;
	mlx_clear_window(data.mlx_ptr, data.mlx_win);
	// pthread_create(&t1, NULL, render_thread, (void *)1);
	// pthread_create(&t2, NULL, render_thread, (void *)2);
	// pthread_create(&t3, NULL, render_thread, (void *)3);
	// pthread_create(&t4, NULL, render_thread, (void *)4);
	// pthread_join(t1,NULL); 	
	// pthread_join(t2,NULL); 	
	// pthread_join(t3,NULL); 	
	// pthread_join(t4,NULL);

	render(data,objects,lights,current_camera,0);
	//mlx_put_image_to_window(data.mlx_ptr,data.mlx_win, data.img_ptr, 0, 0);

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
	render(data,objects,lights,current_camera, 10);
	save_bmp("img.bmp",g_resolution.x,g_resolution.y,72, (int *)data.img_data);
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
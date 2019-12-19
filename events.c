#include "minirt.h"
extern struct s_minirt g_minirt;

//event handling
void *render_thread(void *part)
{
	render((int)part);
	//printf("rendered from thread");
	//pthread_exit(NULL);
    return (0);
}
int	re_render(int key,void *param)
{
	mlx_clear_window(g_minirt.data.mlx_ptr, g_minirt.data.mlx_win);
	render(0);
	return (1);
}
//camera
int	rotate_camera(int key,void *param)
{
	t_camera *cam = (t_camera *)((t_object *)g_minirt.current_camera->content)->details;
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
	t_camera *cam = (t_camera *)((t_object *)g_minirt.current_camera->content)->details;
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
	if (g_minirt.current_camera->next)
		g_minirt.current_camera = g_minirt.current_camera->next;
	else
		g_minirt.current_camera = g_minirt.cameras;
	re_render(key,NULL);
	return (0);
}

//objects
int	transform_object(int key,void *param)
{
	t_object *obj = g_minirt.selected_object;
	int index = index_of_in_tab(obj->type,ft_split(g_minirt.g_supported_objects,';')) - 3;
	printf("index %d\n",index);
	g_obj_transformer[index](key,param);
	re_render(key, NULL);
	return (0);
}
int toggle_menu(int key, void *param)
{
	g_minirt.g_menu.on = !g_minirt.g_menu.on;
	re_render(key,NULL);
	return (0);
}
int edit_lights(int key, void *param)
{
	if (g_minirt.current_light)
		g_minirt.current_light = (g_minirt.current_light->next ? g_minirt.current_light->next : g_minirt.lights);
	else
		g_minirt.current_light = g_minirt.lights;
	g_minirt.selected_object = (t_object *)g_minirt.current_light->content;
	return (re_render(key,NULL));
}
int save_frame(int key,void *param)
{
	ft_printf("saving frame");
	render(10);
	save_bmp("img.bmp",g_minirt.g_resolution.x,g_minirt.g_resolution.y,72, (int *)g_minirt.data.img_data);
	ft_printf("Saved img\n");
	return (0);
}
int handle_keys(int key, void *param)
{
	if (key == KEY_RIGHT || key == KEY_LEFT || key == KEY_UP || key == KEY_DOWN)
		return ((g_minirt.selected_object ? transform_object(key, param) : rotate_camera(key, param)));
	else if (key == KEY_D || key == KEY_A || key == KEY_W || key == KEY_S)
		return ((g_minirt.selected_object ? transform_object(key, param) : move_camera(key, param)));
	else if (key == KEY_C)
		return (g_minirt.selected_object ? ((g_minirt.selected_object = NULL) ||(g_minirt.current_light = NULL) || re_render(key , param)) : change_camera(key,param));
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
	t_camera *cam = (t_camera *)((t_object *)g_minirt.current_camera->content)->details;
	t_ray ray = cast_ray(x,y,cam, -1);
	t_intersection* closest = get_closest_intersection(g_minirt.objects, ray);
	t_object *tmp = (closest ? closest->obj : NULL);
	if (button == 1 && g_minirt.selected_object != tmp)
	{
		g_minirt.selected_object = tmp;
		re_render(0, NULL);
	}
	return (1);
}
int resize_object(int btn, int x, int y,void *param)
{
	float ratio = 0.05;
	char *type = g_minirt.selected_object->type;
	if (!ft_memcmp(type,"sp",max(ft_strlen(type),2)))
		((t_sphere *)g_minirt.selected_object->details)->diameter +=
			(btn == 4 ? -1 : 1) * ratio;
	if (!ft_memcmp(type,"sq",max(ft_strlen(type),2)))
		((t_square *)g_minirt.selected_object->details)->side_size +=
			(btn == 4 ? -1 : 1) * ratio;
	re_render(btn, param);
	return (1);
}
int move_light_z(int btn, int x, int y,void *param)
{
	float vel = 0.05;
	t_light *light = (t_light *)(((t_object *)g_minirt.current_light->content)->details);
	light->pos = vec_add(light->pos,vec_mult(vec_create(0,0,1), (btn == 4 ? -1 : 1) * vel));
	re_render(btn, param);
	return (1);
}
int add_new_light(int button, int x, int y, void * param)
{
	//printf("btn = %d x = %d y = %d \n",button,x,y);
	t_camera *cam = (t_camera *)((t_object *)g_minirt.current_camera->content)->details;
	t_ray ray = cast_ray(x,y,cam, -1);
	t_intersection* closest = get_closest_intersection(g_minirt.objects, ray);
	if (closest)
	{
		t_vector p = vec_add(closest->point,vec_mult(closest->normal,0.08));
		char *data = ft_strjoin_va(7,"l ",ft_ftoa(p.x,2),",",ft_ftoa(p.y,2),",",ft_ftoa(p.z,2)," 0.4 255,255,180");
		add_light(ft_split(data,' '));
		return (re_render(button, NULL));
	}
	return (1);
}
int handle_mouse(int button, int x, int y, void *param)
{	
	if (button == 1 && y >= 0)
		return ((g_minirt.current_light ? add_new_light(button,x,y,param) : select_object(button,x,y,param)));
	if ((button == 4 || button == 5) && y >= 0)
		return ((g_minirt.current_light ? move_light_z(button, x,y,param) : (g_minirt.selected_object && resize_object(button,x,y,param))));
	return (0);
}
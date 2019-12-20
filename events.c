#include "minirt.h"
#include <time.h>

extern struct s_minirt g_rt;

int	re_render(int key, void *param)
{
	clock_t t[2];

	mlx_clear_window(g_rt.data.mlx_ptr, g_rt.data.mlx_win);
	t[0] = clock();
	render(0, 0, g_rt.g_res.x, g_rt.g_res.y);
	t[1] = clock();
	ft_printf("Rendering time (s) : %s\n",
		ft_ftoa((double)(t[1] - t[0]) / (double)CLOCKS_PER_SEC, 3));
	return (1);
}

int	rotate_camera(int key, void *param)
{
	t_cam *cam;

	cam = (t_cam *)((t_obj *)g_rt.curr_cam->content)->details;
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

int	move_camera(int key, void *param)
{
	t_cam *cam;
	float vel;

	vel = 0.1;
	cam = (t_cam *)((t_obj *)g_rt.curr_cam->content)->details;
	if (key == KEY_D)
		cam->pos = vec_add(cam->pos,
			vec_mult(vec_rotate(vec_create(1, 0, 0), cam->rot), vel));
	if (key == KEY_A)
		cam->pos = vec_add(cam->pos,
			vec_mult(vec_rotate(vec_create(1, 0, 0), cam->rot), -vel));
	if (key == KEY_W)
		cam->pos = vec_add(cam->pos,
			vec_mult(vec_rotate(vec_create(0, 0, -1), cam->rot), vel));
	if (key == KEY_S)
		cam->pos = vec_add(cam->pos,
			vec_mult(vec_rotate(vec_create(0, 0, -1), cam->rot), -vel));
	re_render(key, NULL);
	return (0);
}

int	change_camera(int key, void *param)
{
	if (g_rt.curr_cam->next)
		g_rt.curr_cam = g_rt.curr_cam->next;
	else
		g_rt.curr_cam = g_rt.cameras;
	re_render(key, NULL);
	return (0);
}

int	transform_object(int key, void *param)
{
	t_obj	*obj;
	int		index;

	obj = g_rt.selected_object;
	index = index_of_in_tab(obj->type,
		ft_split(g_rt.g_supported_objects, ';')) - 3;
	g_obj_transformer[index](key, param);
	re_render(key, NULL);
	return (0);
}

int	toggle_menu(int key, void *param)
{
	g_rt.g_menu.on = !g_rt.g_menu.on;
	re_render(key, NULL);
	return (0);
}

int	edit_lights(int key, void *param)
{
	if (g_rt.current_light)
		g_rt.current_light = (g_rt.current_light->next ?
			g_rt.current_light->next : g_rt.lights);
	else
		g_rt.current_light = g_rt.lights;
	g_rt.selected_object = ((t_obj *)g_rt.current_light ?
		(t_obj *)g_rt.current_light->content : NULL);
	return (re_render(key, NULL));
}

int	save_frame(int key, void *param)
{
	ft_printf("	[~] Saving...\n");
	render(0, 0, g_rt.g_res.x, g_rt.g_res.y);
	save_bmp("img.bmp", g_rt.g_res.x, g_rt.g_res.y,
		72, (int *)g_rt.data.img_data);
	ft_printf("	[+] Saved frame\n");
	return (0);
}

int	handle_keys(int key, void *param)
{
	if (key == KEY_RIGHT || key == KEY_LEFT || key == KEY_UP || key == KEY_DOWN)
		return ((g_rt.selected_object ?
			transform_object(key, param) : rotate_camera(key, param)));
	else if (key == KEY_D || key == KEY_A || key == KEY_W || key == KEY_S)
		return ((g_rt.selected_object ?
			transform_object(key, param) : move_camera(key, param)));
	else if (key == KEY_C)
		return (g_rt.selected_object ?
			((g_rt.selected_object = NULL)
				|| (g_rt.current_light = NULL)
				|| re_render(key, param))
				: change_camera(key, param));
	else if (key == KEY_M)
		return (toggle_menu(key, param));
	else if (key == KEY_L)
		return (edit_lights(key, param));
	else if (key == KEY_P)
		return (save_frame(key, param));
	return (0);
}

int	select_obj(int button, int x, int y, void *param)
{
	t_cam			*cam;
	t_ray			ray;
	t_intersection	*closest;
	t_obj			*tmp;

	cam = (t_cam *)((t_obj *)g_rt.curr_cam->content)->details;
	ray = cast_ray(x, y, cam, -1);
	closest = get_closest_intersection(g_rt.objects, ray);
	tmp = (closest ? closest->obj : NULL);
	if (button == 1 && g_rt.selected_object != tmp)
	{
		g_rt.selected_object = tmp;
		re_render(0, NULL);
	}
	return (1);
}

int	resize_object(int btn, int x, int y, void *param)
{
	float	ratio;
	char	*type;

	ratio = 0.05;
	type = g_rt.selected_object->type;
	if (!ft_memcmp(type, "sp", max(ft_strlen(type), 2)))
		((t_sphere *)g_rt.selected_object->details)->diameter +=
			(btn == 4 ? -1 : 1) * ratio;
	if (!ft_memcmp(type, "sq", max(ft_strlen(type), 2)))
		((t_square *)g_rt.selected_object->details)->side_size +=
			(btn == 4 ? -1 : 1) * ratio;
	re_render(btn, param);
	return (1);
}

int	move_light_z(int btn, int x, int y, void *param)
{
	float	vel;
	t_light	*light;

	vel = 0.05;
	light = (t_light *)(((t_obj *)g_rt.current_light->content)->details);
	light->pos = vec_add(light->pos,
		vec_mult(vec_create(0, 0, 1), (btn == 4 ? -1 : 1) * vel));
	re_render(btn, param);
	return (1);
}

int	add_new_light(int button, int x, int y, void *param)
{
	t_cam			*cam;
	t_ray			ray;
	t_intersection	*closest;
	char			*data;
	t_vector		p;

	cam = (t_cam *)((t_obj *)g_rt.curr_cam->content)->details;
	ray = cast_ray(x, y, cam, -1);
	closest = get_closest_intersection(g_rt.objects, ray);
	if (closest)
	{
		p = vec_add(closest->point, vec_mult(closest->normal, 0.08));
		data = ft_strjoin_va(7, "l ", ft_ftoa(p.x, 2), ",", ft_ftoa(p.y, 2),
			",", ft_ftoa(p.z, 2), " 0.7 255,255,180");
		add_light(ft_split(data, ' '));
		return (re_render(button, NULL));
	}
	return (1);
}

int	handle_mouse(int button, int x, int y, void *param)
{
	if (button == 1 && y >= 0)
		return ((g_rt.current_light ?
			add_new_light(button, x, y, param)
			: select_obj(button, x, y, param)));
	else if ((button == 4 || button == 5) && y >= 0)
		return ((g_rt.current_light ?
			move_light_z(button, x, y, param)
			: (g_rt.selected_object
			&& resize_object(button, x, y, param))));
	else
		return (0);
}

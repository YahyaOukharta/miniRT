#include "objects.h"
#include "../minirt.h"
extern struct s_minirt g_rt;

t_light		*new_light(char **info)
{
	t_light	*new_light;
	char	**tab;

	new_light = (t_light *)malloc(sizeof(t_light));
	tab = ft_split(info[1], ',');
	new_light->pos.x = ft_atof(tab[0]);
	new_light->pos.y = ft_atof(tab[1]);
	new_light->pos.z = ft_atof(tab[2]);
	free_s_tab(tab);
	new_light->brightness = ft_atof(info[2]);
	new_light->color = rgb_to_int(info[3]);
	return (new_light);
}

int			add_light(char **tab)
{
	t_obj *obj;

	obj = (t_obj *)malloc(sizeof(t_obj));
	obj->type = ft_strdup(tab[0]);
	obj->details = (void *)new_light(tab);
	ft_lstadd_back(&g_rt.lights, ft_lstnew(obj));
	return (1);
}

int			transform_light(int key, void *param)
{
	t_light	*light;
	t_cam	*cam;

	light = (t_light *)g_rt.selected_object->details;
	cam = (t_cam *)((t_obj *)g_rt.curr_cam->content)->details;
	if (key == KEY_D)
		light->pos = vec_add(light->pos,
			vec_mult(vec_rotate(vec_create(1, 0, 0), cam->rot), TRANS_VEL));
	if (key == KEY_A)
		light->pos = vec_add(light->pos,
			vec_mult(vec_rotate(vec_create(1, 0, 0), cam->rot), -TRANS_VEL));
	if (key == KEY_W)
		light->pos = vec_add(light->pos,
			vec_mult(vec_rotate(vec_create(0, 1, 0), cam->rot), TRANS_VEL));
	if (key == KEY_S)
		light->pos = vec_add(light->pos,
			vec_mult(vec_rotate(vec_create(0, 1, 0), cam->rot), -TRANS_VEL));
	return (0);
}

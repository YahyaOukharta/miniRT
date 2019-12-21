#include "objects.h"
#include "../minirt.h"
extern struct s_minirt g_rt;

t_sphere	*new_sphere(char **info)
{
	t_sphere	*new_sphere;
	char		**tab;

	new_sphere = (t_sphere *)malloc(sizeof(t_sphere));
	tab = ft_split(info[1], ',');
	new_sphere->pos.x = ft_atof(tab[0]);
	new_sphere->pos.y = ft_atof(tab[1]);
	new_sphere->pos.z = ft_atof(tab[2]);
	free_s_tab(tab);
	new_sphere->diameter = ft_atof(info[2]);
	new_sphere->color = rgb_to_int(info[3]);
	return (new_sphere);
}

int			add_sphere(char **tab)
{
	t_obj *obj;

	obj = (t_obj *)malloc(sizeof(t_obj));
	obj->type = ft_strdup(tab[0]);
	obj->details = (void *)new_sphere(tab);
	ft_lstadd_back(&g_rt.objects, ft_lstnew(obj));
	return (1);
}

int			transform_sphere(int key, void *param)
{
	t_sphere	*sphere;
	t_cam		*cam;
	float		vel;

	cam = (t_cam *)((t_obj *)g_rt.curr_cam->content)->details;
	sphere = (t_sphere *)g_rt.selected_object->details;
	if (key == KEY_D)
		sphere->pos = vec_add(sphere->pos,
			vec_mult(vec_rotate(vec_create(1, 0, 0), cam->rot), TRANS_VEL));
	if (key == KEY_A)
		sphere->pos = vec_add(sphere->pos,
			vec_mult(vec_rotate(vec_create(1, 0, 0), cam->rot), -TRANS_VEL));
	if (key == KEY_W)
		sphere->pos = vec_add(sphere->pos,
			vec_mult(vec_rotate(vec_create(0, 1, 0), cam->rot), TRANS_VEL));
	if (key == KEY_S)
		sphere->pos = vec_add(sphere->pos,
			vec_mult(vec_rotate(vec_create(0, 1, 0), cam->rot), -TRANS_VEL));
	return (0);
}
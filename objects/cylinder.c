#include "objects.h"
#include "../minirt.h"

extern struct s_minirt g_rt;

t_cylinder	*new_cylinder(char **info)
{
	t_cylinder	*new_cylinder;
	char		**tab;

	new_cylinder = (t_cylinder *)malloc(sizeof(t_cylinder));
	tab = ft_split(info[1], ',');
	new_cylinder->pos.x = ft_atof(tab[0]);
	new_cylinder->pos.y = ft_atof(tab[1]);
	new_cylinder->pos.z = ft_atof(tab[2]);
	free_s_tab(tab);
	tab = ft_split(info[2], ',');
	new_cylinder->orientation.x = ft_atof(tab[0]);
	new_cylinder->orientation.y = ft_atof(tab[1]);
	new_cylinder->orientation.z = ft_atof(tab[2]);
	free_s_tab(tab);
	new_cylinder->diameter = ft_atof(info[3]);
	new_cylinder->height = ft_atof(info[4]);
	new_cylinder->color = rgb_to_int(info[5]);
	return (new_cylinder);
}

int			add_cylinder(char **tab)
{
	t_obj *obj;

	obj = (t_obj *)malloc(sizeof(t_obj));
	obj->type = ft_strdup(tab[0]);
	obj->details = (void *)new_cylinder(tab);
	ft_lstadd_back(&g_rt.objects, ft_lstnew(obj));
	return (1);
}
int			transform_cylinder(int key, void *param)
{
	t_cylinder *cylinder = (t_cylinder *)g_rt.selected_object->details;
	t_cam *cam = (t_cam *)((t_obj *)g_rt.curr_cam->content)->details;
	float vel = 0.1;
	if (key == KEY_D)
		cylinder->pos = vec_add(cylinder->pos,vec_mult(vec_rotate(vec_create(1,0,0), cam->rot),vel));
	if (key == KEY_A)
		cylinder->pos = vec_add(cylinder->pos,vec_mult(vec_rotate(vec_create(1,0,0), cam->rot),-vel));
	if (key == KEY_W)
		cylinder->pos = vec_add(cylinder->pos,vec_mult(vec_rotate(vec_create(0,1,0), cam->rot),vel));
	if (key == KEY_S)
		cylinder->pos = vec_add(cylinder->pos,vec_mult(vec_rotate(vec_create(0,1,0), cam->rot),-vel));
	if (key == KEY_RIGHT)
	   cylinder->orientation = vec_rotate(cylinder->orientation, vec_create(0,0,vel));
	if (key == KEY_LEFT)
		cylinder->orientation = vec_rotate(cylinder->orientation, vec_create(0,0,-vel));
	if (key == KEY_UP)
		cylinder->orientation = vec_rotate(cylinder->orientation, vec_create(vel,0,0));
	if (key == KEY_DOWN)
		cylinder->orientation = vec_rotate(cylinder->orientation, vec_create(-vel,0,0));
	return (0);
}
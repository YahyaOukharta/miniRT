#include "objects.h"
#include "../minirt.h"

extern struct s_minirt g_rt;

t_plane		*new_plane(char **info)
{
	t_plane *new_plane;
	char **tab;

	new_plane = (t_plane *)malloc(sizeof(t_plane));
	tab = ft_split(info[1], ',');
	new_plane->pos.x = ft_atof(tab[0]);
	new_plane->pos.y = ft_atof(tab[1]);
	new_plane->pos.z = ft_atof(tab[2]);
   free_s_tab(tab);

	tab = ft_split(info[2], ',');
	new_plane->orientation.x = ft_atof(tab[0]);
	new_plane->orientation.y = ft_atof(tab[1]);
	new_plane->orientation.z = ft_atof(tab[2]);
   free_s_tab(tab);

	new_plane->color = rgb_to_int(info[3]);
	return (new_plane);
}

int			add_plane(char **tab)
{
	t_obj *obj;

	obj = (t_obj *)malloc(sizeof(t_obj));
	obj->type = ft_strdup(tab[0]);
	obj->details = (void *)new_plane(tab);
	ft_lstadd_back(&g_rt.objects, ft_lstnew(obj));
	return (1);
}
int			transform_plane(int key, void *param)
{
	t_plane *plane = (t_plane *)g_rt.selected_object->details;
	t_cam *cam = (t_cam *)((t_obj *)g_rt.curr_cam->content)->details;
	float vel = 0.1;
	if (key == KEY_D)
		plane->pos = vec_add(plane->pos,vec_mult(vec_rotate(vec_create(1,0,0), cam->rot),vel));
	if (key == KEY_A)
		plane->pos = vec_add(plane->pos,vec_mult(vec_rotate(vec_create(1,0,0), cam->rot),-vel));
	if (key == KEY_W)
		plane->pos = vec_add(plane->pos,vec_mult(vec_rotate(vec_create(0,1,0), cam->rot),vel));
	if (key == KEY_S)
		plane->pos = vec_add(plane->pos,vec_mult(vec_rotate(vec_create(0,1,0), cam->rot),-vel));
	if (key == KEY_RIGHT)
		rotate_y(&plane->orientation.x,&plane->orientation.z,vel);
	if (key == KEY_LEFT)
		rotate_y(&plane->orientation.x,&plane->orientation.z,-vel);
	if (key == KEY_UP)
		rotate_x(&plane->orientation.y,&plane->orientation.z,vel);
	if (key == KEY_DOWN)
		rotate_x(&plane->orientation.y,&plane->orientation.z,-vel);
	return (0);
}
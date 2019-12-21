#include "../minirt.h"

extern struct s_minirt g_rt;

t_cam		*new_camera(char **info)
{
	t_cam *new_cam;
	char **tab;

	new_cam = (t_cam *)malloc(sizeof(t_cam));
	tab = ft_split(info[1], ',');
	new_cam->pos.x = ft_atof(tab[0]);
	new_cam->pos.y = ft_atof(tab[1]);
	new_cam->pos.z = ft_atof(tab[2]);
	free_s_tab(tab);

	tab = ft_split(info[2], ',');
	new_cam->dir.x = ft_atof(tab[0]);
	new_cam->dir.y = ft_atof(tab[1]);
	new_cam->dir.z = ft_atof(tab[2]);
	free_s_tab(tab);

	new_cam->fov = ft_atof(info[3]);
	t_vector tmp;

	tmp = vec_normalize(new_cam->dir);
	tmp.x = 0;
	tmp = vec_normalize(tmp);
	float Rx = acos(vec_dot(vec_create(0,0,-1),tmp));

	tmp = vec_normalize(new_cam->dir);
	tmp.y = 0;
	tmp = vec_normalize(tmp);
	float Ry = acos(vec_dot(vec_create(0,0,-1),tmp));
	new_cam->rot = vec_create(Rx,Ry,0);
	return (new_cam);
}

int			add_camera(char **tab)
{
	t_obj *obj;

	obj = (t_obj *)malloc(sizeof(t_obj));
	obj->type = ft_strdup(tab[0]);
	obj->details = (void *)new_camera(tab);
	ft_lstadd_back(&g_rt.cameras, ft_lstnew(obj));
	return (1);
}
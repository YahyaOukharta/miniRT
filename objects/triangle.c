#include "objects.h"
#include "../minirt.h"

extern struct s_minirt g_rt;

t_triangle	*new_triangle(char **info)
{
	t_triangle	*new_triangle;
	char		**tab;

	new_triangle = (t_triangle *)malloc(sizeof(t_triangle));
	tab = ft_split(info[1], ',');
	new_triangle->p1.x = ft_atof(tab[0]);
	new_triangle->p1.y = ft_atof(tab[1]);
	new_triangle->p1.z = ft_atof(tab[2]);
	free_s_tab(tab);
	tab = ft_split(info[2], ',');
	new_triangle->p2.x = ft_atof(tab[0]);
	new_triangle->p2.y = ft_atof(tab[1]);
	new_triangle->p2.z = ft_atof(tab[2]);
	free_s_tab(tab);
	tab = ft_split(info[3], ',');
	new_triangle->p3.x = ft_atof(tab[0]);
	new_triangle->p3.y = ft_atof(tab[1]);
	new_triangle->p3.z = ft_atof(tab[2]);
	free_s_tab(tab);
	new_triangle->color = rgb_to_int(info[4]);
	return (new_triangle);
}

int			add_triangle(char **tab)
{
	t_obj *obj;

	obj = (t_obj *)malloc(sizeof(t_obj));
	obj->type = ft_strdup(tab[0]);
	obj->details = (void *)new_triangle(tab);
	ft_lstadd_back(&g_rt.objects, ft_lstnew(obj));
	return (1);
}

int			transform_triangle(int key, void *param)
{
	t_triangle	*tri;
	t_cam		*cam;
	t_vector	dir;

	tri = (t_triangle *)g_rt.selected_object->details;
	cam = (t_cam *)((t_obj *)g_rt.curr_cam->content)->details;
	if (key == KEY_D || key == KEY_A)
	{
		dir = vec_mult(vec_rotate(vec_create(1, 0, 0), cam->rot),
				(key == KEY_D ? 1 : -1) * TRANS_VEL);
		tri->p1 = vec_add(tri->p1, dir);
		tri->p2 = vec_add(tri->p2, dir);
		tri->p3 = vec_add(tri->p3, dir);
	}
	if (key == KEY_W || key == KEY_S)
	{
		dir = vec_mult(vec_rotate(vec_create(0, 1, 0), cam->rot),
				(key == KEY_D ? 1 : -1) * TRANS_VEL);
		tri->p1 = vec_add(tri->p1, dir);
		tri->p2 = vec_add(tri->p2, dir);
		tri->p3 = vec_add(tri->p3, dir);
	}
	return (0);
}

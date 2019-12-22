#include "menu.h"

extern struct s_minirt g_rt;
#define PRECISION 2

void init_obj_details()
{
	g_obj_details[0] = get_cam_details;
	g_obj_details[1] = get_light_details;
	g_obj_details[2] = get_sphere_details;
	g_obj_details[3] = get_plane_details;
	g_obj_details[4] = get_square_details;
	g_obj_details[5] = get_cylinder_details;
	g_obj_details[6] = get_triangle_details;
}

char **get_light_details(t_obj *obj)
{
	int n_details = 4;
	t_light *light = (t_light *)obj->details;
	char **tab = (char **)malloc(sizeof(char *) * (n_details + 1));
	tab[0] = ft_strdup("Type = Light");
	tab[1] = ft_strjoin_va(7,"Pos = (",ft_ftoa(light->pos.x, PRECISION),",",ft_ftoa(light->pos.y, PRECISION),",",ft_ftoa(light->pos.z, PRECISION),")");
	tab[2] = ft_strjoin_va(2,"brightness = (",ft_ftoa(light->brightness, PRECISION));
	tab[3] = ft_strjoin_va(2,"Color = ",ft_itoa(light->color));
	tab[4] = 0;
	return (tab);
}

char **get_cam_details(t_obj *obj)
{
	int n_details = 4; //type pos dir fov;
	t_cam *cam = (t_cam *)obj->details;
	t_vector dir = vec_rotate(vec_create(0,0,-1),cam->rot);
	char **tab = (char **)malloc(sizeof(char *) * (n_details + 1));
	tab[0] = ft_strdup("Type = Camera");
	tab[1] = ft_strjoin_va(7,"Pos = (",ft_ftoa(cam->pos.x, PRECISION),",",ft_ftoa(cam->pos.y, PRECISION),",",ft_ftoa(cam->pos.z, PRECISION),")");
	tab[2] = ft_strjoin_va(7,"Dir = (",ft_ftoa(dir.x, PRECISION),",",ft_ftoa(dir.y, PRECISION),",",ft_ftoa(dir.z, PRECISION),")");
	tab[3] = ft_strjoin_va(2,"FOV = ",ft_itoa(cam->fov));
	tab[4] = 0;
	return (tab);
}

char **get_sphere_details(t_obj *obj)
{
	int n_details = 4; //type pos radius color
	t_sphere *sph = (t_sphere *)obj->details;
	char **tab = (char **)malloc(sizeof(char *) * (n_details + 1));
	tab[0] = ft_strdup("Type = Sphere");
	tab[1] = ft_strjoin_va(7,"Pos = (",ft_ftoa(sph->pos.x, PRECISION),",",ft_ftoa(sph->pos.y, PRECISION),",",ft_ftoa(sph->pos.z, PRECISION),")");
	tab[2] = ft_strjoin_va(2,"Radius = ",ft_ftoa(sph->diameter / 2, PRECISION));
	tab[3] = ft_strjoin_va(2,"Color = ",ft_itoa(sph->color));
	tab[4] = 0;

	return (tab);
}

char **get_plane_details(t_obj *obj)
{
	int n_details;
	t_plane *plane;
	char **tab;

	n_details = 4;
	plane = (t_plane *)obj->details;
	tab = (char **)malloc(sizeof(char *) * (n_details + 1));
	tab[0] = ft_strdup("Type = Plane");
	tab[1] = ft_strjoin_va(7, "Pos = (", ft_ftoa(plane->pos.x, PRECISION),
		",", ft_ftoa(plane->pos.y, PRECISION), ",",
		ft_ftoa(plane->pos.z, PRECISION), ")");
	tab[2] = ft_strjoin_va(7, "Dir = (", ft_ftoa(plane->orientation.x,
		PRECISION), ",", ft_ftoa(plane->orientation.y, PRECISION), ",",
		ft_ftoa(plane->orientation.z, PRECISION), ")");
	tab[3] = ft_strjoin_va(2, "Color = ", ft_itoa(plane->color));
	tab[4] = 0;
	return (tab);
}

char **get_cylinder_details(t_obj *obj)
{
	int n_details = 6; //type pos dir diameter height color
	t_cylinder *cylinder = (t_cylinder *)obj->details;
	char **tab = (char **)malloc(sizeof(char *) * (n_details + 1));
	tab[0] = ft_strdup("Type = cylinder");
	tab[1] = ft_strjoin_va(7,"Pos = (",ft_ftoa(cylinder->pos.x, PRECISION),",",ft_ftoa(cylinder->pos.y, PRECISION),",",ft_ftoa(cylinder->pos.z, PRECISION),")");
	tab[2] = ft_strjoin_va(7,"Dir = (",ft_ftoa(cylinder->orientation.x, PRECISION),",",ft_ftoa(cylinder->orientation.y, PRECISION),",",ft_ftoa(cylinder->orientation.z, PRECISION),")");
	tab[3] = ft_strjoin_va(4,"Radius = ",ft_ftoa(cylinder->diameter / 2,PRECISION)," Height = ",ft_ftoa(cylinder->height,PRECISION));
	tab[4] = ft_strjoin_va(2,"Color = ",ft_itoa(cylinder->color));
	tab[5] = 0;
	return (tab);
}

char **get_triangle_details(t_obj *obj)
{
	int n_details = 5; //type p1 p2 p3 color
	t_triangle *tri = (t_triangle *)obj->details;
	char **tab = (char **)malloc(sizeof(char *) * (n_details + 1));
	tab[0] = ft_strdup("Type = Triangle");
	tab[1] = ft_strjoin_va(7,"P1 = (",ft_ftoa(tri->p1.x, PRECISION),",",ft_ftoa(tri->p1.y, PRECISION),",",ft_ftoa(tri->p1.z, PRECISION),")");
	tab[2] = ft_strjoin_va(7,"P2 = (",ft_ftoa(tri->p2.x, PRECISION),",",ft_ftoa(tri->p2.y, PRECISION),",",ft_ftoa(tri->p2.z, PRECISION),")");
	tab[3] = ft_strjoin_va(7,"P3 = (",ft_ftoa(tri->p3.x, PRECISION),",",ft_ftoa(tri->p3.y, PRECISION),",",ft_ftoa(tri->p3.z, PRECISION),")");
	tab[4] = ft_strjoin_va(2,"Color = ",ft_itoa(tri->color));
	tab[5] = 0;
	return (tab);
}   

char **get_square_details(t_obj *obj)
{
	int n_details = 5; //type pos dir side_size color
	t_square *square = (t_square *)obj->details;
	char **tab = (char **)malloc(sizeof(char *) * (n_details + 1));
	tab[0] = ft_strdup("Type = Square");
	tab[1] = ft_strjoin_va(7,"Pos = (",ft_ftoa(square->pos.x, PRECISION),",",ft_ftoa(square->pos.y, PRECISION),",",ft_ftoa(square->pos.z, PRECISION),")");
	tab[2] = ft_strjoin_va(7,"Dir = (",ft_ftoa(square->orientation.x, PRECISION),",",ft_ftoa(square->orientation.y, PRECISION),",",ft_ftoa(square->orientation.z, PRECISION),")");
	tab[3] = ft_strjoin_va(2,"Side size = ",ft_ftoa(square->side_size, PRECISION));
	tab[4] = ft_strjoin_va(2,"Color = ",ft_itoa(square->color));
	tab[5] = 0;
	return (tab);
}

int init_menu()
{
	g_rt.g_menu.w = 300;
	g_rt.g_menu.opacity = 0.6;
	init_obj_details();
	return (1);
}

char **get_obj_details(t_obj *obj)
{
	int index;
	index = index_of_in_tab(obj->type, ft_split(g_rt.g_supported_objects,';')) - 2;
	return (g_obj_details[index](obj));
}

int print_cam_obj_instructions()
{
	char *title,*move,*rot,*change,*obj_scroll,*obj_select,*obj_move;
	title = "// Instructions //";
	change = (g_rt.selected_object ? "-> Press C to unselect object" : "-> Press C to change camera");
	move = ft_strjoin("-> Press WASD to move ",(g_rt.selected_object ? "object" : "camera"));
	rot = ft_strjoin("-> Press Arrow keys to rotate ",(g_rt.selected_object ? "object" : "camera"));
	obj_scroll = (g_rt.selected_object ? "-> Scroll mouse to resize object" : "");;
	obj_select = (g_rt.selected_object ? "Selected object details: " : "Click to select object from scene");

	int i = 0;
	if (g_rt.g_menu.on)
	{   // centered
		mlx_string_put(g_rt.data.mlx_ptr, g_rt.data.mlx_win, g_rt.g_menu.w / 2 - ft_strlen(title) * FONT_WIDTH / 3,40, rgb_to_int("255,255,255"), title);
		// instructions  
		mlx_string_put(g_rt.data.mlx_ptr, g_rt.data.mlx_win, g_rt.g_menu.w / 8,90, rgb_to_int("255,255,255"), change);
		mlx_string_put(g_rt.data.mlx_ptr, g_rt.data.mlx_win, g_rt.g_menu.w / 8,110, rgb_to_int("255,255,255"), move);
		mlx_string_put(g_rt.data.mlx_ptr, g_rt.data.mlx_win, g_rt.g_menu.w / 8,130, rgb_to_int("255,255,255"), rot);
		mlx_string_put(g_rt.data.mlx_ptr, g_rt.data.mlx_win, g_rt.g_menu.w / 8,150, rgb_to_int("255,255,255"), obj_scroll);
	}
	return (0);
}

int print_light_instructions()
{
	char *title,*move,*rot,*change,*obj_scroll,*obj_select,*obj_move;
	title = "// Instructions //";
	change = "-> Press C to exit light edit mode";
	move = "-> Press WASD to move light";
	rot = "-> Click on objects to add light";
	obj_scroll = "-> Scroll to move light along Z axis";
	obj_select = "Selected object details:";

	int i = 0;
	if (g_rt.g_menu.on)
	{   // centered
		mlx_string_put(g_rt.data.mlx_ptr, g_rt.data.mlx_win, g_rt.g_menu.w / 2 - ft_strlen(title) * FONT_WIDTH / 3,40, rgb_to_int("255,255,255"), title);
		// instructions  
		mlx_string_put(g_rt.data.mlx_ptr, g_rt.data.mlx_win, g_rt.g_menu.w / 8,90, rgb_to_int("255,255,255"), change);
		mlx_string_put(g_rt.data.mlx_ptr, g_rt.data.mlx_win, g_rt.g_menu.w / 8,110, rgb_to_int("255,255,255"), move);
		mlx_string_put(g_rt.data.mlx_ptr, g_rt.data.mlx_win, g_rt.g_menu.w / 8,130, rgb_to_int("255,255,255"), obj_scroll);
		mlx_string_put(g_rt.data.mlx_ptr, g_rt.data.mlx_win, g_rt.g_menu.w / 8,150, rgb_to_int("255,255,255"), rot);
	}
	return (0);
}

int show_menu()
{   char *camera,*light;
	char **obj_details;
	char **cam_details;
	char *obj_scroll = (g_rt.selected_object ? "-> Scroll mouse to resize object" : "");;
	char *obj_select = (g_rt.selected_object ? "Selected object details: " : "Click to select object from scene");
	camera = "Current camera details:";
	light = (g_rt.current_light ? "-> Press L to edit next light" : "-> Press L to edit lights");
	int i = 0;
	if (g_rt.g_menu.on)
	{   // centered
		if (g_rt.current_light)
			print_light_instructions();
		else
			print_cam_obj_instructions();
		// objects
		mlx_string_put(g_rt.data.mlx_ptr, g_rt.data.mlx_win, g_rt.g_menu.w / 7,180, rgb_to_int("255,255,255"), obj_select);
		if (g_rt.selected_object)
		{
			obj_details = get_obj_details(g_rt.selected_object);
			while (obj_details[i])
			{
				mlx_string_put(g_rt.data.mlx_ptr, g_rt.data.mlx_win, g_rt.g_menu.w / 4,200 + i * 20, rgb_to_int("255,255,255"), obj_details[i]);
				i++;
			}
			free_s_tab(obj_details);
		}
		//current camera
		i = 1;
		mlx_string_put(g_rt.data.mlx_ptr, g_rt.data.mlx_win, g_rt.g_menu.w / 7,300, rgb_to_int("255,255,255"), camera);
		cam_details = get_obj_details((t_obj *)g_rt.curr_cam->content);
		while (cam_details[i])
		{
			mlx_string_put(g_rt.data.mlx_ptr, g_rt.data.mlx_win, g_rt.g_menu.w / 4,320 + (i - 1) * 20, rgb_to_int("255,255,255"), cam_details[i]);
			i++;
		}
		free_s_tab(cam_details);
		mlx_string_put(g_rt.data.mlx_ptr, g_rt.data.mlx_win, g_rt.g_menu.w / 8, 400, rgb_to_int("255,255,255"), light);
		mlx_string_put(g_rt.data.mlx_ptr, g_rt.data.mlx_win, g_rt.g_menu.w / 8, 420, rgb_to_int("255,255,255"), "-> Press P to save as bitmap");
	}
	return (1);
}

int menu_toggle_msg()
{
	mlx_string_put(g_rt.data.mlx_ptr, g_rt.data.mlx_win, g_rt.g_res.x - 150,
		g_rt.g_res.y - 22, rgb_to_int("255,255,255"), (g_rt.g_menu.on ?
		"Press M to hide menu" : "Press M to show menu"));
	mlx_string_put(g_rt.data.mlx_ptr, g_rt.data.mlx_win, g_rt.g_res.x - 150,
		g_rt.g_res.y - 10, rgb_to_int("255,255,255"), "Press ESC to quit");
	return (1);
}

int	selected_objects_msg()
{
	char	*str;
	int		n;

	str = (g_rt.selected_object ? g_rt.selected_object->type : "(null)");
	if (g_rt.selected_object && !ft_memcmp(g_rt.selected_object->type,
		"l", max(ft_strlen(g_rt.selected_object->type), 1)))
	{
		n = ft_lstsize(g_rt.lights) - ft_lstsize(g_rt.current_light);
		str = ft_strjoin("Selected light = L", ft_itoa(n + 1));
	}
	else
		str = ft_strjoin("Selected object = ", str);
	mlx_string_put(g_rt.data.mlx_ptr, g_rt.data.mlx_win, g_rt.g_res.x - 180,
		34, rgb_to_int("255,255,255"), str);
	n = ft_lstsize(g_rt.cameras) - ft_lstsize(g_rt.curr_cam);
	str = ft_strjoin("Current camera  = C", ft_itoa(n + 1));
	mlx_string_put(g_rt.data.mlx_ptr, g_rt.data.mlx_win, g_rt.g_res.x - 180,
		20, rgb_to_int("255,255,255"), str);
	return (1);
}

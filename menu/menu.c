#include "menu.h"

extern struct    data_s data;
extern struct    s_resolution g_resolution;
extern char *g_supported_objects;
extern struct s_menu g_menu;
extern struct s_object *selected_object;
extern t_list *current_camera;
#define PRECISION 2

void init_obj_details()
{
    g_obj_details[0] = get_camera_details;
//    g_obj_details[1] = get_light_details;
    g_obj_details[2] = get_sphere_details;
    g_obj_details[3] = get_plane_details;
//    g_obj_details[4] = get_square_details;
//    g_obj_details[5] = get_cylinder_details;
    g_obj_details[6] = get_triangle_details;

}
char **get_camera_details(t_object *obj)
{
    int n_details = 4; //type pos dir fov;
    t_camera *cam = (t_camera *)obj->details;
    t_vector dir = vec_rotate(vec_create(0,0,-1),cam);
    char **tab = (char **)malloc(sizeof(char *) * (n_details + 1));
    tab[0] = ft_strdup("Type = Camera");
    tab[1] = ft_strjoin_va(7,"Pos = (",ft_ftoa(cam->pos.x, PRECISION),",",ft_ftoa(cam->pos.y, PRECISION),",",ft_ftoa(cam->pos.z, PRECISION),")");
    tab[2] = ft_strjoin_va(7,"Dir = (",ft_ftoa(dir.x, PRECISION),",",ft_ftoa(dir.y, PRECISION),",",ft_ftoa(dir.z, PRECISION),")");
    tab[3] = ft_strjoin_va(2,"fov = ",ft_itoa(cam->fov));
    tab[4] = 0;
    return (tab);
}
char **get_sphere_details(t_object *obj)
{
    int n_details = 4; //type pos radius color
    t_sphere *sph = (t_sphere *)obj->details;
    char **tab = (char **)malloc(sizeof(char *) * (n_details + 1));
    tab[0] = ft_strdup("Type = Sphere");
    tab[1] = ft_strjoin_va(7,"Pos = (",ft_ftoa(sph->pos.x, PRECISION),",",ft_ftoa(sph->pos.y, PRECISION),",",ft_ftoa(sph->pos.z, PRECISION),")");
    tab[2] = ft_strjoin_va(2,"Radius = ",ft_ftoa(sph->diameter / 2, PRECISION));
    tab[3] = ft_strjoin_va(2,"color = ",ft_itoa(sph->color));
    tab[4] = 0;

    return (tab);
}
char **get_plane_details(t_object *obj)
{
    int n_details = 3; //type pos radius
    t_plane *plane = (t_plane *)obj->details;
    char **tab = (char **)malloc(sizeof(char *) * (n_details + 1));
    tab[0] = ft_strdup("Type = Plane");
    tab[1] = ft_strjoin_va(7,"Pos = (",ft_ftoa(plane->pos.x, PRECISION),",",ft_ftoa(plane->pos.y, PRECISION),",",ft_ftoa(plane->pos.z, PRECISION),")");
    tab[2] = ft_strjoin_va(7,"Dir = (",ft_ftoa(plane->orientation.x, PRECISION),",",ft_ftoa(plane->orientation.y, PRECISION),",",ft_ftoa(plane->orientation.z, PRECISION),")");
    tab[3] = ft_strjoin_va(2,"color = ",ft_itoa(plane->color));
    tab[4] = 0;
    return (tab);
}
char **get_triangle_details(t_object *obj)
{
    int n_details = 3; //type p1 p2 p3
    t_triangle *tri = (t_triangle *)obj->details;
    char **tab = (char **)malloc(sizeof(char *) * (n_details + 1));
    tab[0] = ft_strdup("Type = triangle");
    tab[1] = ft_strjoin_va(7,"P1 = (",ft_ftoa(tri->p1.x, PRECISION),",",ft_ftoa(tri->p1.y, PRECISION),",",ft_ftoa(tri->p1.z, PRECISION),")");
    tab[2] = ft_strjoin_va(7,"P2 = (",ft_ftoa(tri->p2.x, PRECISION),",",ft_ftoa(tri->p2.y, PRECISION),",",ft_ftoa(tri->p2.z, PRECISION),")");
    tab[3] = ft_strjoin_va(7,"P3 = (",ft_ftoa(tri->p3.x, PRECISION),",",ft_ftoa(tri->p3.y, PRECISION),",",ft_ftoa(tri->p3.z, PRECISION),")");
    tab[4] = 0;
    return (tab);
}   
int init_menu()
{
    g_menu.menu_w = 300;
    g_menu.opacity = 0.6;
    init_obj_details();
    return (1);
}
char **get_object_details(t_object *obj)
{
    int index;
    index = index_of_in_tab(obj->type, ft_split(g_supported_objects,';')) - 2;
    return (g_obj_details[index](obj));
}

int show_menu()
{
    char *title,*move,*rot,*change,*obj_scroll,*obj_select,*obj_move,**obj_details,*camera,**cam_details;
    title = "Instructions";
    change = (selected_object ? "-> Press C to unselect object" : "-> Press C to change camera");
    move = ft_strjoin("-> Press WASD to move ",(selected_object ? "object" : "camera"));
    rot = ft_strjoin("-> Press Arrow keys to rotate ",(selected_object ? "object" : "camera"));
    obj_scroll = (selected_object ? "-> Scroll mouse to resize object" : "");;

    obj_select = (selected_object ? "Selected object details: " : "Click to select object from scene");
    camera = "Current camera details:";
    int i = 0;
    if (g_menu.on)
    {   // centered
        mlx_string_put(data.mlx_ptr, data.mlx_win, g_menu.menu_w / 2 - ft_strlen(title) * FONT_WIDTH / 3,40, rgb_to_int("255,255,255"), title);
        // instructions  
        mlx_string_put(data.mlx_ptr, data.mlx_win, g_menu.menu_w / 8,90, rgb_to_int("255,255,255"), change);
        mlx_string_put(data.mlx_ptr, data.mlx_win, g_menu.menu_w / 8,110, rgb_to_int("255,255,255"), move);
        mlx_string_put(data.mlx_ptr, data.mlx_win, g_menu.menu_w / 8,130, rgb_to_int("255,255,255"), rot);
        mlx_string_put(data.mlx_ptr, data.mlx_win, g_menu.menu_w / 8,150, rgb_to_int("255,255,255"), obj_scroll);
        // objects
        mlx_string_put(data.mlx_ptr, data.mlx_win, g_menu.menu_w / 7,180, rgb_to_int("255,255,255"), obj_select);
        if (selected_object)
        {
            obj_details = get_object_details(selected_object);
            while (obj_details[i])
            {
                mlx_string_put(data.mlx_ptr, data.mlx_win, g_menu.menu_w / 4,200 + i * 20, rgb_to_int("255,255,255"), obj_details[i]);
                i++;
            }
        }
        //current camera
        i = 1;
        mlx_string_put(data.mlx_ptr, data.mlx_win, g_menu.menu_w / 7,300, rgb_to_int("255,255,255"), camera);
        cam_details = get_object_details((t_object *)current_camera->content);
        while (cam_details[i])
        {
            mlx_string_put(data.mlx_ptr, data.mlx_win, g_menu.menu_w / 4,320 + (i - 1) * 20, rgb_to_int("255,255,255"), cam_details[i]);
            i++;
        }
    }
    return (1);
}

int menu_toggle_msg()
{
    mlx_string_put(data.mlx_ptr, data.mlx_win, g_resolution.x - 150, g_resolution.y - 10,
        rgb_to_int("255,255,255"), (g_menu.on ? "Press M to hide menu" : "Press M to show menu"));
    return (1);
}
int selected_objects_msg()
{
    mlx_string_put(data.mlx_ptr, data.mlx_win, g_resolution.x - 180,20,
        rgb_to_int("255,255,255"), ft_strjoin("Selected Object = ",(selected_object ? selected_object->type : "(null)")));
    return (1);
}
#include "menu.h"

extern struct    data_s data;
extern struct    s_resolution g_resolution;
extern struct s_menu g_menu;
int init_menu()
{
    g_menu.menu_w = 240;
    g_menu.opacity = 0.6;
    return (1);
}

int show_menu()
{
    char *title,*cam_move,*cam_rot;
    title = "miniRT";
    cam_move = "WASD to move camera";
    cam_rot = "Arrow keys to rotate camera";
    if (g_menu.on)
    {// centered
        mlx_string_put(data.mlx_ptr, data.mlx_win, g_menu.menu_w / 2 - ft_strlen(title) * FONT_WIDTH / 3,40, rgb_to_int("255,255,255"), title);
        mlx_string_put(data.mlx_ptr, data.mlx_win, g_menu.menu_w / 2 - ft_strlen(cam_move) * FONT_WIDTH / 3,60, rgb_to_int("255,255,255"), cam_move);
        mlx_string_put(data.mlx_ptr, data.mlx_win, g_menu.menu_w / 2 - ft_strlen(cam_rot) * FONT_WIDTH / 3,80, rgb_to_int("255,255,255"), cam_rot);
    }
    return (1);
}

int menu_toggle_msg()
{
    mlx_string_put(data.mlx_ptr,data.mlx_win, g_resolution.x - 150,g_resolution.y - 10,
        rgb_to_int("255,255,255"), (g_menu.on ? "Press M to hide menu" : "Press M to show menu"));
    return (1);
}
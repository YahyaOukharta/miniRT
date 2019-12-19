#ifndef MINIRT_H
# define MINIRT_H
# include "mlx.h"
# include "keys.h"
# include "utils/utils.h"
# include "file_checker/file_checker.h"
# include "objects/objects.h"
# include "vector_math/vector_math.h"
# include "rays_and_intersections/ray.h"
# include <fcntl.h>
# include <math.h>
# include "gnl/get_next_line.h"
# include "ft_printf/ft_printf.h"
# include "object_printer/obj_printer.h"
# include "menu/menu.h"
# define FONT_WIDTH 10
# define FONT_HEIGHT 20

typedef struct					s_data
{
	void						*mlx_ptr;
	void						*mlx_win;
	int							bpp;
	int							size_line;
	int							endian;
	int							*img_data;
	void						*img_ptr;
}								t_data;

typedef struct					s_menu
{
	int							on;
	int							menu_w;
	float						opacity;
}								t_menu;

typedef struct					s_minirt
{
	t_data						data;
	char						*g_supported_objects;
	struct s_menu				g_menu;
	struct s_resolution			g_resolution;
	struct s_ambient_light		g_ambient_light;
	t_list						*objects;
	t_list						*lights;
	t_list						*current_light;
	t_list						*cameras;
	t_list						*current_camera;
	struct s_object				*selected_object;
}								t_minirt;
typedef struct s_ray			t_ray;
typedef struct s_intersection	t_intersection;

int								get_ambient_color(t_intersection *closest);
int								get_diffuse_color(t_intersection *closest,
									t_ray shadow_ray,
									t_light *light);
int								get_specular_color(t_intersection *closest,
									t_ray ray, t_ray shadow_ray,
									t_light *light);
void							init_objects(void);
int								re_render(int key, void *param);
int								rotate_camera(int key, void *param);
int								move_camera(int key, void *param);
int								change_camera(int key, void *param);
int								transform_object(int key, void *param);
int								toggle_menu(int key, void *param);
int								edit_lights(int key, void *param);
int								save_frame(int key, void *param);
int								handle_keys(int key, void *param);
int								select_object(int button,
									int x, int y, void *param);
int								resize_object(int btn,
									int x, int y, void *param);
int								move_light_z(int btn,
									int x, int y, void *param);
int								add_new_light(int button,
									int x, int y, void *param);
int								handle_mouse(int button,
									int x, int y, void *param);
t_intersection					*get_closest_intersection(t_list *objects,
									t_ray ray);
int								is_ray_blocked(t_ray shadow_ray);
int								compute_pixel_color(t_intersection *closest,
									t_ray ray, t_list *lights);
t_ray							cast_ray(int x, int y,
									t_camera *cam, float zoom);
int								render(int part);
#endif

#ifndef MINIRT_H
# define MINIRT_H

#include "mlx.h"
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

#define FONT_WIDTH	10
#define	FONT_HEIGHT	20

//mlx struct
typedef struct    data_s
{
    void          *mlx_ptr;
    void          *mlx_win;
}                 data_t;
typedef struct    s_menu
{
    int on;
    int menu_w;
    float opacity;
}               t_menu;
void init_objects(void);
#endif
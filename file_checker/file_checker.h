#ifndef FILE_CHECKER_H
# define FILE_CHECKER_H

#include "../utils/utils.h"

int check_info_resolution(char **tab);

int check_info_ambient_light(char **tab);

int check_info_camera(char **tab);

int check_info_light(char **tab);

int check_info_sphere(char **tab);

int check_info_plane(char **tab);

int check_info_square(char **tab);

int check_info_cylinder(char **tab);

int check_info_triangle(char **tab);

typedef int(*t_checker)(char **);

t_checker g_file_checker[10];

void init_file_checker(){
    g_file_checker[0] = check_info_resolution;
    g_file_checker[1] = check_info_ambient_light;
    g_file_checker[2] = check_info_camera;
    g_file_checker[3] = check_info_light;
    g_file_checker[4] = check_info_sphere;
    g_file_checker[5] = check_info_plane;
    g_file_checker[6] = check_info_square;
    g_file_checker[7] = check_info_cylinder;
    g_file_checker[8] = check_info_triangle;
}
#endif
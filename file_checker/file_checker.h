#ifndef FILE_CHECKER_H
# define FILE_CHECKER_H

#include "../minirt.h"

int check_info_resolution(char **tab, int n);
int check_info_ambient_light(char **tab, int n);
int check_info_camera(char **tab, int n);
int check_info_light(char **tab, int n);
int check_info_sphere(char **tab, int n);
int check_info_plane(char **tab, int n);
int check_info_square(char **tab, int n);
int check_info_cylinder(char **tab, int n);
int check_info_triangle(char **tab, int n);

typedef int(*t_checker)(char **, int);
t_checker g_file_checker[10];

void init_file_checker(void);

#endif
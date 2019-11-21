#ifndef __UTILS_H__
# define __UTILS_H__
# include "../minirt.h"
int min(int a, int b);
int max(int a, int b);

int is_int(char *s);
int is_float(char *s);
int is_color(char *s);
int is_pos_vector(char *s);
int is_norm_dir_vector(char *s);

int tab_len(char **tab);
int exists_in_tab(char *s,char **tab);
int index_of_in_tab(char *s, char **tab);

int rgb_to_int(char *rgb);

float ft_atof(const char *str);
#endif
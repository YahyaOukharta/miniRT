#include "utils.h"


int min(int a, int b)
{
    return (a < b ? a : b);
}
int max(int a, int b)
{
    return (a > b ? a : b);
}
int tab_len(char **tab)
{
	int i;
	
	i = 0;
	while (tab[i])
		i++;
	return (i);
}

int exists_in_tab(char *s,char **tab)
{
    while (*tab)
    {
        if (!ft_strncmp(s, *tab, max(ft_strlen(s), ft_strlen(*tab))))
            return (1);
        tab++;
    }
    return (0);
}

int index_of_in_tab(char *s, char **tab)
{
    int i;

    i = 0;
    while (tab[i])
    {
        if (!ft_strncmp(s, tab[i], max(ft_strlen(s), ft_strlen(tab[i]))))
            return (i);
        i++;
    }
    return (-1);
}

int is_int(char *str)
{
    if(*str == '-')
        str++;
    while (*str)
    {
        if(!ft_isdigit(*str))
            return (0);
        str++;
    }
    return (1);
}
int is_float(char *str)
{
    int f;

    f = 0;
    if(*str == '-')
    str++;
    while (*str)
    {
        if (!ft_isdigit(*str))
        {
            if (*str == '.' && !f)
                f = 1;
            else
                return (0);
        }
        str++;
    }
    return (1);
}

int how_many_in(char c, char *str)
{
    int i;
    i = 0;
    while (*str)
    {
        if (*str == c)
            i++;
        str++;
    }
    return (i);
}

int is_color(char *str)
{
    char **tab;

    if (how_many_in(',',str) != 2)
        return (0);
    tab = ft_split(str, ',');
    if (tab_len(tab) != 3)
        return (0);
    while (*tab)
    {
        if (!is_int(*tab) || ft_atoi(*tab) < 0 || ft_atoi(*tab) > 255)
            return(0);
        tab++;
    }
    return (1);
}

int is_pos_vector(char *str)
{
    char **tab;

    if (how_many_in(',',str) != 2)
        return (0);
    tab = ft_split(str, ',');
    if (tab_len(tab) != 3)
        return (0);
    while (*tab)
    {
        if (!is_float(*tab))
            return(0);
        tab++;
    }
    return (1);
}

int is_norm_dir_vector(char *str)
{
    char **tab;

    if (how_many_in(',',str) != 2)
        return (0);
    tab = ft_split(str, ',');
    if (tab_len(tab) != 3)
        return (0);
    while (*tab)
    {
        if (!is_float(*tab) || ft_atof(*tab) < -1 || ft_atof(*tab) > 1)
            return(0);
        tab++;
    }
    return (1);
}
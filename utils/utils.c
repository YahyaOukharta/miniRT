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

    if (!ft_strchr(str, '.'))
        return (is_int(str));
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

int free_s_tab(char **tab)
{
    int i;

    i = 0;
    if (tab)
    {
        while (tab[i])
        {
            free(tab[i]);
            i++;
        }
        free(tab);
    }
    return (0);
}

int is_color(char *str)
{
    char **tab;
    int i;

    i = 0;
    if (how_many_in(',',str) != 2)
        return (0);
    tab = ft_split(str, ',');
    if (tab_len(tab) != 3)
    {
        free_s_tab(tab);
        return (0);
    }
    while (tab[i])
    {
        if (!is_int(tab[i]) || ft_atoi(tab[i]) < 0 || ft_atoi(tab[i]) > 255)
        {
            free_s_tab(tab);
            return (0);
        }
        i++;
    }
    free_s_tab(tab);
    return (1);
}

int is_pos_vector(char *str)
{
    char **tab;
    int i;

    i = 0;
    if (how_many_in(',',str) != 2)
        return (0);
    tab = ft_split(str, ',');
    if (tab_len(tab) != 3)
        return (0);
    while (tab[i])
    {
        if (!is_float(tab[i]))
        {
            free_s_tab(tab);
            return(0);}
        i++;
    }
    free_s_tab(tab);
    return (1);
}

int is_norm_dir_vector(char *str)
{
    char **tab;
    int i;

    i = 0;
    if (how_many_in(',',str) != 2)
        return (0);
    tab = ft_split(str, ',');
    if (tab_len(tab) != 3)
    {
        free_s_tab(tab);
        return (0);
    }
    while (tab[i])
    {
        if (!is_float(tab[i]) || ft_atof(tab[i]) < -1.0 || ft_atof(tab[i]) > 1.0)
        {
            free_s_tab(tab);
            return(0);
        }
        i++;
    }
    free_s_tab(tab);
    return (1);
}

int rgb_to_int(char *s)
{
    char **tab;
    char **tmp;
    int res;

    tab = ft_split(s, ',');
    tmp = tab;
    res = 0;
    while (*tab)
    {
        res = res * 256 + ft_atoi(*tab);
        free (*tab);
        tab++; 
    }
    free(tmp);
    return (res);
}

int add_colors(int c1, int c2)
{
    int r1,g1,b1,r2,g2,b2;
    int r3,g3,b3;
    int result;

    b1 = c1 % 256;
    c1 /=256;    
    g1 = c1 % 256;
    c1 /=256;    
    r1 = c1 % 256;
    c1 /=256;
    
    b2 = c2 % 256;
    c2 /=256;    
    g2 = c2 % 256;
    c2 /=256;    
    r2 = c2 % 256;
    c2 /=256;

    // r3 = (r1 + r2) / 2;
    // g3 = (g1 + g2) / 2;
    // b3 = (b1 + b2) / 2;
    
    r3 = min((r1 + r2), 255);
    g3 = min((g1 + g2), 255);
    b3 = min((b1 + b2), 255);

    result = r3 * 256;
    result = (result + g3) * 256;     
    result = result + b3;

    return (result);
}
int mult_colors(int c1, float value)
{
    int r1,g1,b1,r2,g2,b2;
    int r3,g3,b3;
    int result;

    b1 = c1 % 256;
    c1 /=256;    
    g1 = c1 % 256;
    c1 /=256;    
    r1 = c1 % 256;
    c1 /=256;


    
    r3 = r1 * value;
    g3 = g1 * value;
    b3 = b1 * value;

    result = r3 * 256;
    result = (result + g3) * 256;     
    result = result + b3;

    return (result);
}

void free_object(void *object)
{
    t_object *obj;
    char **tmp;
    int index;
    obj = (t_object *)object;
    free(obj->details);
    free(obj->type);
    free(obj);
}
void save_bmp (const char *filename, int w, int h, int dpi, int *image) {
	FILE *f;
	int k = w*h;
	int s = 4*k;
	int filesize = 54 + s;
	
	double factor = 39.375;
	int m = (int)(factor);
	
	int ppm = dpi*m;
	
	unsigned char bmpfileheader[14] = {'B','M', 0,0,0,0, 0,0,0,0, 54,0,0,0};
	unsigned char bmpinfoheader[40] = {40,0,0,0, 0,0,0,0, 0,0,0,0, 1,0,24,0};
	
	bmpfileheader[ 2] = (unsigned char)(filesize);
	bmpfileheader[ 3] = (unsigned char)(filesize>>8);
	bmpfileheader[ 4] = (unsigned char)(filesize>>16);
	bmpfileheader[ 5] = (unsigned char)(filesize>>24);
	
	bmpinfoheader[ 4] = (unsigned char)(w);
	bmpinfoheader[ 5] = (unsigned char)(w>>8);
	bmpinfoheader[ 6] = (unsigned char)(w>>16);
	bmpinfoheader[ 7] = (unsigned char)(w>>24);
	
	bmpinfoheader[ 8] = (unsigned char)(h);
	bmpinfoheader[ 9] = (unsigned char)(h>>8);
	bmpinfoheader[10] = (unsigned char)(h>>16);
	bmpinfoheader[11] = (unsigned char)(h>>24);
	
	bmpinfoheader[21] = (unsigned char)(s);
	bmpinfoheader[22] = (unsigned char)(s>>8);
	bmpinfoheader[23] = (unsigned char)(s>>16);
	bmpinfoheader[24] = (unsigned char)(s>>24);
	
	bmpinfoheader[25] = (unsigned char)(ppm);
	bmpinfoheader[26] = (unsigned char)(ppm>>8);
	bmpinfoheader[27] = (unsigned char)(ppm>>16);
	bmpinfoheader[28] = (unsigned char)(ppm>>24);
	
	bmpinfoheader[29] = (unsigned char)(ppm);
	bmpinfoheader[30] = (unsigned char)(ppm>>8);
	bmpinfoheader[31] = (unsigned char)(ppm>>16);
	bmpinfoheader[32] = (unsigned char)(ppm>>24);
	
	f = fopen(filename,"wb");
	
	fwrite(bmpfileheader,1,14,f);
	fwrite(bmpinfoheader,1,40,f);
	
	for (int i = 0; i < k; i++) {
		int rgb = image[k - i];
		double blue = rgb % 256;
        rgb /= 256;
        double green = rgb % 256;
        rgb /= 256;
		double red = rgb % 256;		
		unsigned char color[3] = {(int)floor(blue),(int)floor(green),(int)floor(red)};
		fwrite(color,1,3,f);
	}
	fclose(f);
}

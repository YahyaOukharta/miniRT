#include "object_liberator.h"

extern char *g_supported_objects;

void free_object(void *object)
{
    t_object *obj;
    char **tmp;
    int index;

    obj = (t_object *)object;
    index = index_of_in_tab(obj->type, (tmp = ft_split(g_supported_objects, ';'))) - 2;
    free_s_tab(tmp);
    free(obj->details);
    free(obj->type);
    free(obj);
}

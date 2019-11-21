
#include "libft.h"

t_list		*ft_lstnew(void *content)
{
	t_list	*list;

	list = malloc(sizeof(t_list));
	if (list)
	{
		list->content = content;
		list->next = NULL;
		return (list);
	}
	return (NULL);
}

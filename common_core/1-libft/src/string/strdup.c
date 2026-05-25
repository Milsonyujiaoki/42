#include "libft.h"

char *ft_strdup(const char *src)
{
	char	*new_str;
	t_usize	len;

	if (!src)
		return (NULL);
	len = ft_strlen(src) + 1;
	new_str = (char *)ft_malloc(len);
	if (!new_str)
		return (NULL);
	ft_memcpy(new_str, src, len);
	return (new_str);
}
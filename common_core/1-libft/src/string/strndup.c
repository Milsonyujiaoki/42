#include "libft.h"

char *ft_strndup(const char *src, size_t count)
{
	char	*new_str;
	t_usize	len;

	if (!src)
		return (NULL);
	len = ft_strlen(src);
	if (len > (t_usize)count)
		len = (t_usize)count;
	new_str = (char *)ft_malloc(len + 1);
	if (!new_str)
		return (NULL);
	ft_memcpy(new_str, src, len);
	new_str[len] = '\0';
	return (new_str);
}
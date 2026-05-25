#include "libft.h"
#include <stddef.h>

char	*ft_strncat(char *dest, const char *src, size_t count)
{
	char	*ptr;

	ptr = dest;
	while (*ptr)
		ptr++;
	while (*src && count > 0)
	{
		*ptr = *src;
		ptr++;
		src++;
		count--;
	}
	*ptr = '\0';
	return (dest);
}
#include "libft.h"

char *ft_strcpy_fast(char *dest, const char *src)
{
	char *start = dest;

	while ((*dest++ = *src++))
	{
	}
	return (start);
}

char *ft_strcpy_v2(char *dest, const char *src)
{
	return (ft_strcpy_fast(dest, src));
}

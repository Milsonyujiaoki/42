#include <string.h>

int	ft_memcmp(const void *lhs, const void *rhs, size_t count)
{
	const unsigned char	*p1;
	const unsigned char	*p2;
	size_t				i;

	p1 = (const unsigned char *)lhs;
	p2 = (const unsigned char *)rhs;
	i = 0;
	while (i < count)
	{
		if (p1[i] != p2[i])
			return (p1[i] - p2[i]);
		i++;
	}
	return (0);
}

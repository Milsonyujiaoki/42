
#include <string.h>

void	*ft_memccpy(void *restrict dest, const void *restrict src,
			int c, size_t count)
{
	unsigned char		*d;
	const unsigned char	*s;
	unsigned char		uc;

	d = (unsigned char *)dest;
	s = (const unsigned char *)src;
	uc = (unsigned char)c;
	while (count--)
	{
		*d = *s;
		if (*d == uc)
			return ((void *)(d + 1));
		d++;
		s++;
	}
	return (NULL);
}

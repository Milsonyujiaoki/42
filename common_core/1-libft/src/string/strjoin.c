#include "libft.h"
#include <stdlib.h>

char	*ft_strjoin(const char *s1, const char *s2)
{
	size_t	len1;
	size_t	len2;
	size_t	i;
	size_t	j;
	char	*result;

	if (!s1 || !s2)
		return (NULL);

	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);

	result = malloc(len1 + len2 + 1);
	if (!result)
		return (NULL);

	i = 0;
	while (s1[i])
	{
		result[i] = s1[i];
		i++;
	}

	j = 0;
	while (s2[j])
	{
		result[i + j] = s2[j];
		j++;
	}

	result[i + j] = '\0';

	return (result);
}
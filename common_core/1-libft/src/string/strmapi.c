#include <libft.h>

char *ft_strmapi(const char *str, char (*f)(unsigned int, char))
{
    if (!str || !f)
        return NULL;

    size_t len = ft_strlen(str);
    char *result = ft_malloc(len + 1);
    if (!result)
        return NULL;

    for (size_t i = 0; i < len; i++)
        result[i] = f(i, str[i]);
    result[len] = '\0';

    return result;
}
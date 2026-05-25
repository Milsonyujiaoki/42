#include "libft.h"


char *ft_strtrim(const char *str, const char *set)
{
    size_t	start;
    size_t	end;
    size_t	len;

    if (!str || !set)
        return (NULL);
    start = 0;
    while (str[start] && ft_strchr(set, str[start]))
        start++;
    end = ft_strlen(str);
    while (end > start && ft_strchr(set, str[end - 1]))
        end--;
    len = end - start;
    return (ft_substr(str, start, len));
}
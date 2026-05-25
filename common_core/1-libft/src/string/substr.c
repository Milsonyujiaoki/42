#include "libft.h"


char *ft_substr(const char *str, unsigned int start, size_t len){
    size_t  str_len;
    char    *substr;

    if (!str)
        return (NULL);
    str_len = ft_strlen(str);
    if (start >= str_len)
        return (ft_strdup(""));
    if (len > str_len - start)
        len = str_len - start;
    substr = ft_strndup(str + start, len);
    return (substr);
}
#include <stdlib.h>
#include "libft.h"

/*
** ft_realloc — wraps the system realloc.
** Future: replace with custom allocator integration.
*/
void    *ft_realloc(void *ptr, t_usize new_size)
{
    if (new_size == 0)
    {
        free(ptr);
        return (NULL);
    }
    return (realloc(ptr, new_size));
}

/*
** ft_realloc_safe — safe realloc that preserves the original
** pointer on allocation failure.
**
** Usage:
**   if (!ft_realloc_safe(&buf, new_size)) { ... OOM handler ... }
*/
void    *ft_realloc_safe(void **ptr, t_usize new_size)
{
    void    *tmp;

    if (!ptr)
        return (NULL);
    tmp = ft_realloc(*ptr, new_size);
    if (!tmp)
        return (NULL);
    *ptr = tmp;
    return (tmp);
}

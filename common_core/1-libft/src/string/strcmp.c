#include "libft.h"

int ft_strcmp(const char *lhs, const char *rhs)
{
    while (*lhs && (*lhs == *rhs))
    {
        lhs++;
        rhs++;
    }
    // Converte cada um para unsigned char PRIMEIRO, depois subtrai
    return ((unsigned char)*lhs - (unsigned char)*rhs);
}
    
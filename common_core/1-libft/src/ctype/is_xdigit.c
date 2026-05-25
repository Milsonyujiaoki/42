#include "libft.h"

int ft_isxdigit(int dg)

{

    return (ft_isdigit(dg) || (dg >= 'a' && dg <= 'f') || (dg >= 'A' && dg <= 'F'));

}
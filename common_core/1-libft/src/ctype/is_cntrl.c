#include "libft.h"

int ft_iscntrl(int ch)

{

    return (ch >= 0 && ch <= 31) || (ch == 127);

}
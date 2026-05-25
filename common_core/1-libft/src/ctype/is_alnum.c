#include "libft.h"

int ft_isalnum(int ch)
{
    return (ft_isupper(ch) || ft_islower(ch) || ft_isdigit(ch));
}

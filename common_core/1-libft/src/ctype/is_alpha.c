#include "libft.h"

int ft_isalpha(int ch){

	return (ft_isupper(ch) || ft_islower(ch));
}

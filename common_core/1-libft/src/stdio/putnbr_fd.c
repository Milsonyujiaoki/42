#include <libft.h>

void ft_putnbr_fd(int n, int fd) {
    char *n_transformed;
    
    if (!fd || fd < 0 || n == 0) {
        return;
    }
    n_transformed = ft_itoa(n);
    ft_putstr_fd(n_transformed, fd);
    ft_free(n_transformed);
}
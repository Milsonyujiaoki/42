#include <libft.h>

void ft_putendl_fd(const char *str, int fd) {
    if (!fd || fd < 0 || !str) {
        return;
    }
    ft_putstr_fd(str, fd);
    ft_putchar_fd('\n', fd);
}
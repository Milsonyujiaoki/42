#include <unistd.h>
#include <libft.h>

void ft_putchar_fd(char c, int fd) {
    if (fd >= 0) {
        if (write(fd, &c, 1) == -1)
            return ;
    }
}
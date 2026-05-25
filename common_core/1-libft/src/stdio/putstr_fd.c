#include <libft.h>

void ft_putstr_fd(const char *s, int fd) {
    if (!s || fd < 0) {
        return;
    }
    // Chame a sua ft_strlen se necessário ou use um loop de ponteiros
    while (*s) {
        ft_putchar_fd(*s, fd);
        s++;
    }
}

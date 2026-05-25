#include <unistd.h>

ssize_t ft_read(int fd, void *buf, size_t count) {
    // Encapsulamento simples e direto
    return read(fd, buf, count);
}

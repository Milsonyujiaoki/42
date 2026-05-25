#include <unistd.h>

ssize_t ft_write(int fd, const void *buf, size_t count) {

    return write(fd, buf, count);
}

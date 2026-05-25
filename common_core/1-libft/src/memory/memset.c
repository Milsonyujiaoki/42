#include <string.h>

void *ft_memset(void *dest, int ch, size_t count) {
    unsigned char *ptr = (unsigned char *)dest;
    while (count--) {
        *ptr++ = (unsigned char)ch;
    }
    return dest;
}

#include <string.h>

void *ft_memchr(const void *ptr, int value, size_t count) {
    const unsigned char *p;
    unsigned char c;

    p = (const unsigned char *)ptr;
    c = (unsigned char)value;

    for (size_t i = 0; i < count; i++) {
        if (p[i] == c) {
            return ((void *)(p + i));
        }
    }
    return (NULL);
}

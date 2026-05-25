#include "libft.h"

int ft_strncmp(const char *lhs, const char *rhs, size_t count) {
    for (size_t i = 0; i < count; i++) {
        if (lhs[i] != rhs[i]) {
            return (unsigned char)lhs[i] - (unsigned char)rhs[i];
        }
        if (lhs[i] == '\0') {
            return 0;
        }
    }
    return 0;
}
#include <stdlib.h>

void ft_exit(int status) {
    // TODO: implement - call exit syscall
    (void)status;
    __builtin_unreachable();
}

#include "libft.h"
#include <string.h>
#include <stdio.h>

int main(void) {
    char buffer[10] = "Olá Yuji";
    printf("Buffer before ft_bzero: %s %p \n", buffer, (void *)buffer);

    ft_bzero(buffer, 4);
    printf("Buffer after ft_bzero: %s %p \n", buffer+4, (void *)(buffer+4));
    printf("%s\n", (ft_memcmp(buffer, "\0\0\0\0 Yuji", 10) == 0) ? "Test passed" : "Test failed");
    return 0;
}  
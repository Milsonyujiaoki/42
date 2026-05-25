#include "libft.h"
#include <string.h>
#include <stdio.h>

int main(void) {
    char buffer[10] = "abcdefghi";
    printf("Buffer before ft_bzero: %s %p \n", buffer, (void *)buffer);
    ft_bzero(buffer, 5);
    printf("Buffer after ft_bzero: %s %p \n", buffer+5, (void *)(buffer+5));

    printf("%s\n", (ft_memcmp(buffer, "\0\0\0\0\0fghi", 10) == 0) ? "Test passed" : "Test failed");

}
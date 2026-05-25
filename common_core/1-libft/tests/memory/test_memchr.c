#include "libft.h"
#include <string.h>
#include <stdio.h>

int main(void) {
    char str[] = "Hello, world!";
    printf("String: %s | Endereço: %p | Tamanho: %zu\n", str, (void *)str, sizeof(str));
    char *result = ft_memchr(str, 'o', sizeof(str));
    if (result) {
        printf("Character found: %c  %p\n", *result, (void *)result);
    } else {
        printf("Character not found.\n");
    }

    return 0;
}

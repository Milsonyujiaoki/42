#include "libft.h"
#include <string.h>
#include <stdio.h>

int main(void) {
    char src[] = "Hello, world!";
    char dest[20] = {0}; // Inicializa com zeros

    void *result = ft_memccpy(dest, src, 'o', sizeof(src));
    if (result) {
        printf("Character found. Destination: %s\n", dest);
    } else {
        printf("Character not found. Destination: %s\n", dest);
    }

    return 0;
}
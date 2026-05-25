#include "libft.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int main(void) {
    char src[] = "Hello, World!";
    char dest[60] = {0}; // Inicializa com zeros para garantir null termination

    ft_strncpy(dest, src, 6); // Copy only the first 6 characters
    dest[6] = '\0'; // Adiciona null terminator explicitamente após a cópia

    printf("Source: %s | Endereço %p\n", src, (void *)src);
    printf("Destination: %s | Endereço %p\n", dest, (void *)dest);

    return 0;
}
#include "libft.h"

#include <string.h>
#include <stdio.h>

int main(void) {
    char src[] = "Hello, World!";
    printf("Source: %s | Endereço: %p | Tamanho: %zu\n", src, (void *)src, sizeof(src));

    char dest[20];
    // Não para no \0. Ela continua a copiar até atingir o número de bytes definido
    ft_memcpy(dest, src, sizeof(src));

    printf("Destino: %s | Endereço: %p | Tamanho: %zu\n", dest, (void *)dest, sizeof(dest));

    return 0;
}
#include "libft.h"
#include <string.h>
#include <stdio.h>

int main(void) {
    //criando um buffer e preenchendo metade dele com 'A' usando ft_memset
    char buffer[21] = {0}; // Inicializa com zeros e adiciona 1 byte extra para null terminator
    size_t metade = (sizeof(buffer) - 1)/2; // -1 para manter o último byte como \0
    ft_memset(buffer, 'A', metade);
    printf("Buffer after memset: %s\n", buffer);

    // preenchendo a outra metade do buffer com 'B' usando ft_memset
    ft_memset(buffer + metade, 'B', metade);
    printf("Buffer after second memset: %s\n", buffer);

   // substituindo o conteúdo do buffer por 'C' usando ft_memset
    ft_memset(buffer, 'C', sizeof(buffer) - 1); // -1 para manter o null terminator
    printf("Buffer after third memset: %s\n", buffer);
    return 0;
}
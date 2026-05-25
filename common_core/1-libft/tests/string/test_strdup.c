#include "libft.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int main(void) {
    const char *original = "Hello, World!";
    //Ao contrário de ft_strcpy e ft_memcpy, tu não precisas de ter um buffer de destino pronto; ela cria um novo para ti
    //Como ela usa malloc, tu é responsável por dar free() nessa memória mais tarde para evitar memory leaks.
    char *duplicate = ft_strdup(original);

    if (duplicate == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    printf("Original: %s | Endereço: %p\n", original, (void *)original);
    printf("Duplicate: %s | Endereço: %p\n", duplicate, (void *)duplicate);

    free(duplicate); // Don't forget to free the allocated memory
    return 0;
}

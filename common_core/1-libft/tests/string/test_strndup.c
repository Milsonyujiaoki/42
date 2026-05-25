#include "libft.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int main(void) {
    const char *original = "Hello, World!";
    char *duplicate = ft_strndup(original, 5); // Duplicate only the first 5 characters

    if (duplicate == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    printf("Original: %s | Endereço: %p\n", original, (void *)original);
    printf("Duplicate: %s | Endereço: %p\n", duplicate, (void *)duplicate);

    free(duplicate); // Don't forget to free the allocated memory
    return 0;
}
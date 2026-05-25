#include "libft.h"
#include <libft.h>
#include <stdio.h>
#include <stdlib.h>

int main(void) {
    char *result;

    // Test case 1: Normal case
    result = ft_substr("Hello, World!", 7, 5);
    printf("'ft_substr(\"Hello, World!\", 7, 5)': '%s'\n", result); // Expected: 'World'
    free(result);

    // Test case 2: Começar além do comprimento da string
    result = ft_substr("Hello, World!", 20, 5);
    printf("'ft_substr(\"Hello, World!\", 20, 5)': '%s'\n", result); // Expected: ''
    free(result);

    // Test case 3: tamanho maior que o restante da string
    result = ft_substr("Hello, World!", 7, 20);
    printf("'ft_substr(\"Hello, World!\", 7, 20)': '%s'\n", result); // Expected: 'World!'
    free(result);

    // Test case 4: Null input string
    result = ft_substr(NULL, 0, 5);
    printf("'ft_substr(NULL, 0, 5)': '%s'\n", result); // Expected: '(null)'
    free(result);

    return 0;
}
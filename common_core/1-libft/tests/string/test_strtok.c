#include "libft.h"
#include <string.h>
#include <stdio.h>

int main() {
    char str[] = "Aprender C e fixe o conhecimento com projetos práticos";
    char *token;

    // 1ª chamada: passa a string "str"
    token = ft_strtok(str, " ");
    
    while (token != NULL) {
        printf("Token: %s\n", token);

        // Chamadas seguintes: passa NULL
        token = ft_strtok(NULL, " ");
    }
    return 0;
}

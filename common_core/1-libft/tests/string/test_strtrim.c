#include "libft.h"
#include <stdio.h>
#include <stdlib.h>

int main(){
    printf("Teste 1: String normal\n");
    printf("ft_strtrim(\"  Hello, World!  \", \" \")\n");
    char *result1 = ft_strtrim("  Hello, World!  ", " ");
    printf("Teste 1: '%s'\n", result1);
    free(result1);

    printf("Teste 2: String com caracteres a serem removidos no meio\n");
    printf("ft_strtrim(\"xxHello, World!xx\", \"x\")\n");
    char *result2 = ft_strtrim("xxHello, World!xx", "x");    
    printf("Teste 2: '%s'\n", result2);
    free(result2);

    printf("Teste 3: String sem caracteres a serem removidos\n");
    printf("ft_strtrim(\"Hello, World!\", \" \")\n");
    char *result3 = ft_strtrim("Hello, World!", " ");
    printf("Teste 3: '%s'\n", result3);
    free(result3);
    return 0;
}
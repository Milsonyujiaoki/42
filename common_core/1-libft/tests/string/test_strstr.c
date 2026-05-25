#include "libft.h"
#include <string.h>
#include <stdio.h>

void find_str(char const* str, char const* substr)
{
    char const* pos = ft_strstr(str, substr);
    if (pos)
        printf(
            "Found the string [%s] in [%s] at position %td\n",
            substr, str, pos - str
        );
    else
        printf(
            "The string [%s] was not found in [%s]\n",
            substr, str
        );
}


int main() {
    const char *str = "Hello, World!";
    // Agrupamos os testes num array para usar um loop
    const char *testes[] = {
        "World", 
        ",", 
        "Hello", 
        "!", 
        "NotInString", 
        "",           // Caso crítico: substring vazia
        "Hello, World! Extra" // Caso: substring maior que a string
    };
    int num_testes = sizeof(testes) / sizeof(testes[0]);

    printf("--- Testando ft_strstr ---\n");
    printf("String base: [%s]\n\n", str);

    for (int i = 0; i < num_testes; i++) {
        find_str(str, testes[i]);       
        }

    return 0;
}

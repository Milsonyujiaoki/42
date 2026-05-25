#include "libft.h"

char *ft_strtok( char* restrict str, const char* restrict delim ) {
    static char *last_pos = NULL;

    if (str != NULL)
        last_pos = str;
    if (last_pos == NULL || *last_pos == '\0')
        return NULL;

    // 1. Pular delimitadores que estejam NO INÍCIO (ex: espaços antes da palavra)
    while (*last_pos && ft_strchr(delim, *last_pos))
        last_pos++;

    if (*last_pos == '\0') return NULL; // Se só havia delimitadores

    char *start = last_pos;
    char *prt = start;

    // 2. Procurar o próximo delimitador para "cortar"
    while (*prt && !ft_strchr(delim, *prt))
        prt++;

    // 3. O CORTE
    if (*prt != '\0') {
        *prt = '\0';
        last_pos = prt + 1;
    } else {
        last_pos = prt; // Chegamos ao fim da string
    }
    // 4. Retornar o token encontrado
    return (start);
}


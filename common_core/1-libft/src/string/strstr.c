#include "libft.h"


char *ft_strstr(const char *str, const char* substr) {
    if (!*substr) {
        return (char *)str; // Se a substring for vazia, retorna o ponteiro para a string original
    }

    for (; *str; str++) {
        const char *s1 = str;
        const char *s2 = substr;
        // Compara a substring com a parte atual da string
        while (*s1 && *s2 && (*s1 == *s2)) {
            s1++;
            s2++;
        }

        if (!*s2) { // Se chegamos ao final da substring, encontramos uma correspondência
            return (char *)str;
        }
    }

    return NULL; // Substring não encontrada
}
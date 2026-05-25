#include "libft.h"
#include <stdio.h>
#include <libft.h>

int main(void) {
    char texto[] = "Salve Galera!!!";

    char destino[50];

    // A função nao tem protecao contra buffer overflow, entao cuidado com o tamanho do destino e do texto
    ft_strcpy(destino, texto);

    printf("ft_strcpy: %s\n", destino);

    return 0;
}

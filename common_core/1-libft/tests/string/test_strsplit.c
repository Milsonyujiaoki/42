#include "libft.h"

int main(void)
{
    // Testes para ft_strsplit
    char **result;

    // Teste 1: String com delimitador simples
    result = ft_strsplit("Hello World!", ' ');
    ft_printf("ft_strsplit(\"Hello World!\", ' ')\n");
    for (int i = 0; result[i] != NULL; i++)
    {
        ft_printf("Teste 1: '%s'\n", result[i]);
        ft_free(result[i]);
    }
    ft_free(result);

    // Teste 2: String com múltiplos delimitadores
    result = ft_strsplit(",,Hello,,World!", ',');
    ft_printf("ft_strsplit(\",,Hello,,World!\", ',')\n");   
    for (int i = 0; result[i] != NULL; i++)
    {
        ft_printf("Teste 2: '%s'\n", result[i]);
        ft_free(result[i]);
    }
    ft_free(result);

    return (0);
}
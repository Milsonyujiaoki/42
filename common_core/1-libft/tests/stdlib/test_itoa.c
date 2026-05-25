#include "libft.h"
#include <libft.h>

int main(void)
{
    // Teste 1: Conversão de um número positivo
    char *result1 = ft_itoa(12345);
    ft_printf("ft_itoa(12345) = %s\n", result1);
    ft_free(result1); // Lembre-se de liberar a memória alocada

    // Teste 2: Conversão de um número negativo
    char *result2 = ft_itoa(-6789);
    ft_printf("ft_itoa(-6789) = %s\n", result2);
    ft_free(result2);

    // Teste 3: Conversão do número zero
    char *result3 = ft_itoa(0);
    ft_printf("ft_itoa(0) = %s\n", result3);
    ft_free(result3);

    return 0;
}
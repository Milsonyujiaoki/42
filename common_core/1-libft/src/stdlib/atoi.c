#include "libft.h"

int ft_atoi(const char *str)
{
    // 1. Declarar variáveis (índice, sinal, resultado)
    
    // 2. Loop para pular espaços: ' ', '\t', '\n', '\v', '\f', '\r'
    
    // 3. Condição para checar e salvar o sinal (+ ou -)
    
    // 4. Loop principal: enquanto (str[i] >= '0' && str[i] <= '9')
    //    Faz o cálculo matemático e avança o índice
    
    // 5. Retorna (resultado * sinal)
    int result = 0;
    int sign = 1;

    // Pular espaços em branco iniciais
    while (ft_isspace((unsigned char)*str)) {
        str++;
    }

    // Lidar com sinal opcional
    if (*str == '-')
    {
        sign = -1;
        str++;
    }
    else if (*str == '+')
    {
        str++;
    }

    // Converter dígitos para inteiro
    while (ft_isdigit((unsigned char)*str)) {
        result = result * 10 + (*str - '0');
        str++;
    }

    return sign * result;
}

#include <libft.h>

char *ft_itoa(int n)
{
    // 1. Declarar variáveis (tamanho do número, sinal, índice)
    
    // 2. Verificar se n é negativo e ajustar o sinal e o valor de n
    
    // 3. Calcular o número de dígitos em n (considerando o sinal)
    
    // 4. Alocar memória para a string resultante (tamanho + 1 para NUL)
    
    // 5. Preencher a string com os dígitos de n (do final para o início)
    
    // 6. Adicionar o sinal se necessário
    
    // 7. Retornar a string alocada
    char buffer[12]; // Buffer temporário para armazenar o número como string
    int is_negative = n < 0;
    int i = 0;

    if (n == 0) {
        buffer[i++] = '0';
    } else {
        if (is_negative) {
            n = -n; // Tornar n positivo para facilitar a conversão
        }
        while (n > 0) {
            buffer[i++] = (n % 10) + '0'; // Obter o dígito mais à direita
            n /= 10; // Remover o dígito mais à direita
        }
        if (is_negative) {
            buffer[i++] = '-'; // Adicionar o sinal negativo
        }
    }
    buffer[i] = '\0'; // Terminar a string

    // Inverter a string para obter a representação correta
    for (int j = 0; j < i / 2; j++) {
        char temp = buffer[j];
        buffer[j] = buffer[i - j - 1];
        buffer[i - j - 1] = temp;
    }

    return ft_strdup(buffer); // Retornar uma cópia alocada da string
}
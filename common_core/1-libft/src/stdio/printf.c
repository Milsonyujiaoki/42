#include <stdio.h>
#include <stdarg.h>

/*
** ft_printf — encapsula o printf do sistema.
** Futuro: substituir por uma implementação própria que escreve diretamente no stdout (fd 1).
*/
int ft_printf(const char *format, ...)
{
    va_list args;
    int     printed_chars;

    if (!format)
        return (0);

    // 1. Inicializa a lista de argumentos variáveis
    va_start(args, format);

    // 2. Passa a lista de argumentos para a função do sistema 'vprintf'
    printed_chars = vprintf(format, args);

    // 3. Limpa a memória utilizada pela lista de argumentos
    va_end(args);

    // Retorna o total de caracteres impressos, mantendo o comportamento do printf original
    return (printed_chars);
}

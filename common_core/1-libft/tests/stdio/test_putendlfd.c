#include "libft.h"
#include <libft.h>

int main() {
    ft_printf("=== INICIANDO TESTES: ft_putendl_fd ===\n\n");

    // Teste 01: Escreve a string "Hello, World!" seguida de uma nova linha no stdout usando ft_putendl_fd
    ft_putendl_fd("Hello, World!\n", 1);
    ft_printf("[OK] Teste 01: ft_putendl_fd(\"Hello, World!\", 1) - Verifique se 'Hello, World!' foi impresso seguido de uma nova linha no console\n");

    ft_printf("\n=== TESTES CONCLUÍDOS: ft_putendl_fd ===\n");
    return 0;
}
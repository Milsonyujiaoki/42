#include "libft.h"
#include <libft.h>

int main() {

   ft_printf("=== INICIANDO TESTES: ft_putstr_fd ===\n\n");
    // Teste 01: Escreve a string "Hello, World!" no stdout usando ft_putstr_fd
    ft_putstr_fd("Hello, World!", 1);
    ft_printf("\n[OK] Teste 01: ft_putstr_fd(\"Hello, World!\", 1) - Verifique se 'Hello, World!' foi impresso no console\n");


    return 0;
}
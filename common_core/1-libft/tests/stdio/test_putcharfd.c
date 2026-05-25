#include "libft.h"
#include <libft.h>

int main() {
    ft_printf("=== INICIANDO TESTES: ft_putchar_fd ===\n\n");
    
    // Teste 01: Escreve o caractere 'A' no stdout usando ft_putchar_fd
    ft_putchar_fd('A', 1); 
    
    ft_printf("\n[OK] Teste 01: ft_putchar_fd('A', 1) - Verifique se 'A' foi impresso no console\n");
    ft_printf("\n=== TESTES CONCLUÍDOS: ft_putchar_fd ===\n");
    return 0;
}
    
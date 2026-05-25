#include "libft.h"
#include <libft.h>

int main() {
    ft_printf("=== INICIANDO TESTES: ft_putnbr_fd ===\n\n");
    // Teste 01: Escreve o número 42 no stdout usando ft_putnbr_fd
    ft_putnbr_fd(42, 1);
    ft_printf("\n[OK] Teste 01: ft_putnbr_fd(42, 1) - Verifique se '42' foi impresso no console\n");
    // Teste 02: Escreve o número -12345 no stdout usando ft_putnbr_fd
    ft_putnbr_fd(-12345, 1);
    ft_printf("\n[OK] Teste 02: ft_putnbr_fd(-12345, 1) - Verifique se '-12345' foi impresso no console\n");

    ft_printf("\n=== TESTES CONCLUÍDOS: ft_putnbr_fd ===\n");
    return 0;
}
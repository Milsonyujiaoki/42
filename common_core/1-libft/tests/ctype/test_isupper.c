#include "libft.h"
#include <ctype.h>
#include <stdio.h>
#include <stdio.h>
int main(void) {
    // 1. Casos Válidos (Devem passar)
    char validos[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    
    // 2. Casos Inválidos Próximos (Devem falhar - Erros comuns de intervalo)
    char invalidos[] = "abcdefghijklmnopqrstuvwxyz0123456789"; // Letras minúsculas e números
    
    // 3. Casos Especiais (Invisíveis e limites ASCII)
    int especiais[] = {0, 32, 127, -1, 255};

    printf("=== TESTANDO CASOS VÁLIDOS (Esperado: > 0) ===\n");
    for (size_t i = 0; validos[i] != '\0'; i++) {
        int res = ft_isupper(validos[i]);
        // Verificamos apenas se res != 0 (padrão C)
        printf("Char '%c' (ASCII %3d) -> Retorno: %d [%s]\n", 
               validos[i], validos[i], res, (res != 0) ? "OK" : "FAIL");
    }

    printf("\n=== TESTANDO CASOS INVÁLIDOS (Esperado: 0) ===\n");
    for (size_t i = 0; invalidos[i] != '\0'; i++) {
        int res = ft_isupper(invalidos[i]);
        printf("Char '%c' (ASCII %3d) -> Retorno: %d [%s]\n", 
               invalidos[i], invalidos[i], res, (res == 0) ? "OK" : "FAIL");
    }

    printf("\n=== TESTANDO LIMITES E ESPECIAIS (Esperado: 0) ===\n");
    for (size_t i = 0; i < sizeof(especiais) / sizeof(especiais[0]); i++) {
        int res = ft_isupper(especiais[i]);
        // Se for imprimível mostra o char, senão mostra '?'
        char visual = (especiais[i] >= 32 && especiais[i] < 127) ? especiais[i] : '?';
        printf("Int  %3d  (Visual '%c') -> Retorno: %d [%s]\n", 
               especiais[i], visual, res, (res == 0) ? "OK" : "FAIL");
    }

    return (0);
}

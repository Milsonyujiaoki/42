#include "libft.h"
#include <ctype.h>
#include <stdio.h>
#include <stdio.h>
int main(void) {
    // 1. Casos Válidos (Devem passar)
    char validos[] = "059aFf%^~120";
    
    // 2. Casos Inválidos Próximos (Devem falhar - Erros comuns de intervalo)
    char invalidos[] = "\x1F\x7F"; // 31 é limite inferior, 127 é limite superior
    
    // 3. Casos Especiais (Invisíveis e limites ASCII)
    int especiais[] = {0, 32, 127, -1, 255};

    printf("=== TESTANDO CASOS VÁLIDOS (Esperado: > 0) ===\n");
    for (size_t i = 0; validos[i] != '\0'; i++) {
        int res = ft_isgraph(validos[i]);
        // Verificamos apenas se res != 0 (padrão C)
        printf("Char '%c' (ASCII %3d) -> Retorno: %d [%s]\n", 
               validos[i], validos[i], res, (res != 0) ? "OK" : "FAIL");
    }

    printf("\n=== TESTANDO CASOS INVÁLIDOS (Esperado: 0) ===\n");
    for (size_t i = 0; invalidos[i] != '\0'; i++) {
        int res = ft_isgraph(invalidos[i]);
        printf("Char '%c' (ASCII %3d) -> Retorno: %d [%s]\n", 
               invalidos[i], invalidos[i], res, (res == 0) ? "OK" : "FAIL");
    }

    printf("\n=== TESTANDO LIMITES E ESPECIAIS (Esperado: 0) ===\n");
    for (size_t i = 0; i < sizeof(especiais) / sizeof(especiais[0]); i++) {
        int res = ft_isgraph(especiais[i]);
        // Se for imprimível mostra o char, senão mostra '?'
        char visual = (especiais[i] >= 33 && especiais[i] < 127) ? especiais[i] : '?';
        printf("Int  %3d  (Visual '%c') -> Retorno: %d [%s]\n", 
               especiais[i], visual, res, (res == 0) ? "OK" : "FAIL");
    }

    return (0);
}

#include "libft.h"
#include <ctype.h>
#include <stdio.h>
#include <stdio.h>
int main(void) {
    // 1. Casos Válidos (Devem passar)
    char validos[] = "\x00\x01\x02\x03\x04\x05\x06\x07\x08\x09\x0A\x0B\x0C\x0D\x0E\x0F"
                      "\x10\x11\x12\x13\x14\x15\x16\x17\x18\x19\x1A\x1B\x1C\x1D\x1E\x1F"; // Todos os caracteres de controle ASCII
    
    // 2. Casos Inválidos Próximos (Devem falhar - Erros comuns de intervalo)
    char invalidos[] = " \x7F"; // Espaço e DEL não são caracteres de controle
    
    // 3. Casos Especiais (Invisíveis e limites ASCII)
    int especiais[] = {0, 32, 127, -1, 255};

    printf("=== TESTANDO CASOS VÁLIDOS (Esperado: > 0) ===\n");
    for (size_t i = 0; validos[i] != '\0'; i++) {
        int res = ft_iscntrl(validos[i]);
        // Verificamos apenas se res != 0 (padrão C)
        printf("Char '%c' (ASCII %3d) -> Retorno: %d [%s]\n", 
               validos[i], validos[i], res, (res != 0) ? "OK" : "FAIL");
    }

    printf("\n=== TESTANDO CASOS INVÁLIDOS (Esperado: 0) ===\n");
    for (size_t i = 0; invalidos[i] != '\0'; i++) {
        int res = ft_iscntrl(invalidos[i]);
        printf("Char '%c' (ASCII %3d) -> Retorno: %d [%s]\n", 
               invalidos[i], invalidos[i], res, (res == 0) ? "OK" : "FAIL");
    }

    printf("\n=== TESTANDO LIMITES E ESPECIAIS (Esperado: 0) ===\n");
    for (size_t i = 0; i < sizeof(especiais) / sizeof(especiais[0]); i++) {
        int res = ft_iscntrl(especiais[i]);
        // Se for imprimível mostra o char, senão mostra '?'
        char visual = (especiais[i] >= 32 && especiais[i] < 127) ? especiais[i] : '?';
        printf("Int  %3d  (Visual '%c') -> Retorno: %d [%s]\n", 
               especiais[i], visual, res, (res == 0) ? "OK" : "FAIL");
    }

    return (0);
}

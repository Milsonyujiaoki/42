#include <unistd.h>
#include <libft.h>



int ft_puts(const char *s) {
    // Se a string for nula, imprime uma linha vazia ou simula erro
    if (!s) {
        s = "(null)";
    }

    size_t len = ft_strlen(s);

    // 1. Escreve o conteúdo da string no stdout (fd 1)
    if (write(1, s, len) < 0) {
        return -1; // Retorna EOF (-1) se falhar
    }

    // 2. Escreve a quebra de linha ('\n') obrigatória do puts
    if (write(1, "\n", 1) < 0) {
        return -1;
    }

    // O puts original retorna um valor não-negativo em caso de sucesso
    return 1; 
}

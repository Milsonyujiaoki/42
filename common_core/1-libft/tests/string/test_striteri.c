#include "libft.h"
#include <libft.h>

void to_upper(unsigned int i, char *c) {
        (void)i; // Ignora o índice para esta função, mas mantém a assinatura
        if (*c >= 'a' && *c <= 'z')
            *c = *c - 32;
    }

int main(){
    // teste striteri
    char str[] = "Hello";
    
    ft_striteri(str, to_upper);
    if (ft_strcmp(str, "HELLO") == 0)
        ft_printf("[OK] Teste ft_striteri: \"Hello\" -> \"HELLO\"\n");
    else
        ft_printf("[FAIL] Teste ft_striteri: Esperado \"HELLO\", obtido \"%s\"\n", str);

    return 0;
}
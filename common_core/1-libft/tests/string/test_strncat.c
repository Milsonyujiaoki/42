#include "libft.h"
#include <stdio.h>
#include <string.h>

int main(void){

    char msg[60] = "Fala pessoal!\n"; 
    char src[20] = "Tudo bem com voces?";
    printf("Mensagem: %s | Endereço de msg antes: %p\n", msg, (void *)msg);
    ft_strncat(msg, src, 10);
    
    printf("Mensagem após ft_strncat: %s | Endereço %p\n", msg, (void *)msg);
    return 0;
}
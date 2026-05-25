#include <stdio.h>
#include "libft.h"

int main(void){

    char msg[60] = "Fala pessoal!\n"; 
    printf("msg: %s\n", msg);

    char src[20] = "Tudo bem com voces?";
    printf("src: %s\n", src);

    ft_strcat(msg, src);
    
    printf("msg após ft_strcat: %s\n", msg);
    return 0;
}

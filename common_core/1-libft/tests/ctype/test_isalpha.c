#include "libft.h"
#include <ctype.h>
#include <stdio.h>
#include <stdio.h>
int main(void){
	char msg = 'H';
	char msg2 = '2';
	char msg3 = '@';
	unsigned char c = '\xdf'; // German letter ß in ISO-8859-1

	printf("retorno is_alpha H: %d\n ",!!ft_isalpha(msg));
	printf("retorno is_alpha 2: %d\n ",!!ft_isalpha(msg2));
	printf("retorno is_alpha @: %d\n ",!!ft_isalpha(msg3));
	printf("retorno is_alpha '\xdf': %d\n ",!!ft_isalpha(c));
	
	return 0;
}

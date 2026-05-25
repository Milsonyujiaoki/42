#include <libft.h>

void	ft_striteri(char *str, void (*f)(unsigned int, char*))
{
	unsigned int	i;

	// 1. Verificação de segurança (Se str ou f não existirem, sai da função)
	if (!str || !f)
		return ; // Corrigido: apenas 'return' sem valor porque a função é void

	// 2. Percorrer a string original usando um índice
	i = 0;
	while (str[i] != '\0')
	{
		// 3. Passar o índice 'i' e o ENDEREÇO do caractere atual '&str[i]' para a função f
		f(i, &str[i]);
		i++;
	}
}

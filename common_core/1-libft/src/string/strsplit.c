#include <libft.h>


char	**ft_strsplit(const char *str, char delimiter)
{
	char	*s;
	char	d;
	char	**result;
	size_t	len;
	size_t	words;
	size_t	i;

	s = (char *)str; 
	d = delimiter;
	if (!s)
		return (NULL); 

	// 1. CONTAR PALAVRAS 
	words = 0;
	i = 0;
	while (s[i])
	{
		while (s[i] == d)
			i++;
		if (s[i] != '\0')
		{
			words++;
			while (s[i] && s[i] != d)
				i++;
		}
	}

	// 2. MALLOC DO ARRAY PRINCIPAL 
	result = (char **)ft_malloc((words + 1) * sizeof(char *));
	if (!result)
		return (NULL);

	// 3. EXTRAIR E COPIAR PALAVRAS
	i = 0;
	while (*s)
	{
		// Ignorar delimitadores iniciais 
		while (*s == d)
			s++;
		if (*s == '\0')
			break ;
		// Descobrir o tamanho da palavra atual
		len = 0;
		while (s[len] && s[len] != d)
			len++;

		// Malloc da palavra e cópia usando ft_substr para garantir alocação e cópia segura 
		result[i] = ft_substr(s, 0, len);
		if (!result[i])		{
			// Em caso de falha, liberar o que já foi alocado
			while (i > 0)			{
				i--;
				ft_free(result[i]);
			}
			ft_free(result);
			return (NULL);
		}
		s += len;
		i++;
	} // Chaveta de fecho do while (*s) movida para o lugar correto

	// 4. FINALIZAR COM NULL 
	result[i] = NULL;
	return (result); 
}

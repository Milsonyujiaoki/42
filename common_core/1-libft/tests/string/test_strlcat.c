#include "libft.h"
#include <string.h>
#include <stdio.h>

// Prototipagem da sua função para o compilador
size_t	ft_strlcat(char *dst, const char *src, size_t size);

int	main(void)
{
	size_t	tamanho_necessario;
	char	dest3_antes[20];

	// =========================================================================
	// TESTE 1: Cenário de Sucesso (Cabe tudo no buffer)
	// =========================================================================
	printf("--- TESTE 1: Concatenação com Sucesso ---\n");
	char	src1[] = " Mundo!";
	char	dest1[20] = "Olá"; // comprimento inicial = 3

	printf("Antes -> Dest: '%s' | Src: '%s'\n", dest1, src1);
	tamanho_necessario = ft_strlcat(dest1, src1, sizeof(dest1));
	printf("Depois -> Dest: '%s'\n", dest1);
	printf("Retorno da Função:  %zu (Esperado: 10)\n", tamanho_necessario);

	if (tamanho_necessario < sizeof(dest1) && ft_strcmp(dest1, "Olá Mundo!") == 0)
		printf("Resultado:          [SUCESSO]\n\n");
	else
		printf("Resultado:          [FALHA]\n\n");

	// =========================================================================
	// TESTE 2: Cenário de Truncagem (O texto é cortado)
	// =========================================================================
	printf("--- TESTE 2: Concatenação com Truncagem ---\n");
	char	src2[] = "Texto Muito Longo";
	char	dest2[20] = "Início, "; // comprimento inicial = 8

	printf("Antes -> Dest: '%s' | Src: '%s'\n", dest2, src2);
	tamanho_necessario = ft_strlcat(dest2, src2, sizeof(dest2));
	printf("Depois -> Dest: '%s'\n", dest2);
	printf("Retorno da Função:  %zu (Esperado: 25)\n", tamanho_necessario);

	if (tamanho_necessario >= sizeof(dest2))
	{
		printf("Resultado:          [SUCESSO] O texto foi truncado com segurança.\n");
		printf("Nota:               Faltaram %zu bytes para anexar tudo.\n\n", (tamanho_necessario - sizeof(dest2) + 1));
	}
	else
		printf("Resultado:          [FALHA]\n\n");

	// =========================================================================
	// TESTE 3: Caso Limite (Size menor que o tamanho atual do destino)
	// =========================================================================
	printf("--- TESTE 3: Caso Limite (Size <= strlen(dst)) ---\n");
	char	src3[] = "Invisível";
	char	dest3[20] = "Texto Base"; // comprimento inicial = 10

	ft_strcpy(dest3_antes, dest3);
	printf("Antes -> Dest: '%s' | Src: '%s'\n", dest3, src3);
	// Passamos size = 5, que é menor que o comprimento de "Texto Base" (10)
	tamanho_necessario = ft_strlcat(dest3, src3, 5);
	printf("Depois -> Dest: '%s' (Não deve ter mudado)\n", dest3);
	printf("Retorno da Função:  %zu (Esperado: 5 + %zu = %zu)\n",
		tamanho_necessario, ft_strlen(src3), 5 + ft_strlen(src3));

	if (ft_strcmp(dest3, dest3_antes) == 0
		&& tamanho_necessario == (5 + ft_strlen(src3)))
		printf("Resultado:          [SUCESSO] Proteção ativa. Destino intacto.\n");
	else
		printf("Resultado:          [FALHA] O destino foi corrompido ou o retorno está incorreto.\n");

	return (0);
}

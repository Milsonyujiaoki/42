#include "libft.h"
#include <stdio.h>
#include <string.h>
// Prototipagem da sua função para o compilador
size_t	ft_strlcpy(char *dst, const char *src, size_t size);

int	main(void)
{
	char	destino[10];
	size_t	tamanho_necessario;

	// =========================================================================
	// TESTE 1: Cenário de Truncagem (Origem maior que o Destino)
	// =========================================================================
	printf("--- TESTE 1: Cenário de Truncagem ---\n");
	char	origem1[] = "Texto Muito Longo";
	
	ft_memset(destino, 'X', sizeof(destino)); // Preenche com 'X' para detetar vazamentos
	tamanho_necessario = ft_strlcpy(destino, origem1, sizeof(destino));

	printf("Origem:             '%s' (%zu bytes)\n", origem1, ft_strlen(origem1));
	printf("Destino Final:      '%s'\n", destino);
	printf("Retorno da Função:  %zu\n", tamanho_necessario);

	if (tamanho_necessario >= sizeof(destino))
	{
		printf("Resultado:          [SUCESSO] O texto foi truncado com segurança.\n");
		printf("Nota:               Faltaram %zu bytes para copiar tudo.\n", (tamanho_necessario - sizeof(destino) + 1));
	}
	else
		printf("Resultado:          [FALHA] A função deveria ter indicado truncagem.\n");

	// =========================================================================
	// TESTE 2: Cenário de Sucesso (Origem cabe perfeitamente)
	// =========================================================================
	printf("\n--- TESTE 2: Cenário de Sucesso ---\n");
	char	origem2[] = "Curto";

	ft_memset(destino, 'X', sizeof(destino));
	tamanho_necessario = ft_strlcpy(destino, origem2, sizeof(destino));

	printf("Origem:             '%s' (%zu bytes)\n", origem2, ft_strlen(origem2));
	printf("Destino Final:      '%s'\n", destino);
	printf("Retorno da Função:  %zu\n", tamanho_necessario);

	if (tamanho_necessario < sizeof(destino) && ft_strcmp(destino, origem2) == 0)
		printf("Resultado:          [SUCESSO] Cópia integral e sem cortes.\n");
	else
		printf("Resultado:          [FALHA] Erro na cópia ou no retorno.\n");

	// =========================================================================
	// TESTE 3: Cenário com Tamanho Zero (Proteção de Limite)
	// =========================================================================
	printf("\n--- TESTE 3: Cenário com Tamanho Zero ---\n");
	char	origem3[] = "Não Copiar";

	ft_memset(destino, 'X', sizeof(destino));
	destino[9] = '\0'; // Garante terminação para o printf não quebrar
	
	tamanho_necessario = ft_strlcpy(destino, origem3, 0);

	printf("Origem:             '%s' (%zu bytes)\n", origem3, ft_strlen(origem3));
	printf("Destino Final:      '%s' (Não deve mudar de 'XXXXXXXXX')\n", destino);
	printf("Retorno da Função:  %zu\n", tamanho_necessario);

	if (tamanho_necessario == ft_strlen(origem3) && destino[0] == 'X')
		printf("Resultado:          [SUCESSO] O destino foi protegido e o tamanho correto foi retornado.\n");
	else
		printf("Resultado:          [FALHA] O código tentou escrever em tamanho zero ou retornou valor errado.\n");

	return (0);
}

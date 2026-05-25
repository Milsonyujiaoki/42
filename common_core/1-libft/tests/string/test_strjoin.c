#include "libft.h"
#include <stdio.h>
#include <stdlib.h>

// =========================================================================
// Função auxiliar de teste
// =========================================================================
static void	run_test(
	const char *test_name,
	const char *s1,
	const char *s2,
	const char *expected
)
{
	char	*result;

	printf("=== %s ===\n", test_name);

	result = ft_strjoin(s1, s2);

	// ---------------------------------------------------------------------
	// Casos onde esperamos NULL
	// ---------------------------------------------------------------------
	if (expected == NULL)
	{
		if (result == NULL)
			printf("[SUCESSO] Retornou NULL como esperado.\n\n");
		else
		{
			printf("[FALHA] Esperava NULL, mas recebeu: '%s'\n\n", result);
			free(result);
		}
		return ;
	}

	// ---------------------------------------------------------------------
	// Falha de malloc
	// ---------------------------------------------------------------------
	if (result == NULL)
	{
		printf("[FALHA] ft_strjoin retornou NULL inesperadamente.\n\n");
		return ;
	}

	// ---------------------------------------------------------------------
	// Comparação do resultado
	// ---------------------------------------------------------------------
	printf("Resultado obtido: '%s'\n", result);
	printf("Resultado esperado: '%s'\n", expected);

	if (ft_strcmp(result, expected) == 0)
		printf("[SUCESSO]\n\n");
	else
		printf("[FALHA]\n\n");

	free(result);
}

// =========================================================================
// MAIN
// =========================================================================
int	main(void)
{
	// =========================================================================
	// TESTE 1: Strings normais
	// =========================================================================
	run_test(
		"TESTE 1: Strings normais",
		"Hello, ",
		"World!",
		"Hello, World!"
	);

	// =========================================================================
	// TESTE 2: Strings vazias
	// =========================================================================
	run_test(
		"TESTE 2: Strings vazias",
		"",
		"",
		""
	);

	// =========================================================================
	// TESTE 3: Primeira string vazia
	// =========================================================================
	run_test(
		"TESTE 3: Primeira string vazia",
		"",
		"World",
		"World"
	);

	// =========================================================================
	// TESTE 4: Segunda string vazia
	// =========================================================================
	run_test(
		"TESTE 4: Segunda string vazia",
		"Hello",
		"",
		"Hello"
	);

	// =========================================================================
	// TESTE 5: s1 == NULL
	// =========================================================================
	run_test(
		"TESTE 5: s1 == NULL",
		NULL,
		"World",
		NULL
	);

	// =========================================================================
	// TESTE 6: s2 == NULL
	// =========================================================================
	run_test(
		"TESTE 6: s2 == NULL",
		"Hello",
		NULL,
		NULL
	);

	// =========================================================================
	// TESTE 7: Ambos NULL
	// =========================================================================
	run_test(
		"TESTE 7: Ambos NULL",
		NULL,
		NULL,
		NULL
	);

	return (0);
}
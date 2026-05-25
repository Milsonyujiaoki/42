#include <stdlib.h>
#include "libft.h"
#include <stdint.h>
#include <stdio.h>


int	main(void)
{
	// Teste 1: Alocação básica e inicialização a zero
	size_t count = 5;
	size_t size = sizeof(int);
	int *arr = (int *)ft_calloc(count, size);
	if (arr == NULL) {
		printf("Falha no Teste 1: Alocação retornou NULL\n");
		return (1);
	}
	for (size_t i = 0; i < count; i++) {
		if (arr[i] != 0) {
			printf("Falha no Teste 1: Memória não foi zerada no índice %zu\n", i);
			free(arr);
			return (1);
		}
	}
	free(arr);

	// Teste 2: Count ou Size igual a zero (Ajustado para o padrão C)
	void *ptr1 = ft_calloc(0, size);
	void *ptr2 = ft_calloc(count, 0);
	
	// Como ambos os comportamentos são válidos, libertamos a memória se não for NULL
	if (ptr1 != NULL)
		free(ptr1);
	if (ptr2 != NULL)
		free(ptr2);
	// Nota: Removeu-se a verificação rígida de NULL para evitar falsos negativos no Linux

	// Teste 3: Verificação de tratamento de Overflow
	size_t large_count = SIZE_MAX / size + 1;
	void *ptr3 = ft_calloc(large_count, size);
	if (ptr3 != NULL) {
		printf("Falha no Teste 3: Overflow não foi detetado (retornou ponteiro)\n");
		free(ptr3);
		return (1);
	}

	printf("Todos os testes da ft_calloc passaram com SUCESSO!\n");
	return (0);
}

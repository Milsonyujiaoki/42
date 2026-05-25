#include "libft.h"
#include <string.h>
#include <stdio.h>

// Prototipagem da sua função para o compilador saber que ela existe
void	*ft_memmove(void *dest, const void *src, size_t n);

int	main(void)
{
    // =========================================================================
	printf("--- TESTE ORIGINAL: Cópia entre buffers diferentes ---\n");
	char src[] = "Hello, World!";
	printf("Source: %s | Endereço: %p | Tamanho: %zu\n", src, (void *)src, sizeof(src));

	// Inicializado com {0} para limpar o lixo de memória da RAM
	char dest[20] = {0}; 
	printf("Criação do buffer de destino: %s | Endereço: %p | Tamanho: %zu\n", dest, (void *)dest, sizeof(dest));
	
	ft_memmove(dest, src, sizeof(src));
	printf("Destino: %s | Endereço: %p | Tamanho: %zu\n\n", dest, (void *)dest, sizeof(dest));
    printf("validação: %s\n\n", ft_memcmp(dest, src, sizeof(src)) == 0 ? "SUCESSO" : "FALHA");

	// =========================================================================
	// TESTE 2: Sobreposição da Direita para a Esquerda (d < s)
	// Copiar "World" para o lugar de "Hello"
	// =========================================================================
	printf("--- TESTE 2: Sobreposição (Esquerda <- Direita | d < s) ---\n");
	char str_overlap1[] = "Hello, World!";
	printf("Antes:  %s| Endereço: %p | Tamanho: %zu\n", str_overlap1, (void *)str_overlap1, sizeof(str_overlap1));
	
	// Origem: índice 7 ('W'), Destino: índice 0 ('H'), Tamanho: 5 bytes ("World")
	ft_memmove(&str_overlap1[0], &str_overlap1[7], 5);
    printf("Depois: %s| Endereço: %p | Tamanho: %zu\n", str_overlap1, (void *)str_overlap1, sizeof(str_overlap1));
	printf("validação: %s\n", ft_memcmp(&str_overlap1[0], "World", 5) == 0 ? "SUCESSO" : "FALHA");

	// =========================================================================
	// TESTE 3: Sobreposição da Esquerda para a Direita (d > s) -> CASO CRÍTICO
	// Copiar "Hello" para o lugar de "World"
	// =========================================================================
	printf("--- TESTE 3: Sobreposição (Esquerda -> Direita | d > s) ---\n");
	char str_overlap2[] = "Hello, World!";
	printf("Antes:  %s| Endereço: %p | Tamanho: %zu\n", str_overlap2, (void *)str_overlap2, sizeof(str_overlap2));
	
	// Origem: índice 0 ('H'), Destino: índice 7 ('W'), Tamanho: 5 bytes ("Hello")
	ft_memmove(&str_overlap2[7], &str_overlap2[0], 5);
    printf("Depois: %s| Endereço: %p | Tamanho: %zu\n", str_overlap2, (void *)str_overlap2, sizeof(str_overlap2));
	printf("validação: %s\n", ft_memcmp(&str_overlap2[7], "Hello", 5) == 0 ? "SUCESSO" : "FALHA");

	return (0);
}

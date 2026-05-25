#include "libft.h"
#include <libft.h>
#include <assert.h> // Útil para automação, ou use if/else se a norma proibir

// Função 1: Deslocamento por índice (Segura)
char shift_by_index(unsigned int i, char c)
{
    return (c + i);
}

// Função 2: Mascarar posições ímpares (Evita overflow e testa lógica posicional)
char upper_on_even(unsigned int i, char c)
{
    if (i % 2 == 0 && (c >= 'a' && c <= 'z'))
        return (c - 32);
    return (c);
}

char mudar_case(unsigned int i, char c)
{
    (void)i; // Ignora o índice para esta função, mas mantém a assinatura
    if (c >= 'a' && c <= 'z')
        return (c - 32);
    else if (c >= 'A' && c <= 'Z')
        return (c + 32);
    return (c);
}

int main()
{
    ft_printf("=== INICIANDO TESTES: ft_strmapi ===\n\n");

    // Teste 1: Fluxo Padrão (Sua lógica do "abc" -> "ace")
    char *res1 = ft_strmapi("abc", shift_by_index);
    if (res1 && ft_strncmp(res1, "ace", 4) == 0)
        ft_printf("[OK] Teste 1: Deslocamento básico (\"abc\" -> \"ace\")\n");
    else
        ft_printf("[FAIL] Teste 1: Esperado \"ace\", obtido \"%s\"\n", res1);
    ft_free(res1);

    // Teste 2: Lógica posicional avançada com string mais longa
    char *res2 = ft_strmapi("hello", upper_on_even);
    if (res2 && ft_strncmp(res2, "HeLlO", 6) == 0)
        ft_printf("[OK] Teste 2: Maiúsculas em índices pares\n");
    else
        ft_printf("[FAIL] Teste 2: Esperado \"HeLlO\", obtido \"%s\"\n", res2);
    ft_free(res2);

    // Teste 3: String Vazia
    char *res3 = ft_strmapi("", shift_by_index);
    if (res3 && res3[0] == '\0')
        ft_printf("[OK] Teste 3: String vazia retorna string vazia válida\n");
    else
        ft_printf("[FAIL] Teste 3: Falha ao lidar com \"\"\n");
    ft_free(res3);

    // Teste 4: Proteção contra String NULL
    char *res4 = ft_strmapi(NULL, shift_by_index);
    if (res4 == NULL)
        ft_printf("[OK] Teste 4: Entrada de String NULL protegida\n");
    else
        ft_printf("[FAIL] Teste 4: Não retornou NULL para string nula\n");
    ft_free(res4);

    // Teste 5: Proteção contra Função NULL (Regra estrita da libft)
    char *res5 = ft_strmapi("abc", NULL);
    if (res5 == NULL)
        ft_printf("[OK] Teste 5: Entrada de Função NULL protegida\n");
    else
        ft_printf("[FAIL] Teste 5: Não retornou NULL para função nula\n");
    ft_free(res5);

    // Teste 6: Lógica de mudança de case (Teste adicional para lógica mais complexa)
    char *res6 = ft_strmapi("TeStInG", mudar_case);
    if (res6 && ft_strncmp(res6, "tEsTiNg", 8) == 0)
        ft_printf("[OK] Teste 6: Mudança de case (\"TeStInG\" -> \"tEsTiNg\")\n");
    else
        ft_printf("[FAIL] Teste 6: Esperado \"tEsTiNg\", obtido \"%s\"\n", res6);
    ft_free(res6);


    ft_printf("\n=== TESTES CONCLUÍDOS ===\n");
    return (0);
}

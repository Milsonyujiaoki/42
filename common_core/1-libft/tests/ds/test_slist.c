#include "libft.h"


static void print_int(void *data)
{
    ft_putnbr_fd(*(int *)data, 1);
}


/* ── ft_lstnew ───────────────────────────────────────── */

static void test_ft_lstnew(void)
{
    int    *v;
    t_list *n;
    void    (*del)(void *);

    ft_printf("--- ft_lstnew ---\n");
    v = ft_malloc(sizeof(int));
    *v = 42;
    del = ft_free;
    
    n = ft_lstnew(v);

    // 1. Validação Crítica: O nó foi criado com sucesso?
    if (n == NULL)
    {
        ft_printf("[ERRO] ft_lstnew retornou NULL.\n");
        ft_free(v);
    }

    // 2. Validação de Conteúdo: O valor dentro do nó é o esperado?
    if (*(int *)(n->content) == 42)
        ft_printf("[OK] Conteúdo guardado corretamente: %d\n", *(int *)(n->content));
    else
        ft_printf("[ERRO] Conteúdo incorreto: %d (esperado: 42)\n", *(int *)(n->content));

    // 3. Validação do Próximo: O ponteiro 'next' foi limpo na inicialização?
    if (n->next == NULL)
        ft_printf("[OK] Ponteiro 'next' inicializado como NULL.\n");
    else
        ft_printf("[ERRO] O ponteiro 'next' não está a apontar para NULL.\n");

    ft_printf_lst(n, print_int); // Imprime o status da lista usando ft_printf
    
    // Limpeza segura da memória
    ft_lstdelone(n, del);

    //criando varios nós para testar a função de impressão
    t_list *head = NULL;
    for (int i = 1; i <= 3; i++)    {
        int *num = ft_malloc(sizeof(int));
        *num = i;
        t_list *new_node = ft_lstnew(num);
        ft_lstadd_back(&head, new_node);

    }

    ft_printf_lst(head, print_int); // Imprime o status da lista usando ft_printf

    // Limpeza segura da memória
    ft_lstclear(&head, del);
}

int main() 
{
    test_ft_lstnew();
    return 0;
}

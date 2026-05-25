
#include "libft.h"

/*
** =========================================================
** Stack — implementation (backed by t_vector)
** =========================================================
*/

t_stack *ft_stack_create(t_usize elem_size)
{
    t_stack *stack;

    stack = ft_malloc(sizeof(t_stack));
    if (!stack)
        return (NULL);
    stack->vec = ft_vector_create(elem_size);
    if (!stack->vec)
    {
        ft_free(stack);
        return (NULL);
    }
    return (stack);
}

void    ft_stack_destroy(t_stack *stack)
{
    if (!stack)
        return ;
    ft_vector_destroy(stack->vec);
    ft_free(stack);
}

void    ft_stack_destroy_deep(t_stack *stack, void (*free_fn)(void *))
{
    if (!stack)
        return ;
    ft_vector_destroy_deep(stack->vec, free_fn);
    ft_free(stack);
}

int ft_stack_push(t_stack *stack, const void *elem)
{
    if (!stack || !elem)
        return (0);
    return (ft_vector_push(stack->vec, elem));
}

int ft_stack_pop(t_stack *stack, void *out)
{
    if (!stack)
        return (0);
    return (ft_vector_pop(stack->vec, out));
}

void    *ft_stack_peek(const t_stack *stack)
{
    if (!stack)
        return (NULL);
    return (ft_vector_back(stack->vec));
}

t_usize ft_stack_size(const t_stack *stack)
{
    if (!stack)
        return (0);
    return (ft_vector_size(stack->vec));
}

t_bool  ft_stack_empty(const t_stack *stack)
{
    return (!stack || ft_vector_empty(stack->vec));
}

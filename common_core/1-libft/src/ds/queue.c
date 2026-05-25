
#include "libft.h"

/*
** =========================================================
** Queue — implementation (backed by t_dlist)
** =========================================================
*/

t_queue *ft_queue_create(void)
{
    t_queue *queue;

    queue = ft_malloc(sizeof(t_queue));
    if (!queue)
        return (NULL);
    queue->list = ft_dlist_create();
    if (!queue->list)
    {
        ft_free(queue);
        return (NULL);
    }
    return (queue);
}

void    ft_queue_destroy(t_queue *queue)
{
    if (!queue)
        return ;
    ft_dlist_destroy(queue->list);
    ft_free(queue);
}

void    ft_queue_destroy_deep(t_queue *queue, void (*free_fn)(void *))
{
    if (!queue)
        return ;
    ft_dlist_destroy_deep(queue->list, free_fn);
    ft_free(queue);
}

int ft_queue_enqueue(t_queue *queue, void *elem)
{
    if (!queue)
        return (0);
    return (ft_dlist_push_back(queue->list, elem));
}

void    *ft_queue_dequeue(t_queue *queue)
{
    if (!queue)
        return (NULL);
    return (ft_dlist_pop_front(queue->list));
}

void    *ft_queue_front(const t_queue *queue)
{
    if (!queue)
        return (NULL);
    return (ft_dlist_front(queue->list));
}

t_usize ft_queue_size(const t_queue *queue)
{
    if (!queue)
        return (0);
    return (ft_dlist_size(queue->list));
}

t_bool  ft_queue_empty(const t_queue *queue)
{
    return (!queue || ft_dlist_empty(queue->list));
}

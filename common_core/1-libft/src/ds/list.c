
#include "libft.h"

/*
** =========================================================
** Singly Linked List — implementation
** =========================================================
*/

/* ── Private ─────────────────────────────────────────── */

static t_slist_node *node_create(void *data)
{
    t_slist_node *node;

    node = ft_malloc(sizeof(t_slist_node));
    if (!node)
        return (NULL);
    node->data = data;
    node->next = NULL;
    return (node);
}

/* ── Lifecycle ───────────────────────────────────────── */

t_slist *ft_list_create(void)
{
    t_slist *list;

    list = ft_malloc(sizeof(t_slist));
    if (!list)
        return (NULL);
    list->head = NULL;
    list->size = 0;
    return (list);
}

void    ft_list_destroy(t_slist *list)
{
    t_slist_node *cur;
    t_slist_node *next;

    if (!list)
        return ;
    cur = list->head;
    while (cur)
    {
        next = cur->next;
        ft_free(cur);
        cur = next;
    }
    ft_free(list);
}

void    ft_list_destroy_deep(t_slist *list, void (*free_fn)(void *))
{
    t_slist_node *cur;
    t_slist_node *next;

    if (!list)
        return ;
    cur = list->head;
    while (cur)
    {
        next = cur->next;
        if (free_fn && cur->data)
            free_fn(cur->data);
        ft_free(cur);
        cur = next;
    }
    ft_free(list);
}

/* ── Insertion ───────────────────────────────────────── */

int ft_list_push_front(t_slist *list, void *data)
{
    t_slist_node *node;

    if (!list)
        return (0);
    node = node_create(data);
    if (!node)
        return (0);
    node->next = list->head;
    list->head = node;
    list->size++;
    return (1);
}

int ft_list_push_back(t_slist *list, void *data)
{
    t_slist_node *node;
    t_slist_node *cur;

    if (!list)
        return (0);
    node = node_create(data);
    if (!node)
        return (0);
    if (!list->head)
    {
        list->head = node;
    }
    else
    {
        cur = list->head;
        while (cur->next)
            cur = cur->next;
        cur->next = node;
    }
    list->size++;
    return (1);
}

int ft_list_insert_at(t_slist *list, t_usize index, void *data)
{
    t_slist_node *node;
    t_slist_node *cur;
    t_usize      i;

    if (!list || index > list->size)
        return (0);
    if (index == 0)
        return (ft_list_push_front(list, data));
    node = node_create(data);
    if (!node)
        return (0);
    cur = list->head;
    i = 0;
    while (i < index - 1)
    {
        cur = cur->next;
        i++;
    }
    node->next = cur->next;
    cur->next = node;
    list->size++;
    return (1);
}

/* ── Removal ─────────────────────────────────────────── */

void    *ft_list_pop_front(t_slist *list)
{
    t_slist_node *node;
    void        *data;

    if (!list || !list->head)
        return (NULL);
    node = list->head;
    data = node->data;
    list->head = node->next;
    ft_free(node);
    list->size--;
    return (data);
}

void    *ft_list_remove_at(t_slist *list, t_usize index)
{
    t_slist_node *prev;
    t_slist_node *target;
    void        *data;
    t_usize      i;

    if (!list || index >= list->size)
        return (NULL);
    if (index == 0)
        return (ft_list_pop_front(list));
    prev = list->head;
    i = 0;
    while (i < index - 1)
    {
        prev = prev->next;
        i++;
    }
    target = prev->next;
    data = target->data;
    prev->next = target->next;
    ft_free(target);
    list->size--;
    return (data);
}

/* ── Access ──────────────────────────────────────────── */

void    *ft_list_front(const t_slist *list)
{
    if (!list || !list->head)
        return (NULL);
    return (list->head->data);
}

void    *ft_list_get(const t_slist *list, t_usize index)
{
    t_slist_node *cur;
    t_usize      i;

    if (!list || index >= list->size)
        return (NULL);
    cur = list->head;
    i = 0;
    while (i < index)
    {
        cur = cur->next;
        i++;
    }
    return (cur->data);
}

/* ── Query ───────────────────────────────────────────── */

t_usize ft_list_size(const t_slist *list)
{
    if (!list)
        return (0);
    return (list->size);
}

t_bool  ft_list_empty(const t_slist *list)
{
    return (!list || list->size == 0);
}

/* ── Traversal ───────────────────────────────────────── */

void    ft_list_foreach(t_slist *list, void (*fn)(void *, void *), void *ctx)
{
    t_slist_node *cur;

    if (!list || !fn)
        return ;
    cur = list->head;
    while (cur)
    {
        fn(cur->data, ctx);
        cur = cur->next;
    }
}

/* ── Search ──────────────────────────────────────────── */

t_slist_node *ft_list_find(const t_slist *list, int (*pred)(void *, const void *),
                const void *ctx)
{
    t_slist_node *cur;

    if (!list || !pred)
        return (NULL);
    cur = list->head;
    while (cur)
    {
        if (pred(cur->data, ctx))
            return (cur);
        cur = cur->next;
    }
    return (NULL);
}

/* ── Mutation ────────────────────────────────────────── */

void    ft_list_reverse(t_slist *list)
{
    t_slist_node *prev;
    t_slist_node *cur;
    t_slist_node *next;

    if (!list || list->size <= 1)
        return ;
    prev = NULL;
    cur = list->head;
    while (cur)
    {
        next = cur->next;
        cur->next = prev;
        prev = cur;
        cur = next;
    }
    list->head = prev;
}

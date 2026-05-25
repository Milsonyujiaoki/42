
#include "libft.h"

/*
** =========================================================
** Doubly Linked List — implementation
** =========================================================
*/

/* ── Private ─────────────────────────────────────────── */

static t_dlist_node *node_create(void *data)
{
    t_dlist_node    *node;

    node = ft_malloc(sizeof(t_dlist_node));
    if (!node)
        return (NULL);
    node->data = data;
    node->prev = NULL;
    node->next = NULL;
    return (node);
}

/* Unlink node from the list without freeing it.
** Updates head/tail pointers as needed. */
static void node_unlink(t_dlist *list, t_dlist_node *node)
{
    if (node->prev)
        node->prev->next = node->next;
    else
        list->head = node->next;

    if (node->next)
        node->next->prev = node->prev;
    else
        list->tail = node->prev;

    node->prev = NULL;
    node->next = NULL;
    list->size--;
}

/* ── Lifecycle ───────────────────────────────────────── */

t_dlist *ft_dlist_create(void)
{
    t_dlist *list;

    list = ft_malloc(sizeof(t_dlist));
    if (!list)
        return (NULL);
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
    return (list);
}

void    ft_dlist_destroy(t_dlist *list)
{
    t_dlist_node    *cur;
    t_dlist_node    *next;

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

void    ft_dlist_destroy_deep(t_dlist *list, void (*free_fn)(void *))
{
    t_dlist_node    *cur;
    t_dlist_node    *next;

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

int ft_dlist_push_front(t_dlist *list, void *data)
{
    t_dlist_node    *node;

    if (!list)
        return (0);
    node = node_create(data);
    if (!node)
        return (0);
    node->next = list->head;
    if (list->head)
        list->head->prev = node;
    else
        list->tail = node;
    list->head = node;
    list->size++;
    return (1);
}

int ft_dlist_push_back(t_dlist *list, void *data)
{
    t_dlist_node    *node;

    if (!list)
        return (0);
    node = node_create(data);
    if (!node)
        return (0);
    node->prev = list->tail;
    if (list->tail)
        list->tail->next = node;
    else
        list->head = node;
    list->tail = node;
    list->size++;
    return (1);
}

int ft_dlist_insert_after(t_dlist *list, t_dlist_node *ref,
                void *data)
{
    t_dlist_node    *node;

    if (!list || !ref)
        return (0);
    if (!ref->next)
        return (ft_dlist_push_back(list, data));
    node = node_create(data);
    if (!node)
        return (0);
    node->prev = ref;
    node->next = ref->next;
    ref->next->prev = node;
    ref->next = node;
    list->size++;
    return (1);
}

int ft_dlist_insert_before(t_dlist *list, t_dlist_node *ref,
                void *data)
{
    t_dlist_node    *node;

    if (!list || !ref)
        return (0);
    if (!ref->prev)
        return (ft_dlist_push_front(list, data));
    node = node_create(data);
    if (!node)
        return (0);
    node->next = ref;
    node->prev = ref->prev;
    ref->prev->next = node;
    ref->prev = node;
    list->size++;
    return (1);
}

/* ── Removal ─────────────────────────────────────────── */

void    *ft_dlist_pop_front(t_dlist *list)
{
    t_dlist_node    *node;
    void            *data;

    if (!list || !list->head)
        return (NULL);
    node = list->head;
    data = node->data;
    node_unlink(list, node);
    ft_free(node);
    return (data);
}

void    *ft_dlist_pop_back(t_dlist *list)
{
    t_dlist_node    *node;
    void            *data;

    if (!list || !list->tail)
        return (NULL);
    node = list->tail;
    data = node->data;
    node_unlink(list, node);
    ft_free(node);
    return (data);
}

void    *ft_dlist_remove_node(t_dlist *list, t_dlist_node *node)
{
    void    *data;

    if (!list || !node)
        return (NULL);
    data = node->data;
    node_unlink(list, node);
    ft_free(node);
    return (data);
}

/* ── Access ──────────────────────────────────────────── */

void    *ft_dlist_front(const t_dlist *list)
{
    if (!list || !list->head)
        return (NULL);
    return (list->head->data);
}

void    *ft_dlist_back(const t_dlist *list)
{
    if (!list || !list->tail)
        return (NULL);
    return (list->tail->data);
}

/* ── Query ───────────────────────────────────────────── */

t_usize ft_dlist_size(const t_dlist *list)
{
    if (!list)
        return (0);
    return (list->size);
}

t_bool  ft_dlist_empty(const t_dlist *list)
{
    return (!list || list->size == 0);
}

/* ── Traversal ───────────────────────────────────────── */

void    ft_dlist_foreach(t_dlist *list, void (*fn)(void *, void *), void *ctx)
{
    t_dlist_node    *cur;

    if (!list || !fn)
        return ;
    cur = list->head;
    while (cur)
    {
        fn(cur->data, ctx);
        cur = cur->next;
    }
}

void    ft_dlist_foreach_reverse(t_dlist *list, void (*fn)(void *, void *), void *ctx)
{
    t_dlist_node    *cur;

    if (!list || !fn)
        return ;
    cur = list->tail;
    while (cur)
    {
        fn(cur->data, ctx);
        cur = cur->prev;
    }
}

/* ── Search ──────────────────────────────────────────── */

t_dlist_node    *ft_dlist_find(const t_dlist *list, int (*pred)(void *, const void *),
                    const void *ctx)
{
    t_dlist_node    *cur;

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

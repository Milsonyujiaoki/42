#ifndef LIBFT_H
# define LIBFT_H

# include <stddef.h>
# include <stdint.h>
# include <stdbool.h>
# include <stdarg.h>

/* ═══════════════════════════════════════════════════════════════════════════
** §1  CORE — primitive type aliases
** ═══════════════════════════════════════════════════════════════════════════ */

typedef uint8_t       t_u8;
typedef uint16_t      t_u16;
typedef uint32_t      t_u32;
typedef uint64_t      t_u64;

typedef int8_t        t_i8;
typedef int16_t       t_i16;
typedef int32_t       t_i32;
typedef int64_t       t_i64;

typedef float         t_f32;
typedef double        t_f64;

typedef size_t        t_usize;
typedef ptrdiff_t     t_isize;

typedef uintptr_t     t_uptr;
typedef intptr_t      t_iptr;

typedef bool          t_bool;
typedef unsigned char t_byte;

/* ═══════════════════════════════════════════════════════════════════════════
** §2  CTYPE — character classification and case conversion
** ═══════════════════════════════════════════════════════════════════════════ */

int   ft_isdigit(int c);
int   ft_isxdigit(int c);
int   ft_islower(int c);
int   ft_isupper(int c);
int   ft_isascii(int c);
int   ft_isalpha(int c);
int   ft_isalnum(int c);
int   ft_isprint(int c);
int   ft_isspace(int c);
int   ft_isblank(int c);
int   ft_isgraph(int c);
int   ft_iscntrl(int c);
int   ft_ispunct(int c);

int   ft_toupper(int c);
int   ft_tolower(int c);

/* ═══════════════════════════════════════════════════════════════════════════
** §3  MEMORY — raw memory operations
** ═══════════════════════════════════════════════════════════════════════════ */

void  *ft_memset(void *dest, int ch, size_t count);
void  *ft_memcpy(void *dest, const void *src, size_t count);
void  *ft_memccpy(void *restrict dest, const void *restrict src, int c, size_t count);
void  *ft_memmove(void *dest, const void *src, size_t count);
int    ft_memcmp(const void *lhs, const void *rhs, size_t count);
void  *ft_memchr(const void *ptr, int value, size_t count);
void  *ft_bzero(void *ptr, size_t count);

/* ═══════════════════════════════════════════════════════════════════════════
** §4  ALLOC — general-purpose allocators
**
** Ownership contract:
**   ft_malloc / ft_calloc  — caller owns the returned pointer
**   ft_realloc             — may invalidate the original pointer
**   ft_free                — releases ownership; pointer is invalid after
** ═══════════════════════════════════════════════════════════════════════════ */

void  *ft_malloc(t_usize size);
void  *ft_calloc(t_usize count, t_usize size);
void  *ft_realloc(void *ptr, t_usize new_size);
void   ft_free(void *ptr);
void  *ft_realloc_safe(void **ptr, t_usize new_size);

/* ═══════════════════════════════════════════════════════════════════════════
** §5  STRING — examination and manipulation
** ═══════════════════════════════════════════════════════════════════════════ */

size_t  ft_strlen(const char *str);
int     ft_strcmp(const char *lhs, const char *rhs);
int     ft_strncmp(const char *lhs, const char *rhs, size_t count);
char   *ft_strchr(const char *str, int ch);
char   *ft_strrchr(const char *str, int ch);
char   *ft_strstr(const char *str, const char *substr);
char   *ft_strtok(char *restrict str, const char *restrict delim);

char   *ft_strcpy(char *dest, const char *src);
char   *ft_strcpy_fast(char *dest, const char *src);
char   *ft_strcpy_v2(char *dest, const char *src);
char   *ft_strncpy(char *dest, const char *src, size_t count);
size_t  ft_strlcpy(char *dst, const char *src, size_t size);
char   *ft_strdup(const char *src);
char   *ft_strndup(const char *src, size_t count);
char   *ft_strcat(char *dest, const char *src);
size_t  ft_strlcat(char *dst, const char *src, size_t size);
char   *ft_strncat(char *dest, const char *src, size_t count);

char   *ft_substr(const char *str, unsigned int start, size_t len);
char   *ft_strjoin(const char *s1, const char *s2);
char   *ft_strtrim(const char *str, const char *set);
char  **ft_strsplit(const char *str, char delimiter);
char   *ft_strmapi(const char *str, char (*f)(unsigned int, char));
void    ft_striteri(char *str, void (*f)(unsigned int, char *));

/* ═══════════════════════════════════════════════════════════════════════════
** §6  STDLIB — numeric conversions
** ═══════════════════════════════════════════════════════════════════════════ */

int        ft_atoi(const char *str);
long       ft_atol(const char *str);
long long  ft_atoll(const char *str);
double     ft_atof(const char *str);
char      *ft_itoa(int n);

/* ═══════════════════════════════════════════════════════════════════════════
** §7  I/O — character, string, and formatted output
** ═══════════════════════════════════════════════════════════════════════════ */

int   ft_putchar(int c);
int   ft_getchar(void);
int   ft_puts(const char *str);

void  ft_putchar_fd(char c, int fd);
void  ft_putstr_fd(const char *str, int fd);
void  ft_putendl_fd(const char *str, int fd);
void  ft_putnbr_fd(int n, int fd);

int   ft_printf(const char *fmt, ...);
int   ft_sprintf(char *buf, const char *fmt, ...);
int   ft_snprintf(char *buf, t_usize size, const char *fmt, ...);

/* ═══════════════════════════════════════════════════════════════════════════
** §8  DATA STRUCTURES
** ═══════════════════════════════════════════════════════════════════════════ */

/* ── §8.1  t_list  ─────────────────────────────────────────────────────────
** Singly-linked list — required by the 42 norm.
** ft_lst* functions operate on this type.
** ─────────────────────────────────────────────────────────────────────────*/

typedef struct s_list
{
	void            *content;
	struct s_list   *next;
}   t_list;

t_list  *ft_lstnew(void *content);
void     ft_lstadd_front(t_list **lst, t_list *new_node);
int      ft_lstsize(t_list *lst);
t_list  *ft_lstlast(t_list *lst);
void     ft_lstadd_back(t_list **lst, t_list *new_node);
void     ft_lstdelone(t_list *lst, void (*del)(void *));
void     ft_lstclear(t_list **lst, void (*del)(void *));
void     ft_lstiter(t_list *lst, void (*f)(void *));
t_list  *ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));

void     ft_print_list(t_list *lst);
void     ft_printf_lst(t_list *lst, void (*print_data)(void *));

/* ── §8.2  t_slist  ────────────────────────────────────────────────────────
** Generic singly-linked list — O(1) push/pop front, O(1) size.
** ─────────────────────────────────────────────────────────────────────────*/

typedef struct s_slist_node
{
	void                *data;
	struct s_slist_node *next;
}   t_slist_node;

typedef struct s_slist
{
	t_slist_node *head;
	t_usize       size;
}   t_slist;

t_slist      *ft_list_create(void);
void          ft_list_destroy(t_slist *list);
void          ft_list_destroy_deep(t_slist *list, void (*free_fn)(void *));

int           ft_list_push_front(t_slist *list, void *data);
int           ft_list_push_back(t_slist *list, void *data);
int           ft_list_insert_at(t_slist *list, t_usize index, void *data);

void         *ft_list_pop_front(t_slist *list);
void         *ft_list_remove_at(t_slist *list, t_usize index);

void         *ft_list_front(const t_slist *list);
void         *ft_list_get(const t_slist *list, t_usize index);

t_usize       ft_list_size(const t_slist *list);
t_bool        ft_list_empty(const t_slist *list);

void          ft_list_foreach(t_slist *list, void (*fn)(void *, void *), void *ctx);

t_slist_node *ft_list_find(const t_slist *list, int (*pred)(void *, const void *),
                const void *ctx);

void          ft_list_reverse(t_slist *list);

/* ── §8.3  t_dlist  ────────────────────────────────────────────────────────
** Doubly-linked list — O(1) push/pop both ends, bidirectional traversal.
** ─────────────────────────────────────────────────────────────────────────*/

typedef struct s_dlist_node
{
	void                *data;
	struct s_dlist_node *prev;
	struct s_dlist_node *next;
}   t_dlist_node;

typedef struct s_dlist
{
	t_dlist_node *head;
	t_dlist_node *tail;
	t_usize       size;
}   t_dlist;

t_dlist      *ft_dlist_create(void);
void          ft_dlist_destroy(t_dlist *list);
void          ft_dlist_destroy_deep(t_dlist *list, void (*free_fn)(void *));

int           ft_dlist_push_front(t_dlist *list, void *data);
int           ft_dlist_push_back(t_dlist *list, void *data);
int           ft_dlist_insert_after(t_dlist *list, t_dlist_node *node, void *data);
int           ft_dlist_insert_before(t_dlist *list, t_dlist_node *node, void *data);

void         *ft_dlist_pop_front(t_dlist *list);
void         *ft_dlist_pop_back(t_dlist *list);
void         *ft_dlist_remove_node(t_dlist *list, t_dlist_node *node);

void         *ft_dlist_front(const t_dlist *list);
void         *ft_dlist_back(const t_dlist *list);

t_usize       ft_dlist_size(const t_dlist *list);
t_bool        ft_dlist_empty(const t_dlist *list);

void          ft_dlist_foreach(t_dlist *list, void (*fn)(void *, void *), void *ctx);
void          ft_dlist_foreach_reverse(t_dlist *list, void (*fn)(void *, void *), void *ctx);

t_dlist_node *ft_dlist_find(const t_dlist *list, int (*pred)(void *, const void *),
                const void *ctx);

/* ── §8.4  t_vector  ───────────────────────────────────────────────────────
** Dynamic contiguous array — O(1) amortised push/pop back, O(1) random access.
** Elements stored by value; elem_size must be provided at creation.
** ─────────────────────────────────────────────────────────────────────────*/

# define LIBFT_VECTOR_INIT_CAPACITY  8
# define LIBFT_VECTOR_GROW_FACTOR    2

typedef struct s_vector
{
	void    *data;
	t_usize  elem_size;
	t_usize  size;
	t_usize  capacity;
}   t_vector;

t_vector *ft_vector_create(t_usize elem_size);
t_vector *ft_vector_create_cap(t_usize elem_size, t_usize capacity);
void      ft_vector_destroy(t_vector *vec);
void      ft_vector_destroy_deep(t_vector *vec, void (*free_fn)(void *));

int       ft_vector_push(t_vector *vec, const void *elem);
int       ft_vector_pop(t_vector *vec, void *out);
int       ft_vector_insert(t_vector *vec, t_usize index, const void *elem);
int       ft_vector_remove(t_vector *vec, t_usize index);

void     *ft_vector_get(const t_vector *vec, t_usize index);
void     *ft_vector_front(const t_vector *vec);
void     *ft_vector_back(const t_vector *vec);
int       ft_vector_set(t_vector *vec, t_usize index, const void *elem);

t_usize   ft_vector_size(const t_vector *vec);
t_usize   ft_vector_capacity(const t_vector *vec);
t_bool    ft_vector_empty(const t_vector *vec);

int       ft_vector_reserve(t_vector *vec, t_usize new_capacity);
int       ft_vector_shrink(t_vector *vec);
void      ft_vector_clear(t_vector *vec);

void      ft_vector_foreach(t_vector *vec, void (*fn)(void *, void *), void *ctx);
t_isize   ft_vector_find(const t_vector *vec, int (*pred)(void *, const void *),
              const void *ctx);

/* ── §8.5  t_stack  ────────────────────────────────────────────────────────
** LIFO stack backed by t_vector — O(1) amortised push/pop.
** ─────────────────────────────────────────────────────────────────────────*/

typedef struct s_stack
{
	t_vector *vec;
}   t_stack;

t_stack  *ft_stack_create(t_usize elem_size);
void      ft_stack_destroy(t_stack *stack);
void      ft_stack_destroy_deep(t_stack *stack, void (*free_fn)(void *));

int       ft_stack_push(t_stack *stack, const void *elem);
int       ft_stack_pop(t_stack *stack, void *out);
void     *ft_stack_peek(const t_stack *stack);

t_usize   ft_stack_size(const t_stack *stack);
t_bool    ft_stack_empty(const t_stack *stack);

/* ── §8.6  t_queue  ────────────────────────────────────────────────────────
** FIFO queue backed by t_dlist — O(1) enqueue and dequeue.
** ─────────────────────────────────────────────────────────────────────────*/

typedef struct s_queue
{
	t_dlist *list;
}   t_queue;

t_queue  *ft_queue_create(void);
void      ft_queue_destroy(t_queue *queue);
void      ft_queue_destroy_deep(t_queue *queue, void (*free_fn)(void *));

int       ft_queue_enqueue(t_queue *queue, void *elem);
void     *ft_queue_dequeue(t_queue *queue);
void     *ft_queue_front(const t_queue *queue);

t_usize   ft_queue_size(const t_queue *queue);
t_bool    ft_queue_empty(const t_queue *queue);

#endif /* LIBFT_H */

*This project has been created as part of the 42 curriculum by Milsonyujiaoki.*

# ft_printf

## Description

Reimplementação da função `printf` da libc em C puro, construída sobre a
[libft](./libft/README.md) pessoal.

A função suporta as seguintes conversões: `%c` `%s` `%p` `%d` `%i` `%u` `%x` `%X` `%%`

O resultado é empacotado na biblioteca estática `libftprintf.a`.

## Instructions

### Compilar a biblioteca

```bash
make          # compila libftprintf.a em build/static/
```

A libft é compilada automaticamente via `$(MAKE) -C libft static`.

### Rodar os testes

```bash
make test     # compila e executa tests/test_ftprintf.c
```

### Linkar na sua aplicação

```bash
cc main.c \
  -Iinclude -Ilibft/include \
  -Lbuild/static -lftprintf \
  -Llibft/build/static -lft \
  -o programa
```

### Targets disponíveis

| Target      | Efeito                                      |
|-------------|---------------------------------------------|
| `all`       | Compila `libftprintf.a`                     |
| `test`      | Compila e executa a suíte de testes         |
| `clean`     | Remove objetos (`.o`) do ft_printf e libft  |
| `fclean`    | `clean` + remove a lib e o binário de teste |
| `re`        | `fclean` + `all`                            |

## Algorithm & Data Structure

### Algoritmo principal (`ft_printf`)

O loop percorre a string de formato caractere a caractere:

1. Se o caractere **não é `%`** → escreve direto com `ft_putchar_fd` e incrementa o contador.
2. Se é `%` → avança um caractere e chama `dispatch(spec, args)`.

`dispatch` é uma cadeia de `if/return` que mapeia o especificador para a
função de conversão correta. Não há tabela de ponteiros nem `switch` —
a simplicidade é intencional para facilitar a leitura e a manutenção.
```
ft_printf
   │
   ├── loop format string
   │
   ├── char normal ──> write
   │
   └── '%' encontrado
            │
            └── dispatch(specifier)
                     │
                     ├── %c -> print_char
                     ├── %s -> print_str
                     ├── %d -> print_int
                     ├── %x -> print_hex
                     └── ...
```

### Funções de conversão

Cada especificador tem seu próprio arquivo em `src/conversions/`. Todas
recebem `va_list args` e retornam o número de caracteres escritos.

| Especificador | Arquivo            | Estratégia                                              |
|---------------|--------------------|---------------------------------------------------------|
| `%c`          | `print_char.c`     | `va_arg` → `ft_putchar_fd`                              |
| `%s`          | `print_str.c`      | `va_arg` → guarda `"(null)"` se NULL → `ft_putstr_fd`  |
| `%d` / `%i`   | `print_int.c`      | `ft_itoa` → `ft_putstr_fd` → `ft_free` ft_itoa aloca uma string temporária que é liberada imediatamente após a escrita.                |
| `%u`          | `print_uint.c`     | recursão simples, dígito a dígito                       |
| `%x` / `%X`   | `print_hex.c`      | recursão com base `"0123456789abcdef"` ou `"ABCDEF"`    |
| `%p`          | `print_ptr.c`      | prefixo `"0x"` + recursão hex sobre `unsigned long`     |
| `%%`          | `print_percent.c`  | escreve `'%'` direto                                    |

A recursão para `%u`, `%x` e `%p` é a estrutura mais natural para
conversão de base: resolve os dígitos do mais significativo para o
menos significativo sem precisar de buffer ou reversão de string.

## Structure

```
src/
  conversions/   # print_char, print_str, print_int, print_uint,
                 # print_hex, print_ptr, print_percent
  core/          # ft_printf.c — loop principal + dispatch
include/
  ft_printf.h    # protótipo público + protótipos internos
libft/           # dependência — compilada como estática
tests/
  test_ftprintf.c
build/
  static/        # libftprintf.a
  obj/static/    # arquivos objeto
```

## Resources

- [man 3 printf](https://www.man7.org/linux/man-pages/man3/printf.3.html) — especificação de comportamento esperado
- [cppreference — va_arg](https://en.cppreference.com/w/c/variadic) — funções variádicas em C
- [42 Norm v4](https://github.com/42School/norminette) — norma de estilo obrigatória

### Uso de IA

O GitHub Copilot foi utilizado como ferramenta de auxílio nos seguintes aspectos:

- **Makefile**: estrutura de regras com `patsubst`, `wildcard` e compilação em cascata da libft.
- **Testes**: geração dos casos de teste comparativos entre `ft_printf` e `printf`.
- **Depuração de includes**: identificação do caminho correto de include dado o `-I` do CPPFLAGS.

Todo o algoritmo central, as conversões e a lógica de dispatch foram raciocidados e implementados manualmente antes de qualquer consulta à IA.


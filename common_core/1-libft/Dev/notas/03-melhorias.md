1. Symbol visibility
2. API versioning
3. Header organization
4. Tests
5. Sanitizers
6. Benchmarks
7. Internal/private API separation
8. Documentation
9. Typed/generic containers
10. Hashmap


## Algo MUITO importante que você pode melhorar agora
Controle de visibilidade de símbolos

Hoje:
quase tudo é exportado.

Isso aumenta:

tamanho da .dynsym
tempo de dynamic linking
risco de symbol collision
surface area da API
acoplamento
Como libs profissionais fazem

Elas exportam apenas:

API pública

E escondem:

helpers internos
experimental APIs
private utilities
Como fazer isso
GCC Visibility

Compile com:

-fvisibility=hidden

E exporte explicitamente:

__attribute__((visibility("default")))
Exemplo
libft_export.h
#ifndef LIBFT_EXPORT_H
# define LIBFT_EXPORT_H

# define FT_API __attribute__((visibility("default")))

#endif
header público
FT_API void *ft_malloc(size_t size);
FT_API void ft_free(void *ptr);
helper interno
static void internal_helper(void)
{
}

ou

void helper(void)
{
}

sem FT_API.

Resultado

Sua .dynsym cai drasticamente.

Shared library mais profissional.

Outra melhoria MUITO importante
Versionamento de API

Você já está num tamanho onde isso importa.

Exemplo:

libft.so
libft.so.1
libft.so.1.0.0
Estrutura profissional
build/
├── static/
│   └── libft.a
│
├── shared/
│   ├── libft.so
│   ├── libft.so.1
│   └── libft.so.1.0.0
Outra observação importante

Você tem:

ft_strcpy
ft_strcpy_v2

Isso normalmente indica:

evolução experimental
API temporária
benchmark/testing variant

Em projetos profissionais, melhor:

ft_strcpy_fast
ft_strcpy_safe
ft_strcpy_simd

ou manter interno.


Vou fazer uma análise do projeto para criar um plano bem estruturado. Deixa eu explorar a estrutura atual, símbolos exportados e configurações do Makefile. 

Analisar estrutura do projeto libft

Read [](file:///home/dev_yuji/Dev/libft/include)

Read [](file:///home/dev_yuji/Dev/libft/build)

Read [](file:///home/dev_yuji/Dev/libft/Makefile)

Searched for files matching `libft` · `include/**/*.h`, 20 matches

Read [](file:///home/dev_yuji/Dev/libft/include/core)

Read [](file:///home/dev_yuji/Dev/libft/include/ds)

Read [](file:///home/dev_yuji/Dev/libft/include/algo)

Read [](file:///home/dev_yuji/Dev/libft/include/sys)

Read [](file:///home/dev_yuji/Dev/libft/include/memory)

Read [](file:///home/dev_yuji/Dev/libft/include/string)

Read [](file:///home/dev_yuji/Dev/libft/include/io)

Read [](file:///home/dev_yuji/Dev/libft/include/libft.h)

Read [](file:///home/dev_yuji/Dev/libft/include/memory/memory.h)

Read [](file:///home/dev_yuji/Dev/libft/include/memory/alloc.h)

Read [](file:///home/dev_yuji/Dev/libft/include/memory/arena.h)

Read [](file:///home/dev_yuji/Dev/libft/include/memory/buffer.h)

Read [](file:///home/dev_yuji/Dev/libft/include/string/string.h)

Read [](file:///home/dev_yuji/Dev/libft/include/string/string_builder.h)

Read [](file:///home/dev_yuji/Dev/libft/include/string/string_view.h)

Read [](file:///home/dev_yuji/Dev/libft/include/memory/pool.h)

Read [](file:///home/dev_yuji/Dev/libft/include/ds/slist.h)

Read [](file:///home/dev_yuji/Dev/libft/include/ds/dlist.h)

Read [](file:///home/dev_yuji/Dev/libft/include/ds/vector.h)

Read [](file:///home/dev_yuji/Dev/libft/include/ds/stack.h)

Read [](file:///home/dev_yuji/Dev/libft/include/ds/queue.h)

Read [](file:///home/dev_yuji/Dev/libft/include/ds/list.h)

Read [](file:///home/dev_yuji/Dev/libft/include/algo/compare.h)

Read [](file:///home/dev_yuji/Dev/libft/include/algo/hash.h)

Read [](file:///home/dev_yuji/Dev/libft/include/algo/sort.h)

Read [](file:///home/dev_yuji/Dev/libft/include/algo/search.h)

Read [](file:///home/dev_yuji/Dev/libft/include/core/stdlib-ft.h)

Read [](file:///home/dev_yuji/Dev/libft/include/io/stdio.h)

Read [](file:///home/dev_yuji/Dev/libft/include/io/file.h)

Read [](file:///home/dev_yuji/Dev/libft/include/sys/errno.h)

Read [](file:///home/dev_yuji/Dev/libft/include/sys/unistd.h)

Read [](file:///home/dev_yuji/Dev/libft/include/internal/internal.h)

Read [](file:///home/dev_yuji/Dev/libft/include/internal/debug.h)

Read [](file:///home/dev_yuji/Dev/libft/include/internal/platform.h)

Read [](file:///home/dev_yuji/Dev/libft/include/core/ctype.h)

Searched for regex `_v2|_fast|_safe` (`**/*.{h,c,md,make}`), 10 results

Searched for regex `visibility|fvisibility|__attribute__\s*\(\(visibility|EXPORT|__declspec` (`**/*.{h,c,md,make}`), 21 results

Read [](file:///home/dev_yuji/Dev/libft/build/static)

Read [](file:///home/dev_yuji/Dev/libft/build/shared)

Read [](file:///home/dev_yuji/Dev/libft/build/obj)

Read [](file:///home/dev_yuji/Dev/libft/build/obj/static)

Read [](file:///home/dev_yuji/Dev/libft/build/obj/shared)

Searched for regex `LIBFT_API|LIBFT_HIDDEN` (`**/*.{h,c,md,make}`), 4 results

Searched for files matching `libft` · `build/obj/**/*.o`, no matches

Searched for files matching `libft` · `build/obj/**/*.d`, no matches

Read [](file:///home/dev_yuji/Dev/libft/include/core/compiler.h)

Read [](file:///home/dev_yuji/Dev/libft/build/obj/static/algo)

Read [](file:///home/dev_yuji/Dev/libft/build/obj/static/ctype)

Read [](file:///home/dev_yuji/Dev/libft/build/obj/static/ds)

Read [](file:///home/dev_yuji/Dev/libft/build/obj/static/internal)

Read [](file:///home/dev_yuji/Dev/libft/build/obj/static/memory)

Read [](file:///home/dev_yuji/Dev/libft/build/obj/static/stdio)

Read [](file:///home/dev_yuji/Dev/libft/build/obj/static/stdlib)

Read [](file:///home/dev_yuji/Dev/libft/build/obj/static/string)

Read [](file:///home/dev_yuji/Dev/libft/build/obj/static/unistd)

Read [](file:///home/dev_yuji/Dev/libft/build/obj/shared/algo)

Read [](file:///home/dev_yuji/Dev/libft/build/obj/shared/ctype)

Read [](file:///home/dev_yuji/Dev/libft/build/obj/shared/ds)

Read [](file:///home/dev_yuji/Dev/libft/build/obj/shared/internal)

Read [](file:///home/dev_yuji/Dev/libft/build/obj/shared/memory)

Read [](file:///home/dev_yuji/Dev/libft/build/obj/shared/stdio)

Read [](file:///home/dev_yuji/Dev/libft/build/obj/shared/stdlib)

Read [](file:///home/dev_yuji/Dev/libft/build/obj/shared/string)

Read [](file:///home/dev_yuji/Dev/libft/build/obj/shared/unistd)

Searched for regex `CFLAGS|PIC_FLAGS|SHARED_LIB|STATIC_LIB` (`**/Makefile`), 20 results

Searched for regex `LIBFT_API|LIBFT_HIDDEN` (`**/include/core/compiler.h`), 4 results

Searched for regex `ft_strcpy_v2|ft_realloc_safe` (`**/include/**/*.h`), 3 results

Searched for regex `ft_strcpy_v2|ft_realloc_safe` (`**/src/**/*.c`), 4 results

Searched for regex `ft_strcpy_fast|ft_strcpy_safe` (`**/*.{h,c,md,make}`), 2 results

Read memory

Created memory file [](file:///home/dev_yuji/.vscode-server/data/User/workspaceStorage/4cff17e067c9cbcff9692b54141cb8c7/GitHub.copilot-chat/memory-tool/memories/repo/libft.md)

Read [](file:///home/dev_yuji/Dev/libft/include/ds/slist.h)

Excelente! Agora tenho mapeamento completo do projeto. Vou criar um plano bem estruturado com foco em:

1. **Visibilidade de símbolos** (o ganho mais imediato)
2. **Cleanup de nomes duplicados** (ft_strcpy_v2, ft_realloc_safe)
3. **Versionamento de biblioteca compartilhada**
4. **Documentação e code comments** humanos

Deixa eu esclarecer um ponto importante antes de formalizar o plano: 

Analisando suas respostas...

Perfeito! Agora vou criar o plano detalhado: 

Read memory

Created memory file [](file:///home/dev_yuji/.vscode-server/data/User/workspaceStorage/4cff17e067c9cbcff9692b54141cb8c7/GitHub.copilot-chat/memory-tool/memories/N2Y2MzI4NWQtYzFiZC00ZGJlLWFkNjItY2I5MjA0NWIyYTlj/plan.md)

---

## 📋 Plano: Aplicar Melhorias de Visibilidade de Símbolos ao libft

**TL;DR:** Implementar visibilidade oculta por padrão (`-fvisibility=hidden`) e exportar explicitamente apenas a API pública com `LIBFT_API`. Resultado: biblioteca profissional, símbolos privados reais, .dynsym reduzido, código bem documentado.

---

### **Estrutura em 5 Fases**

#### **Fase 1: Preparação** (baseline de referência)
- Validar que projeto compila sem erros
- Registrar tamanho atual de libft.so e símbolos exportados
- Garantir macros `LIBFT_API` / `LIBFT_HIDDEN` já existem em compiler.h

#### **Fase 2: Configuração no Makefile** (habilitar ocultação)
- Adicionar `-fvisibility=hidden` aos CFLAGS
- Adicionar `-Wl,--exclude-libs,ALL` ao LDFLAGS
- Documentar com comentários o porquê de cada flag

#### **Fase 3: Marcar API Pública** (23 headers, 150+ funções)
- Aplicar `LIBFT_API` a cada função pública
- Organizado por módulo (ctype → memory → string → ds → algo → io → sys)
- Padrão: decorar declaration + adicionar comentário breve

#### **Fase 4: Documentação Humana** (paralelo com Fase 3)
- Bloco de comentário no início de cada header explicando o módulo
- Comentário acima de cada função: propósito, comportamento, notas de uso
- Código humano e legível

#### **Fase 5: Versionamento** (preparação para futuro)
- Criar infraestrutura de versioning sem modificar build
- Deixar pronto para implementação em próxima melhoria

---

### **Arquivos Críticos a Modificar**

| Prioridade | Arquivo | Funções | Fase |
|-----------|---------|---------|------|
| 🔴 Alto | Makefile | CFLAGS, LDFLAGS | 2 |
| 🔴 Alto | compiler.h | Validar macros | 2 |
| 🟡 Médio | ctype.h | 15 funções | 3–4 |
| 🟡 Médio | alloc.h | 5 funções | 3–4 |
| 🟡 Médio | string.h | 17 funções | 3–4 |
| 🟢 Normal | include/ds/\*.h | 75+ funções | 3–4 |
| 🟢 Normal | include/algo/\*.h | 19 funções | 3–4 |
| 🟢 Normal | include/memory/\*.h | 36 funções | 3–4 |
| 🟢 Normal | string_view.h | 14 funções | 3–4 |
| 🟢 Normal | include/io/\*.h | 14 funções | 3–4 |
| 🟢 Normal | include/sys/\*.h | 4 funções | 3–4 |

---

### **Decisões Alinhadas com Você**

✅ **Visibilidade** — Foco principal desta melhoria  
✅ **Listas paralelas** — Manter slist.h e list.h com documentação clara  
⏸️ **Cleanup ft_strcpy_v2** — Não incluído neste plano  
⏸️ **Versionamento real** — Apenas infraestrutura

---

### **Exemplo de Mudança (antes/depois)**

**Antes** (sem visibilidade):
```c
// include/memory/memory.h
void *ft_memcpy(void *dst, const void *src, size_t n);
void *ft_memset(void *b, int c, size_t len);
```

**Depois** (com visibilidade + docs):
```c
/**
 * ============================================================
 * FUNÇÕES DE MANIPULAÇÃO DE MEMÓRIA BRUTA
 * ============================================================
 * 
 * Este módulo fornece operações de baixo nível em blocos
 * contíguos de memória: cópia, comparação, busca, zeramento.
 * 
 * IMPORTANTE: Nenhuma função valida bounds. O caller é
 * responsável por garantir que o tamanho não ultrapassa
 * a região alocada.
 */

/* Copia n bytes de src para dst. NÃO lida com sobreposição. */
LIBFT_API void *ft_memcpy(void *dst, const void *src, size_t n);

/* Preenche uma região de memória com um byte. Exemplo: ft_bzero usa c=0. */
LIBFT_API void *ft_memset(void *b, int c, size_t len);
```

---

### **Testes de Validação**

| Quando | Comando | Esperado |
|--------|---------|----------|
| Antes | `nm -D libft.so \| grep " T " \| wc -l` | ~150 símbolos |
| Depois | `nm -D libft.so \| grep " T " \| wc -l` | 0 ou <10 (só LIBFT_API) |
| Depois | `make test` | Todos os testes passam |

---

**Pronto para começar?** Confirma que o plano faz sentido, e parto para **Fase 1** (validação baseline).
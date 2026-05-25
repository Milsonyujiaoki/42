# Fase 3 Manual - Marcar API Publica com LIBFT_API

Este guia mostra como aplicar manualmente a Fase 3:
- decorar declaracoes publicas com LIBFT_API;
- manter funcoes internas sem LIBFT_API;
- validar compilacao e exportacao de simbolos a cada etapa.

## 1) Objetivo tecnico

Quando a biblioteca usa controle de visibilidade, a API publica precisa estar explicita.
Neste projeto, o macro ja existe em include/core/compiler.h:
- LIBFT_API
- LIBFT_HIDDEN

Regra principal:
- funcao publica de header publico: usar LIBFT_API
- helper interno/privado: nao usar LIBFT_API

## 2) Ordem recomendada por modulo

Aplique nesta ordem para reduzir risco:
1. ctype
2. memory
3. string
4. ds
5. algo
6. io
7. sys

## 3) Padrao de alteracao

Antes:
void *ft_memcpy(void *dst, const void *src, size_t n);

Depois:
LIBFT_API void *ft_memcpy(void *dst, const void *src, size_t n);

Padrao de comentario breve (opcional, recomendado):
- uma linha explicando o que a funcao faz;
- sem repetir o obvio.

## 4) Garantir acesso ao macro

Cada header publico alterado deve conseguir ver LIBFT_API.
Se o header ainda nao inclui o compilador, adicione:

#include "../core/compiler.h"

Observacao:
- se o header ja recebe isso por outra include chain, ainda prefira incluir diretamente para robustez.

## 5) Execucao modulo a modulo

Para cada modulo:
1. editar headers do modulo e adicionar LIBFT_API nas declaracoes publicas;
2. revisar para nao marcar helpers internos;
3. compilar;
4. rodar testes;
5. inspecionar simbolos exportados.

Comandos:
- make clean && make shared
- make test
- nm -D build/shared/libft.so.1.0.0 | grep " T ft_"

## 6) Checklist por grupo de headers

Core:
- include/core/ctype.h
- include/core/stdlib-ft.h

Memory:
- include/memory/memory.h
- include/memory/alloc.h
- include/memory/arena.h
- include/memory/pool.h
- include/memory/buffer.h

String:
- include/string/string.h
- include/string/string_view.h
- include/string/string_builder.h

DS:
- include/ds/slist.h
- include/ds/list.h
- include/ds/dlist.h
- include/ds/vector.h
- include/ds/stack.h
- include/ds/queue.h

Algo:
- include/algo/compare.h
- include/algo/hash.h
- include/algo/sort.h
- include/algo/search.h

IO:
- include/io/stdio.h
- include/io/file.h

Sys:
- include/sys/errno.h
- include/sys/unistd.h

## 7) O que NAO marcar

Nao adicionar LIBFT_API em:
- funcoes static em .c;
- helpers privados em include/internal;
- utilitarios experimentais que voce nao quer na API publica.

## 8) Validacao final

Ao terminar todos os modulos:
1. make clean && make all
2. make test
3. nm -D build/shared/libft.so.1.0.0 | grep " T " | wc -l
4. revisar lista final exportada:
   nm -D build/shared/libft.so.1.0.0 | grep " T "

Se tudo estiver correto:
- testes devem passar;
- simbolos exportados devem refletir apenas a API que voce decidiu manter publica.

## 9) Dica de seguranca de mudanca

Use commits pequenos por modulo.
Exemplo:
- commit 1: ctype + validacao
- commit 2: memory + validacao
- commit 3: string + validacao
...

Isso facilita rollback e review.

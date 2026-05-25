1. Explorar ELF
readelf -a build/shared/libft.so

2. Explorar symbols
nm build/shared/libft.so
T → função exportada
t → função local/internal
D → variável global inicializada
B → variável global não inicializada
R → read-only data
U → símbolo indefinido (vem de outra biblioteca)

Então futuramente você pode usar:
-fvisibility=hidden

e exportar só a API pública.

Exemplo
__attribute__((visibility("default")))
int ft_strlen(const char *s);

Isso reduz:
colisão de símbolos;
tempo de linking;
tamanho da tabela ELF;
problemas de ABI (Application Binary Interface).

3. Runtime dependencies
ldd build/shared/libft.so
4. Dynamic loading
dlopen()
dlsym()
5. pkg-config
libft.pc
6. Symbol visibility
-fvisibility=hidden
7. readelf

Ferramenta avançada para inspecionar ELF.

Exemplo
readelf -a libft.so

Você verá:

symbol tables;
relocation tables;
ELF headers;
sections;
dynamic linking info.
Isso mostra:

.dynsym
→ símbolos exportados dinamicamente
→ API pública da shared library
.symtab
→ tabela completa
→ inclui símbolos locais/internal helpers

8. objdump

Ferramenta para desmontar/analisar binários.

Exemplo
objdump -d libft.so

Mostra:

assembly real

## Dependency Generation (-MMD -MP)

Isso resolve um problema MUITO importante.

Sem isso

Imagine:

libft.h mudou

mas:

ft_strlen.o

não recompila.

Você fica com:

binary inconsistency
Com:
-MMD -MP

o GCC (GNU Compiler Collection) gera:

.d files

com dependências reais.


## Install / Uninstall

Quando você faz:

make install

sua biblioteca vira:

system-wide library
Exemplo
/usr/local/lib/libft.so
/usr/local/include/libft.h
Isso permite:
gcc main.c -lft

globalmente.
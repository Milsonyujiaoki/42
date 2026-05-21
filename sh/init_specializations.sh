#!/bin/bash
# Cria estrutura inicial para projetos de specializations

set -e

GITHUB_USER="Milsonyujiaoki"
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m'

log() { echo -e "${GREEN}[✓]${NC} $1"; }

# Template de README baseado na categoria
get_readme_template() {
    local category=$1
    local project=$2
    
    case $category in
        ai)
            cat <<EOF
# $project

**Categoria:** AI & Machine Learning  
**Status:** 🚧 Em desenvolvimento

## Objetivo

Implementação de $project como parte das especializações em IA da 42.

## Features Planejadas

- [ ] Implementação core
- [ ] Testes unitários
- [ ] Benchmarks de performance
- [ ] Documentação completa

## Stack Técnica

- Linguagem: C/C++
- Build: Makefile
- Testes: Criterion / Custom

## Como Usar

\`\`\`bash
make        # Compila
make test   # Executa testes
make bench  # Benchmarks
\`\`\`

## Referências

- [Papers e artigos relevantes]
- [Documentação oficial]

## Autor

[@$GITHUB_USER](https://github.com/$GITHUB_USER)
EOF
            ;;
        cybersecurity)
            cat <<EOF
# $project

**Categoria:** Cybersecurity  
**Status:** 🔐 Em desenvolvimento

## Objetivo

Implementação de $project focado em segurança e análise.

## Escopo

- [ ] Análise de vulnerabilidades
- [ ] Implementação de proteções
- [ ] Testes de penetração
- [ ] Documentação de exploits/mitigations

## Stack

- C/C++ para performance
- Python para automação
- Assembly quando necessário

## Setup

\`\`\`bash
make
make test
\`\`\`

⚠️ **Aviso:** Para fins educacionais apenas. Use em ambiente controlado.

## Autor

[@$GITHUB_USER](https://github.com/$GITHUB_USER)
EOF
            ;;
        devops)
            cat <<EOF
# $project

**Categoria:** DevOps & Infrastructure  
**Status:** ⚙️ Em desenvolvimento

## Objetivo

Implementação de $project para automação e infraestrutura.

## Features

- [ ] Configuração de pipeline
- [ ] Automação de deploys
- [ ] Monitoring e observability
- [ ] IaC (Infrastructure as Code)

## Stack

- Docker / Kubernetes
- Terraform / Ansible
- CI/CD tools
- Monitoring stack

## Uso

\`\`\`bash
make setup
make deploy
make monitor
\`\`\`

## Autor

[@$GITHUB_USER](https://github.com/$GITHUB_USER)
EOF
            ;;
        graphics)
            cat <<EOF
# $project

**Categoria:** Graphics & Rendering  
**Status:** 🎨 Em desenvolvimento

## Objetivo

Implementação de $project com foco em renderização e gráficos.

## Features Planejadas

- [ ] Engine core
- [ ] Pipeline de renderização
- [ ] Shaders
- [ ] Otimizações

## Stack

- C/C++
- OpenGL / Vulkan / Metal
- GLSL
- Linear algebra libs

## Build

\`\`\`bash
make
./program
\`\`\`

## Autor

[@$GITHUB_USER](https://github.com/$GITHUB_USER)
EOF
            ;;
        networking)
            cat <<EOF
# $project

**Categoria:** Networking & Distributed Systems  
**Status:** 🌐 Em desenvolvimento

## Objetivo

Implementação de $project para sistemas distribuídos e rede.

## Arquitetura

- [ ] Protocolo de comunicação
- [ ] Concorrência e paralelismo
- [ ] Tolerância a falhas
- [ ] Performance e latência

## Stack

- C/C++ para core
- Sockets / epoll / kqueue
- Protocol buffers
- Docker para testes

## Como Rodar

\`\`\`bash
make
./server &
./client
\`\`\`

## Autor

[@$GITHUB_USER](https://github.com/$GITHUB_USER)
EOF
            ;;
        systems)
            cat <<EOF
# $project

**Categoria:** Systems Programming  
**Status:** 🔧 Em desenvolvimento

## Objetivo

Implementação de $project no nível de sistema.

## Componentes

- [ ] Core implementation
- [ ] Memory management
- [ ] System calls / interfaces
- [ ] Performance tuning

## Stack

- C/Assembly
- Low-level system APIs
- GDB/LLDB para debug
- Valgrind/sanitizers

## Build

\`\`\`bash
make
make test
make debug
\`\`\`

## Autor

[@$GITHUB_USER](https://github.com/$GITHUB_USER)
EOF
            ;;
    esac
}

# Cria estrutura de projeto
create_project_structure() {
    local base_path=$1
    local category=$2
    local project_name=$3
    local full_path="$base_path/$category/$project_name"
    
    log "Criando estrutura: $category/$project_name"
    
    mkdir -p "$full_path"/{src,include,tests,docs,.github/workflows}
    
    # README customizado
    get_readme_template "$category" "$project_name" > "$full_path/README.md"
    
    # Makefile genérico
    cat > "$full_path/Makefile" <<'EOF'
NAME = program
CC = gcc
CFLAGS = -Wall -Wextra -Werror -std=c11
INCLUDES = -I./include

SRC_DIR = src
OBJ_DIR = build
INC_DIR = include

SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
	@echo "✓ Build complete: $(NAME)"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	@rm -rf $(OBJ_DIR)
	@echo "✓ Objects cleaned"

fclean: clean
	@rm -f $(NAME)
	@echo "✓ Binary removed"

re: fclean all

test: all
	@echo "Running tests..."
	@./tests/run_tests.sh

.PHONY: all clean fclean re test
EOF

    # .gitignore
    cat > "$full_path/.gitignore" <<'EOF'
*.o
*.a
*.so
*.out
*.exe
program
build/
.vscode/
.idea/
*.swp
.DS_Store
EOF

    # main.c starter
    cat > "$full_path/src/main.c" <<'EOF'
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    (void)argc;
    (void)argv;
    
    printf("42 Project Starter\n");
    printf("TODO: Implement core functionality\n");
    
    return (EXIT_SUCCESS);
}
EOF

    # GitHub Actions CI
    cat > "$full_path/.github/workflows/ci.yml" <<'EOF'
name: CI

on: [push, pull_request]

jobs:
  build:
    runs-on: ubuntu-latest
    steps:
      - uses: actions/checkout@v3
      - name: Build
        run: make
      - name: Test
        run: make test
EOF

    # Inicializa git
    cd "$full_path"
    git init
    git add .
    git commit -m "feat: initial project structure

- Added Makefile
- Added basic source structure
- Added CI/CD workflow
- Added documentation" >/dev/null 2>&1
    
    cd - >/dev/null
    
    log "✓ $category/$project_name estruturado"
}

# Arrays de projetos por categoria
declare -A PROJECTS=(
    ["ai"]="distributed_training inference_engine llm_runtime neural_network vector_database"
    ["cybersecurity"]="exploit_lab malware_analysis packet_sniffer reverse_engineering secure_server"
    ["devops"]="ci_cd kubernetes monitoring observability terraform"
    ["graphics"]="doom_engine game_engine renderer vulkan_renderer"
    ["networking"]="api_gateway distributed_cache grpc_gateway http_server message_broker reverse_proxy service_mesh websocket_server"
    ["systems"]="bootloader compiler container_runtime distributed_runtime filesystem interpreter mini_kernel vm"
)

main() {
    local base="42_specializations"
    
    echo "========================================"
    echo "  Inicialização de Specializations"
    echo "========================================"
    
    total=0
    for category in "${!PROJECTS[@]}"; do
        count=$(echo ${PROJECTS[$category]} | wc -w)
        total=$((total + count))
        echo "$category: $count projetos"
    done
    
    echo "Total: $total projetos"
    echo ""
    echo "Criar estruturas? (y/n)"
    read -r response
    [[ "$response" =~ ^[Yy]$ ]] || exit 0
    
    for category in "${!PROJECTS[@]}"; do
        echo ""
        log "Processando categoria: $category"
        for project in ${PROJECTS[$category]}; do
            create_project_structure "$base" "$category" "$project"
        done
    done
    
    echo ""
    log "✅ Todas estruturas criadas!"
    echo ""
    echo "Próximos passos:"
    echo "1. Revisar estruturas em $base/"
    echo "2. Criar repos no GitHub para cada projeto"
    echo "3. Adicionar como submódulos"
    echo ""
    echo "Script de automação disponível em: auto_push_specializations.sh"
}

main

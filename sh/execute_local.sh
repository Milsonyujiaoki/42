#!/bin/bash
# Organização sem GitHub CLI - preparação local completa

set -e

GREEN='\033[0;32m'
BLUE='\033[0;34m'
YELLOW='\033[1;33m'
NC='\033[0m'

log() { echo -e "${GREEN}[✓]${NC} $1"; }
info() { echo -e "${BLUE}[→]${NC} $1"; }
warn() { echo -e "${YELLOW}[!]${NC} $1"; }

GITHUB_USER="Milsonyujiaoki"
BASE_DIR="/home/dev-yuji/projetos/42"

# Template README por categoria
get_readme() {
    local category=$1
    local project=$2
    
    cat <<EOF
# $project

**Categoria:** $(echo $category | tr '[:lower:]' '[:upper:]')  
**Status:** 🚧 Em desenvolvimento

## Descrição

Implementação de $project como parte das especializações da 42 School.

## Estrutura

\`\`\`
.
├── src/          # Código fonte
├── include/      # Headers
├── tests/        # Testes
├── docs/         # Documentação
└── Makefile      # Build system
\`\`\`

## Build

\`\`\`bash
make        # Compila
make test   # Testes
make clean  # Limpa
\`\`\`

## Autor

[@$GITHUB_USER](https://github.com/$GITHUB_USER)
EOF
}

# Cria estrutura completa de projeto
create_project() {
    local path=$1
    local category=$2
    local name=$3
    
    info "Criando $category/$name"
    
    mkdir -p "$path"/{src,include,tests,docs}
    
    # README
    get_readme "$category" "$name" > "$path/README.md"
    
    # Makefile
    cat > "$path/Makefile" <<'EOF'
NAME = program
CC = gcc
CFLAGS = -Wall -Wextra -Werror
INCLUDES = -I./include

SRC_DIR = src
OBJ_DIR = build

SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
	@echo "✓ Compilado: $(NAME)"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	@rm -rf $(OBJ_DIR)

fclean: clean
	@rm -f $(NAME)

re: fclean all

test: all
	@echo "Running tests..."

.PHONY: all clean fclean re test
EOF

    # .gitignore
    cat > "$path/.gitignore" <<'EOF'
*.o
*.a
*.so
*.out
program
build/
.vscode/
.DS_Store
EOF

    # main.c
    cat > "$path/src/main.c" <<'EOF'
#include <stdio.h>

int main(void)
{
    printf("42 Project\n");
    return (0);
}
EOF

    # Git init
    cd "$path"
    git init -q
    git add .
    git commit -q -m "feat: initial project structure"
    cd - > /dev/null
    
    log "✓ $name estruturado"
}

# Prepara projeto existente
prepare_existing() {
    local path=$1
    local name=$(basename "$path")
    
    info "Preparando $name"
    
    cd "$path"
    
    # Commit mudanças pendentes
    git add -A 2>/dev/null || true
    if ! git diff --quiet 2>/dev/null || ! git diff --staged --quiet 2>/dev/null; then
        git commit -q -m "chore: organize structure" 2>/dev/null || true
    fi
    
    cd - > /dev/null
    
    log "✓ $name pronto"
}

echo "================================"
echo "  Preparação Local Completa"
echo "================================"
echo ""

# Criar specializations
info "FASE 1: Criando specializations..."

declare -A SPECS=(
    ["ai"]="distributed_training inference_engine llm_runtime neural_network vector_database"
    ["cybersecurity"]="exploit_lab malware_analysis packet_sniffer reverse_engineering secure_server"
    ["devops"]="ci_cd kubernetes monitoring observability terraform"
    ["graphics"]="doom_engine game_engine renderer vulkan_renderer"
    ["networking"]="api_gateway distributed_cache grpc_gateway http_server message_broker reverse_proxy service_mesh websocket_server"
    ["systems"]="bootloader compiler container_runtime distributed_runtime filesystem interpreter mini_kernel vm"
)

for category in "${!SPECS[@]}"; do
    for project in ${SPECS[$category]}; do
        path="$BASE_DIR/42_specializations/$category/$project"
        if [ ! -d "$path/.git" ]; then
            create_project "$path" "$category" "$project"
        else
            warn "Pulando $project (já existe)"
        fi
    done
done

log "FASE 1 completa: $(find 42_specializations -name .git -type d | wc -l) projetos criados"

# Preparar projetos existentes
info ""
info "FASE 2: Preparando projetos existentes..."

EXISTING=(
    "42_common_core/rank02/pipex"
    "42_common_core/rank02/push_swap"
    "42_common_core/rank02/so_long"
    "42_common_core/rank03/minishell"
    "42_common_core/rank03/philosophers"
    "42_common_core/rank04/cub3d"
    "42_common_core/rank04/miniRT"
    "42_common_core/rank04/netpractice"
    "42_common_core/rank05/cpp_modules"
    "42_common_core/rank05/inception"
    "42_common_core/rank05/webserv"
    "42_common_core/rank06/ft_transcendence"
    "extras/ft_irc"
    "extras/libasm"
    "extras/malloc"
)

for project in "${EXISTING[@]}"; do
    if [ -d "$BASE_DIR/$project/.git" ]; then
        prepare_existing "$BASE_DIR/$project"
    else
        warn "Pulando $project (sem .git)"
    fi
done

log "FASE 2 completa"

# Gerar script de criação de repos
info ""
info "FASE 3: Gerando instruções..."

cat > "$BASE_DIR/CREATE_REPOS.sh" <<'REPOS_EOF'
#!/bin/bash
# Criar repositórios no GitHub manualmente

GITHUB_USER="Milsonyujiaoki"

echo "Criar repositórios no GitHub para cada projeto"
echo ""
echo "Opções:"
echo "1. Manual via interface web: https://github.com/new"
echo "2. Instalar GitHub CLI: sudo apt install gh"
echo ""
echo "Lista de repositórios necessários:"
echo ""

# Projetos existentes
echo "=== Projetos Existentes (15) ==="
declare -a repos=(
    "pipex"
    "push_swap"
    "so_long"
    "minishell"
    "philosophers"
    "cub3d"
    "miniRT"
    "netpractice"
    "cpp_modules"
    "inception"
    "webserv"
    "ft_transcendence"
    "ft_irc"
    "libasm"
    "malloc"
)

for repo in "${repos[@]}"; do
    echo "  - $repo"
    echo "    https://github.com/new → Nome: $repo"
done

echo ""
echo "=== Specializations (32) ==="

declare -A specs=(
    ["ai"]="distributed_training inference_engine llm_runtime neural_network vector_database"
    ["cybersecurity"]="exploit_lab malware_analysis packet_sniffer reverse_engineering secure_server"
    ["devops"]="ci_cd kubernetes monitoring observability terraform"
    ["graphics"]="doom_engine game_engine renderer vulkan_renderer"
    ["networking"]="api_gateway distributed_cache grpc_gateway http_server message_broker reverse_proxy service_mesh websocket_server"
    ["systems"]="bootloader compiler container_runtime distributed_runtime filesystem interpreter mini_kernel vm"
)

for category in "${!specs[@]}"; do
    echo ""
    echo "[$category]"
    for proj in ${specs[$category]}; do
        repo_name="42-${category}-${proj}"
        echo "  - $repo_name"
    done
done

echo ""
echo "Total: 47 repositórios"
REPOS_EOF

chmod +x "$BASE_DIR/CREATE_REPOS.sh"

# Gerar script de push
cat > "$BASE_DIR/PUSH_ALL.sh" <<'PUSH_EOF'
#!/bin/bash
# Push de todos projetos para GitHub

GITHUB_USER="Milsonyujiaoki"
GREEN='\033[0;32m'
NC='\033[0m'

log() { echo -e "${GREEN}[✓]${NC} $1"; }

push_project() {
    local path=$1
    local repo_name=$2
    
    echo "Pushing $repo_name..."
    cd "$path"
    
    git remote remove origin 2>/dev/null || true
    git remote add origin "git@github.com:$GITHUB_USER/${repo_name}.git"
    git branch -M main
    git push -u origin main --force 2>/dev/null && log "$repo_name pushed" || echo "✗ Falha: $repo_name"
    
    cd - > /dev/null
}

# Projetos existentes
push_project "42_common_core/rank02/pipex" "pipex"
push_project "42_common_core/rank02/push_swap" "push_swap"
push_project "42_common_core/rank02/so_long" "so_long"
push_project "42_common_core/rank03/minishell" "minishell"
push_project "42_common_core/rank03/philosophers" "philosophers"
push_project "42_common_core/rank04/cub3d" "cub3d"
push_project "42_common_core/rank04/miniRT" "miniRT"
push_project "42_common_core/rank04/netpractice" "netpractice"
push_project "42_common_core/rank05/cpp_modules" "cpp_modules"
push_project "42_common_core/rank05/inception" "inception"
push_project "42_common_core/rank05/webserv" "webserv"
push_project "42_common_core/rank06/ft_transcendence" "ft_transcendence"
push_project "extras/ft_irc" "ft_irc"
push_project "extras/libasm" "libasm"
push_project "extras/malloc" "malloc"

# Specializations
declare -A specs=(
    ["ai"]="distributed_training inference_engine llm_runtime neural_network vector_database"
    ["cybersecurity"]="exploit_lab malware_analysis packet_sniffer reverse_engineering secure_server"
    ["devops"]="ci_cd kubernetes monitoring observability terraform"
    ["graphics"]="doom_engine game_engine renderer vulkan_renderer"
    ["networking"]="api_gateway distributed_cache grpc_gateway http_server message_broker reverse_proxy service_mesh websocket_server"
    ["systems"]="bootloader compiler container_runtime distributed_runtime filesystem interpreter mini_kernel vm"
)

for category in "${!specs[@]}"; do
    for proj in ${specs[$category]}; do
        repo_name="42-${category}-${proj}"
        path="42_specializations/$category/$proj"
        push_project "$path" "$repo_name"
    done
done

echo ""
log "Push completo!"
PUSH_EOF

chmod +x "$BASE_DIR/PUSH_ALL.sh"

# Gerar script de conversão para submódulos
cat > "$BASE_DIR/CONVERT_TO_SUBMODULES.sh" <<'CONVERT_EOF'
#!/bin/bash
# Converter projetos locais em submódulos

GITHUB_USER="Milsonyujiaoki"
GREEN='\033[0;32m'
NC='\033[0m'

log() { echo -e "${GREEN}[✓]${NC} $1"; }

convert() {
    local path=$1
    local repo_name=$2
    
    echo "Convertendo $path..."
    
    git rm -r --cached "$path" 2>/dev/null || true
    rm -rf "$path"
    git submodule add "git@github.com:$GITHUB_USER/${repo_name}.git" "$path"
    
    log "$path → submódulo"
}

# Existentes
convert "42_common_core/rank02/pipex" "pipex"
convert "42_common_core/rank02/push_swap" "push_swap"
convert "42_common_core/rank02/so_long" "so_long"
convert "42_common_core/rank03/minishell" "minishell"
convert "42_common_core/rank03/philosophers" "philosophers"
convert "42_common_core/rank04/cub3d" "cub3d"
convert "42_common_core/rank04/miniRT" "miniRT"
convert "42_common_core/rank04/netpractice" "netpractice"
convert "42_common_core/rank05/cpp_modules" "cpp_modules"
convert "42_common_core/rank05/inception" "inception"
convert "42_common_core/rank05/webserv" "webserv"
convert "42_common_core/rank06/ft_transcendence" "ft_transcendence"
convert "extras/ft_irc" "ft_irc"
convert "extras/libasm" "libasm"
convert "extras/malloc" "malloc"

# Specializations
declare -A specs=(
    ["ai"]="distributed_training inference_engine llm_runtime neural_network vector_database"
    ["cybersecurity"]="exploit_lab malware_analysis packet_sniffer reverse_engineering secure_server"
    ["devops"]="ci_cd kubernetes monitoring observability terraform"
    ["graphics"]="doom_engine game_engine renderer vulkan_renderer"
    ["networking"]="api_gateway distributed_cache grpc_gateway http_server message_broker reverse_proxy service_mesh websocket_server"
    ["systems"]="bootloader compiler container_runtime distributed_runtime filesystem interpreter mini_kernel vm"
)

for category in "${!specs[@]}"; do
    for proj in ${specs[$category]}; do
        repo_name="42-${category}-${proj}"
        path="42_specializations/$category/$proj"
        convert "$path" "$repo_name"
    done
done

git add .gitmodules
git commit -m "feat: convert all projects to submodules"

log "Conversão completa!"
CONVERT_EOF

chmod +x "$BASE_DIR/CONVERT_TO_SUBMODULES.sh"

log "FASE 3 completa"

echo ""
echo "================================"
echo "  ✅ PREPARAÇÃO COMPLETA"
echo "================================"
echo ""
./status.sh
echo ""
echo "Próximos passos (em sh/):"
echo ""
echo "1. Ver comandos criar repos: sh/QUICK_REPO_CREATE.sh"
echo "2. Push projetos:           sh/PUSH_ALL.sh"
echo "3. Converter submódulos:    sh/CONVERT_TO_SUBMODULES.sh"
echo "4. Push final:              git push origin main"
echo ""

#!/bin/bash
# Script para organizar submódulos do repositório 42

set -e

GITHUB_USER="Milsonyujiaoki"
MAIN_REPO="42"

# Cores para output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m' # No Color

log_info() { echo -e "${GREEN}[INFO]${NC} $1"; }
log_warn() { echo -e "${YELLOW}[WARN]${NC} $1"; }
log_error() { echo -e "${RED}[ERROR]${NC} $1"; }

# Projetos que já têm .git e precisam virar submódulos
PROJECTS_TO_CONVERT=(
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

# Projetos vazios que precisam de estrutura inicial
SPECIALIZATION_PROJECTS=(
    "42_specializations/ai/distributed_training"
    "42_specializations/ai/inference_engine"
    "42_specializations/ai/llm_runtime"
    "42_specializations/ai/neural_network"
    "42_specializations/ai/vector_database"
    "42_specializations/cybersecurity/exploit_lab"
    "42_specializations/cybersecurity/malware_analysis"
    "42_specializations/cybersecurity/packet_sniffer"
    "42_specializations/cybersecurity/reverse_engineering"
    "42_specializations/cybersecurity/secure_server"
    "42_specializations/devops/ci_cd"
    "42_specializations/devops/kubernetes"
    "42_specializations/devops/monitoring"
    "42_specializations/devops/observability"
    "42_specializations/devops/terraform"
    "42_specializations/graphics/doom_engine"
    "42_specializations/graphics/game_engine"
    "42_specializations/graphics/renderer"
    "42_specializations/graphics/vulkan_renderer"
    "42_specializations/networking/api_gateway"
    "42_specializations/networking/distributed_cache"
    "42_specializations/networking/grpc_gateway"
    "42_specializations/networking/http_server"
    "42_specializations/networking/message_broker"
    "42_specializations/networking/reverse_proxy"
    "42_specializations/networking/service_mesh"
    "42_specializations/networking/websocket_server"
    "42_specializations/systems/bootloader"
    "42_specializations/systems/compiler"
    "42_specializations/systems/container_runtime"
    "42_specializations/systems/distributed_runtime"
    "42_specializations/systems/filesystem"
    "42_specializations/systems/interpreter"
    "42_specializations/systems/mini_kernel"
    "42_specializations/systems/vm"
)

# Função para criar estrutura de projeto padrão
create_project_structure() {
    local project_path=$1
    local project_name=$(basename "$project_path")
    
    log_info "Criando estrutura para $project_name..."
    
    mkdir -p "$project_path"/{src,include,tests,docs}
    
    # README.md
    cat > "$project_path/README.md" <<EOF
# $project_name

**Status:** 🚧 Em desenvolvimento

## Descrição

Projeto $project_name da 42 School.

## Estrutura

\`\`\`
.
├── src/          # Código fonte
├── include/      # Headers
├── tests/        # Testes
├── docs/         # Documentação
└── Makefile      # Build system
\`\`\`

## Como compilar

\`\`\`bash
make
\`\`\`

## Como testar

\`\`\`bash
make test
\`\`\`

## Autor

[@$GITHUB_USER](https://github.com/$GITHUB_USER)

## Licença

Este projeto faz parte do currículo da 42 School.
EOF

    # Makefile básico
    cat > "$project_path/Makefile" <<'EOF'
# Nome do executável
NAME = program

# Compilador e flags
CC = gcc
CFLAGS = -Wall -Wextra -Werror
INCLUDES = -I./include

# Diretórios
SRC_DIR = src
OBJ_DIR = build
INC_DIR = include

# Arquivos
SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# Cores para output
GREEN = \033[0;32m
RED = \033[0;31m
NC = \033[0m

# Regras
all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
	@echo "$(GREEN)✓ $(NAME) compilado com sucesso!$(NC)"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	@rm -rf $(OBJ_DIR)
	@echo "$(RED)✗ Arquivos objeto removidos$(NC)"

fclean: clean
	@rm -f $(NAME)
	@echo "$(RED)✗ $(NAME) removido$(NC)"

re: fclean all

test: all
	@echo "$(GREEN)Executando testes...$(NC)"
	@# Adicione seus comandos de teste aqui

.PHONY: all clean fclean re test
EOF

    # .gitignore
    cat > "$project_path/.gitignore" <<'EOF'
# Executáveis
*.out
*.exe
program

# Arquivos objeto
*.o
*.a
*.so
build/
obj/

# Debug
*.dSYM/
*.gch
*.pch

# Editores
.vscode/
.idea/
*.swp
*.swo
*~

# Sistema
.DS_Store
Thumbs.db

# Testes
test_output/
*.log
EOF

    # main.c exemplo
    cat > "$project_path/src/main.c" <<'EOF'
#include <stdio.h>

int main(int argc, char **argv)
{
    (void)argc;
    (void)argv;
    
    printf("Hello from 42!\n");
    return (0);
}
EOF

    log_info "Estrutura criada para $project_name"
}

# Função para converter projeto existente em submódulo
convert_to_submodule() {
    local project_path=$1
    local project_name=$(basename "$project_path")
    local repo_name=$(echo "$project_name" | tr '[:upper:]' '[:lower:]' | tr '_' '-')
    
    log_info "Convertendo $project_name para submódulo..."
    
    # Verifica se o diretório existe
    if [ ! -d "$project_path" ]; then
        log_error "Diretório $project_path não existe"
        return 1
    fi
    
    # Salva o conteúdo atual
    local temp_dir="/tmp/${repo_name}_backup"
    rm -rf "$temp_dir"
    cp -r "$project_path" "$temp_dir"
    
    log_info "Backup criado em $temp_dir"
    
    echo ""
    echo "========================================="
    echo "PRÓXIMOS PASSOS MANUAIS para $project_name:"
    echo "========================================="
    echo "1. Criar repositório GitHub: https://github.com/new"
    echo "   Nome: $repo_name"
    echo "   Público/Privado: sua escolha"
    echo ""
    echo "2. No diretório do backup ($temp_dir):"
    echo "   cd $temp_dir"
    echo "   git remote remove origin 2>/dev/null || true"
    echo "   git remote add origin git@github.com:$GITHUB_USER/${repo_name}.git"
    echo "   git push -u origin main"
    echo ""
    echo "3. Remover pasta atual e adicionar submódulo:"
    echo "   cd $(pwd)"
    echo "   git rm -rf $project_path"
    echo "   git commit -m \"Remove $project_name before submodule\""
    echo "   git submodule add git@github.com:$GITHUB_USER/${repo_name}.git $project_path"
    echo "   git commit -m \"Add $project_name as submodule\""
    echo ""
    echo "========================================="
    echo ""
}

# Função para criar e inicializar novo projeto como submódulo
create_new_submodule() {
    local project_path=$1
    local project_name=$(basename "$project_path")
    local repo_name=$(echo "$project_name" | tr '[:upper:]' '[:lower:]' | tr '_' '-')
    
    log_info "Preparando $project_name como novo submódulo..."
    
    # Cria estrutura temporária
    local temp_dir="/tmp/${repo_name}_new"
    rm -rf "$temp_dir"
    mkdir -p "$temp_dir"
    
    # Cria estrutura dentro do temp
    cd "$temp_dir"
    create_project_structure "."
    
    # Inicializa git
    git init
    git add .
    git commit -m "Initial commit: project structure"
    
    log_info "Repositório local criado em $temp_dir"
    
    echo ""
    echo "========================================="
    echo "PRÓXIMOS PASSOS MANUAIS para $project_name:"
    echo "========================================="
    echo "1. Criar repositório GitHub: https://github.com/new"
    echo "   Nome: $repo_name"
    echo "   Público/Privado: sua escolha"
    echo ""
    echo "2. No diretório temporário ($temp_dir):"
    echo "   cd $temp_dir"
    echo "   git remote add origin git@github.com:$GITHUB_USER/${repo_name}.git"
    echo "   git push -u origin main"
    echo ""
    echo "3. Adicionar como submódulo:"
    echo "   cd $(pwd)"
    echo "   rm -rf $project_path"  # Remove pasta vazia
    echo "   git submodule add git@github.com:$GITHUB_USER/${repo_name}.git $project_path"
    echo "   git commit -m \"Add $project_name as submodule\""
    echo ""
    echo "========================================="
    echo ""
    
    cd - > /dev/null
}

# Menu principal
show_menu() {
    echo ""
    echo "========================================="
    echo "  Configuração de Submódulos - 42"
    echo "========================================="
    echo "1. Converter projetos existentes (rank02-06 + extras)"
    echo "2. Criar estrutura para specializations"
    echo "3. Fazer ambos"
    echo "4. Gerar script de automação completa"
    echo "5. Sair"
    echo "========================================="
    echo -n "Escolha uma opção: "
}

# Função para gerar script de automação GitHub CLI
generate_automation_script() {
    cat > "automate_github_submodules.sh" <<'SCRIPT_EOF'
#!/bin/bash
# Script de automação completa usando GitHub CLI
# Requer: gh (GitHub CLI) instalado e autenticado

set -e

GITHUB_USER="Milsonyujiaoki"

# Verifica se gh está instalado
if ! command -v gh &> /dev/null; then
    echo "GitHub CLI (gh) não encontrado. Instale: https://cli.github.com/"
    exit 1
fi

# Verifica autenticação
if ! gh auth status &> /dev/null; then
    echo "GitHub CLI não autenticado. Execute: gh auth login"
    exit 1
fi

convert_and_push() {
    local project_path=$1
    local project_name=$(basename "$project_path")
    local repo_name=$(echo "$project_name" | tr '[:upper:]' '[:lower:]' | tr '_' '-')
    
    echo "🔄 Processando $project_name..."
    
    # Cria repositório no GitHub
    gh repo create "$GITHUB_USER/$repo_name" --public --description "42 Project: $project_name" || echo "Repo já existe"
    
    # Backup do projeto
    temp_dir="/tmp/${repo_name}_backup"
    rm -rf "$temp_dir"
    cp -r "$project_path" "$temp_dir"
    
    cd "$temp_dir"
    
    # Remove remote antigo e adiciona novo
    git remote remove origin 2>/dev/null || true
    git remote add origin "git@github.com:$GITHUB_USER/${repo_name}.git"
    
    # Push
    git push -u origin main --force
    
    echo "✅ $project_name pushed para GitHub"
    cd - > /dev/null
}

create_and_push_new() {
    local project_path=$1
    local project_name=$(basename "$project_path")
    local repo_name=$(echo "$project_name" | tr '[:upper:]' '[:lower:]' | tr '_' '-')
    
    echo "🆕 Criando $project_name..."
    
    # Cria repositório no GitHub
    gh repo create "$GITHUB_USER/$repo_name" --public --description "42 Specialization: $project_name" || echo "Repo já existe"
    
    # ... resto do código de criação
    
    echo "✅ $project_name criado e pushed"
}

echo "🚀 Iniciando automação completa..."
echo "Deseja continuar? (y/n)"
read -r response
if [[ ! "$response" =~ ^[Yy]$ ]]; then
    exit 0
fi

# Array de projetos para converter
projects_to_convert=(
    "42_common_core/rank02/pipex"
    "42_common_core/rank02/push_swap"
    # ... adicione todos os projetos
)

for project in "${projects_to_convert[@]}"; do
    convert_and_push "$project"
done

echo "✅ Automação completa!"
SCRIPT_EOF

    chmod +x automate_github_submodules.sh
    log_info "Script de automação criado: automate_github_submodules.sh"
}

# Main
main() {
    while true; do
        show_menu
        read -r choice
        
        case $choice in
            1)
                log_info "Convertendo projetos existentes..."
                for project in "${PROJECTS_TO_CONVERT[@]}"; do
                    convert_to_submodule "$project"
                done
                ;;
            2)
                log_info "Criando estrutura para specializations..."
                for project in "${SPECIALIZATION_PROJECTS[@]}"; do
                    create_new_submodule "$project"
                done
                ;;
            3)
                log_info "Executando processo completo..."
                for project in "${PROJECTS_TO_CONVERT[@]}"; do
                    convert_to_submodule "$project"
                done
                for project in "${SPECIALIZATION_PROJECTS[@]}"; do
                    create_new_submodule "$project"
                done
                ;;
            4)
                generate_automation_script
                ;;
            5)
                log_info "Saindo..."
                exit 0
                ;;
            *)
                log_error "Opção inválida"
                ;;
        esac
    done
}

main

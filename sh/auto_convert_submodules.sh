#!/bin/bash
# Auto-conversão completa usando GitHub CLI
# Requer: gh CLI instalado e autenticado

set -e

GITHUB_USER="Milsonyujiaoki"
GREEN='\033[0;32m'
RED='\033[0;31m'
YELLOW='\033[1;33m'
NC='\033[0m'

log() { echo -e "${GREEN}[$(date +'%H:%M:%S')]${NC} $1"; }
err() { echo -e "${RED}[ERROR]${NC} $1"; exit 1; }
warn() { echo -e "${YELLOW}[WARN]${NC} $1"; }

# Verifica dependências
command -v gh >/dev/null 2>&1 || err "GitHub CLI (gh) não instalado. Instale: https://cli.github.com/"
gh auth status >/dev/null 2>&1 || err "GitHub CLI não autenticado. Execute: gh auth login"

# Projetos com .git para converter
CONVERT_PROJECTS=(
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

convert_existing_project() {
    local path=$1
    local name=$(basename "$path")
    local repo_name=$(echo "$name" | tr '[:upper:]' '[:lower:]')
    
    log "Processando $name → $repo_name"
    
    # Cria repo no GitHub se não existir
    if ! gh repo view "$GITHUB_USER/$repo_name" >/dev/null 2>&1; then
        log "Criando repositório $repo_name no GitHub..."
        gh repo create "$GITHUB_USER/$repo_name" --public --description "42 School: $name"
    else
        warn "Repo $repo_name já existe no GitHub"
    fi
    
    # Salva estado atual
    cd "$path"
    
    # Atualiza remote
    if git remote get-url origin >/dev/null 2>&1; then
        git remote set-url origin "git@github.com:$GITHUB_USER/${repo_name}.git"
    else
        git remote add origin "git@github.com:$GITHUB_USER/${repo_name}.git"
    fi
    
    # Commit e push
    git add -A 2>/dev/null || true
    git diff --quiet && git diff --staged --quiet || git commit -m "chore: organize project structure" || true
    
    log "Pushing $name para GitHub..."
    git push -u origin main --force 2>/dev/null || git push -u origin master --force || warn "Push falhou para $name"
    
    cd - >/dev/null
    
    log "✓ $name → https://github.com/$GITHUB_USER/$repo_name"
    
    # Adiciona info para conversão em submódulo
    echo "$path|$repo_name" >> /tmp/submodules_to_add.txt
}

add_as_submodule() {
    local path=$1
    local repo_name=$2
    
    log "Convertendo $path em submódulo..."
    
    # Remove do git principal (mas mantém arquivos)
    git rm -r --cached "$path" 2>/dev/null || true
    rm -rf "$path"
    
    # Adiciona como submódulo
    git submodule add "git@github.com:$GITHUB_USER/${repo_name}.git" "$path" || warn "Submódulo já existe: $path"
    
    log "✓ Submódulo adicionado: $path"
}

# Main
main() {
    cd /home/dev-yuji/projetos/42
    
    echo "========================================"
    echo "  Auto-conversão para Submódulos"
    echo "========================================"
    echo "Vai processar ${#CONVERT_PROJECTS[@]} projetos"
    echo ""
    echo "Continuar? (y/n)"
    read -r response
    [[ "$response" =~ ^[Yy]$ ]] || exit 0
    
    rm -f /tmp/submodules_to_add.txt
    
    # Fase 1: Push projetos para GitHub
    log "FASE 1: Enviando projetos para GitHub..."
    for project in "${CONVERT_PROJECTS[@]}"; do
        if [ -d "$project/.git" ]; then
            convert_existing_project "$project"
        else
            warn "Pulando $project (sem .git)"
        fi
    done
    
    log ""
    log "FASE 1 completa. Projetos no GitHub."
    log ""
    log "FASE 2: Converter para submódulos?"
    echo "Isso vai remover as pastas atuais e recriar como submódulos."
    echo "Continuar? (y/n)"
    read -r response
    [[ "$response" =~ ^[Yy]$ ]] || exit 0
    
    # Fase 2: Converter para submódulos
    log "FASE 2: Convertendo para submódulos..."
    
    if [ -f /tmp/submodules_to_add.txt ]; then
        while IFS='|' read -r path repo_name; do
            add_as_submodule "$path" "$repo_name"
        done < /tmp/submodules_to_add.txt
        
        # Commit final
        git add .gitmodules
        git commit -m "feat: convert projects to submodules

- Converted rank02-06 projects
- Converted extras projects
- Total: ${#CONVERT_PROJECTS[@]} submodules" || true
        
        log ""
        log "✅ CONVERSÃO COMPLETA!"
        log ""
        log "Próximos passos:"
        log "1. git push origin main"
        log "2. git submodule update --init --recursive"
    fi
}

main

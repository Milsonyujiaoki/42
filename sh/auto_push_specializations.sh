#!/bin/bash
# Automação completa: cria, push e adiciona specializations como submódulos

set -e

GITHUB_USER="Milsonyujiaoki"
GREEN='\033[0;32m'
BLUE='\033[0;34m'
NC='\033[0m'

log() { echo -e "${GREEN}[$(date +'%H:%M:%S')]${NC} $1"; }
info() { echo -e "${BLUE}[INFO]${NC} $1"; }

command -v gh >/dev/null 2>&1 || { echo "Instale GitHub CLI: https://cli.github.com/"; exit 1; }
gh auth status >/dev/null 2>&1 || { echo "Execute: gh auth login"; exit 1; }

process_specialization() {
    local category=$1
    local project=$2
    local path="42_specializations/$category/$project"
    local repo_name="42-${category}-${project}"
    
    log "Processando $category/$project"
    
    # Verifica se já tem estrutura
    if [ ! -d "$path/src" ]; then
        info "Sem estrutura, pulando..."
        return
    fi
    
    # Cria repo no GitHub
    if ! gh repo view "$GITHUB_USER/$repo_name" >/dev/null 2>&1; then
        info "Criando repo: $repo_name"
        gh repo create "$GITHUB_USER/$repo_name" \
            --public \
            --description "42 Specialization: $category - $project" \
            --add-readme=false
    fi
    
    # Push do conteúdo
    cd "$path"
    
    if [ ! -d ".git" ]; then
        git init
        git add .
        git commit -m "feat: initial structure"
    fi
    
    git remote remove origin 2>/dev/null || true
    git remote add origin "git@github.com:$GITHUB_USER/${repo_name}.git"
    
    git branch -M main
    git push -u origin main --force
    
    cd - >/dev/null
    
    log "✓ Pushed $repo_name"
    
    # Registra para conversão em submódulo
    echo "$path|$repo_name" >> /tmp/spec_submodules.txt
}

convert_to_submodules() {
    log "Convertendo para submódulos..."
    
    [ -f /tmp/spec_submodules.txt ] || return
    
    while IFS='|' read -r path repo_name; do
        info "Submódulo: $path"
        
        # Remove do tracking (mantém arquivos localmente)
        git rm -r --cached "$path" 2>/dev/null || true
        
        # Remove pasta
        rm -rf "$path"
        
        # Adiciona submódulo
        git submodule add "git@github.com:$GITHUB_USER/${repo_name}.git" "$path"
        
        log "✓ $path → submódulo"
    done < /tmp/spec_submodules.txt
    
    # Commit
    git add .gitmodules
    git commit -m "feat: add specialization projects as submodules

Auto-converted all specialization projects to GitHub submodules."
}

main() {
    cd /home/dev-yuji/projetos/42
    
    echo "========================================"
    echo " Auto Push Specializations → GitHub"
    echo "========================================"
    echo ""
    echo "Vai processar projetos em 42_specializations/"
    echo "Criar repos + push + converter para submódulos"
    echo ""
    echo "Continuar? (y/n)"
    read -r response
    [[ "$response" =~ ^[Yy]$ ]] || exit 0
    
    rm -f /tmp/spec_submodules.txt
    
    # Categorias e projetos
    declare -A projects=(
        ["ai"]="distributed_training inference_engine llm_runtime neural_network vector_database"
        ["cybersecurity"]="exploit_lab malware_analysis packet_sniffer reverse_engineering secure_server"
        ["devops"]="ci_cd kubernetes monitoring observability terraform"
        ["graphics"]="doom_engine game_engine renderer vulkan_renderer"
        ["networking"]="api_gateway distributed_cache grpc_gateway http_server message_broker reverse_proxy service_mesh websocket_server"
        ["systems"]="bootloader compiler container_runtime distributed_runtime filesystem interpreter mini_kernel vm"
    )
    
    # Fase 1: Push para GitHub
    log "FASE 1: Enviando para GitHub..."
    for category in "${!projects[@]}"; do
        for project in ${projects[$category]}; do
            process_specialization "$category" "$project"
        done
    done
    
    log ""
    log "FASE 1 completa!"
    log ""
    
    # Fase 2: Conversão para submódulos
    echo "FASE 2: Converter para submódulos? (y/n)"
    read -r response
    [[ "$response" =~ ^[Yy]$ ]] || exit 0
    
    convert_to_submodules
    
    log ""
    log "✅ PROCESSO COMPLETO!"
    log ""
    echo "Próximos passos:"
    echo "  git push origin main"
    echo "  git submodule update --init --recursive"
}

main

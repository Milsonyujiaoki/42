#!/bin/bash
# Master script - executa pipeline completa de organização

set -e

GREEN='\033[0;32m'
BLUE='\033[0;34m'
YELLOW='\033[1;33m'
RED='\033[0;31m'
BOLD='\033[1m'
NC='\033[0m'

print_header() {
    echo -e "\n${BOLD}${BLUE}━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━${NC}"
    echo -e "${BOLD}${BLUE}  $1${NC}"
    echo -e "${BOLD}${BLUE}━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━${NC}\n"
}

log_success() { echo -e "${GREEN}✓${NC} $1"; }
log_info() { echo -e "${BLUE}ℹ${NC} $1"; }
log_warn() { echo -e "${YELLOW}⚠${NC} $1"; }
log_error() { echo -e "${RED}✗${NC} $1"; exit 1; }

check_prerequisites() {
    print_header "Verificando Pré-requisitos"
    
    # Git
    if ! command -v git &> /dev/null; then
        log_error "Git não instalado"
    fi
    log_success "Git instalado"
    
    # GitHub CLI
    if ! command -v gh &> /dev/null; then
        log_warn "GitHub CLI não instalado"
        echo ""
        echo "Instalar GitHub CLI? (y/n)"
        read -r install_gh
        if [[ "$install_gh" =~ ^[Yy]$ ]]; then
            log_info "Instalando GitHub CLI..."
            if [[ "$OSTYPE" == "linux-gnu"* ]]; then
                curl -fsSL https://cli.github.com/packages/githubcli-archive-keyring.gpg | sudo dd of=/usr/share/keyrings/githubcli-archive-keyring.gpg
                echo "deb [arch=$(dpkg --print-architecture) signed-by=/usr/share/keyrings/githubcli-archive-keyring.gpg] https://cli.github.com/packages stable main" | sudo tee /etc/apt/sources.list.d/github-cli.list > /dev/null
                sudo apt update && sudo apt install gh -y
            elif [[ "$OSTYPE" == "darwin"* ]]; then
                brew install gh
            fi
        else
            log_error "GitHub CLI necessário. Instale: https://cli.github.com/"
        fi
    fi
    log_success "GitHub CLI instalado"
    
    # Autenticação GitHub
    if ! gh auth status &> /dev/null; then
        log_warn "GitHub CLI não autenticado"
        log_info "Iniciando autenticação..."
        gh auth login
    fi
    log_success "GitHub CLI autenticado"
    
    # Scripts executáveis
    for script in auto_convert_submodules.sh init_specializations.sh auto_push_specializations.sh; do
        if [ ! -x "$script" ]; then
            chmod +x "$script"
            log_info "Permissão adicionada: $script"
        fi
    done
    log_success "Scripts configurados"
}

show_summary() {
    print_header "Resumo da Organização"
    
    echo "📊 Status Atual:"
    echo ""
    
    # Submódulos existentes
    existing=$(git submodule status 2>/dev/null | wc -l)
    echo -e "  ${GREEN}✓${NC} Submódulos existentes: $existing"
    
    # Projetos a converter
    convert_count=0
    for dir in 42_common_core/rank0{2..6}/*/ extras/*/; do
        [ -d "$dir/.git" ] && ((convert_count++)) || true
    done
    echo -e "  ${YELLOW}→${NC} Projetos para converter: $convert_count"
    
    # Projetos vazios
    empty_count=$(find 42_specializations -maxdepth 2 -mindepth 2 -type d | wc -l)
    echo -e "  ${BLUE}+${NC} Projetos para criar: $empty_count"
    
    echo ""
    echo "🎯 Total esperado final: $((existing + convert_count + empty_count)) submódulos"
    echo ""
}

create_backup() {
    print_header "Criando Backup"
    
    backup_dir="/tmp/42_backup_$(date +%Y%m%d_%H%M%S)"
    log_info "Backup em: $backup_dir"
    
    mkdir -p "$backup_dir"
    
    # Backup do .gitmodules
    [ -f .gitmodules ] && cp .gitmodules "$backup_dir/.gitmodules.bak"
    
    # Backup de projetos importantes
    for project in 42_common_core/rank02/* 42_common_core/rank03/*; do
        [ -d "$project" ] && cp -r "$project" "$backup_dir/" 2>/dev/null || true
    done
    
    log_success "Backup criado: $backup_dir"
    echo "$backup_dir" > /tmp/42_last_backup.txt
}

run_pipeline() {
    print_header "Pipeline de Organização"
    
    echo "Etapas:"
    echo "  1. Converter projetos existentes (rank02-06 + extras)"
    echo "  2. Criar estruturas de specializations"
    echo "  3. Push e conversão de specializations"
    echo "  4. Verificação final"
    echo ""
    echo "Executar pipeline completa? (y/n)"
    read -r run_full
    
    if [[ ! "$run_full" =~ ^[Yy]$ ]]; then
        log_warn "Pipeline cancelada"
        exit 0
    fi
    
    # Etapa 1
    print_header "Etapa 1/3: Converter Projetos Existentes"
    ./auto_convert_submodules.sh
    
    # Etapa 2
    print_header "Etapa 2/3: Criar Estruturas Specializations"
    ./init_specializations.sh
    
    # Etapa 3
    print_header "Etapa 3/3: Push Specializations"
    ./auto_push_specializations.sh
}

verify_setup() {
    print_header "Verificação Final"
    
    # Conta submódulos
    total=$(git submodule status | wc -l)
    log_info "Total de submódulos: $total"
    
    # Verifica .gitmodules
    if [ -f .gitmodules ]; then
        urls_incomplete=$(grep -c "url = https://github.com$" .gitmodules || true)
        if [ $urls_incomplete -gt 0 ]; then
            log_warn "$urls_incomplete URLs incompletas em .gitmodules"
            echo "Corrigir agora? (y/n)"
            read -r fix_urls
            if [[ "$fix_urls" =~ ^[Yy]$ ]]; then
                log_info "Atualizando URLs..."
                # Atualizar URLs incompletas
                sed -i 's|url = https://github.com$|url = https://github.com/Milsonyujiaoki|g' .gitmodules
                log_success "URLs corrigidas"
            fi
        else
            log_success "Todas URLs válidas"
        fi
    fi
    
    # Status git
    if git diff --quiet && git diff --staged --quiet; then
        log_success "Repositório limpo"
    else
        log_warn "Mudanças não commitadas"
        git status -s
    fi
    
    echo ""
    echo "Submódulos por categoria:"
    echo "  Piscine: $(git submodule status | grep -c "piscine/" || echo 0)"
    echo "  Common Core: $(git submodule status | grep -c "42_common_core/" || echo 0)"
    echo "  Specializations: $(git submodule status | grep -c "42_specializations/" || echo 0)"
    echo "  Extras: $(git submodule status | grep -c "extras/" || echo 0)"
}

final_steps() {
    print_header "Próximos Passos"
    
    echo "✅ Organização completa!"
    echo ""
    echo "Execute:"
    echo ""
    echo "  # Push do repositório principal"
    echo "  git push origin main"
    echo ""
    echo "  # Atualizar submódulos"
    echo "  git submodule update --init --recursive"
    echo ""
    echo "  # Testar clone"
    echo "  cd /tmp && git clone --recurse-submodules git@github.com:Milsonyujiaoki/42.git"
    echo ""
    
    backup_path=$(cat /tmp/42_last_backup.txt 2>/dev/null || echo "N/A")
    echo "📦 Backup salvo em: $backup_path"
    echo ""
    echo "📚 Documentação: SUBMODULES_SETUP_GUIDE.md"
}

# Main
main() {
    clear
    
    cat << "EOF"
    _____ ___   ____        _                         _       _           
   |  |  |__ \ / ___| _   _| |__  _ __ ___   ___   __| |_   _| | ___  ___ 
   | |_| |  ) |\___ \| | | | '_ \| '_ ` _ \ / _ \ / _` | | | | |/ _ \/ __|
   |_____|  / /  ___) | |_| | |_) | | | | | | (_) | (_| | |_| | |  __/\__ \
   |_____|_|_| |____/ \__,_|_.__/|_| |_| |_|\___/ \__,_|\__,_|_|\___||___/
                                                                            
   Organização Automática de Submódulos                                    
EOF
    
    echo ""
    
    cd /home/dev-yuji/projetos/42 || log_error "Diretório não encontrado"
    
    check_prerequisites
    show_summary
    
    echo ""
    echo "Criar backup antes de continuar? (recomendado) (y/n)"
    read -r do_backup
    if [[ "$do_backup" =~ ^[Yy]$ ]]; then
        create_backup
    fi
    
    run_pipeline
    verify_setup
    final_steps
    
    echo ""
    log_success "Pipeline completa executada!"
}

main

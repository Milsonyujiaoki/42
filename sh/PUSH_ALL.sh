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

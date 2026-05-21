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

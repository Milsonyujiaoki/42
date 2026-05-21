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

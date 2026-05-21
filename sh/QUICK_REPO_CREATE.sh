#!/bin/bash
# Quick repo creator - cria todos repos no GitHub de uma vez

GITHUB_USER="Milsonyujiaoki"

echo "╔════════════════════════════════════════════╗"
echo "║   Criador Rápido de Repos GitHub          ║"
echo "╔════════════════════════════════════════════╗"
echo ""
echo "Total: 47 repositórios"
echo ""
echo "Método 1 - GitHub CLI (automático):"
echo "════════════════════════════════════════════"
cat << 'GH_CLI'
sudo apt install gh -y
gh auth login

# Projetos existentes (15)
gh repo create Milsonyujiaoki/pipex --public
gh repo create Milsonyujiaoki/push_swap --public
gh repo create Milsonyujiaoki/so_long --public
gh repo create Milsonyujiaoki/minishell --public
gh repo create Milsonyujiaoki/philosophers --public
gh repo create Milsonyujiaoki/cub3d --public
gh repo create Milsonyujiaoki/miniRT --public
gh repo create Milsonyujiaoki/netpractice --public
gh repo create Milsonyujiaoki/cpp_modules --public
gh repo create Milsonyujiaoki/inception --public
gh repo create Milsonyujiaoki/webserv --public
gh repo create Milsonyujiaoki/ft_transcendence --public
gh repo create Milsonyujiaoki/ft_irc --public
gh repo create Milsonyujiaoki/libasm --public
gh repo create Milsonyujiaoki/malloc --public

# Specializations (32)
gh repo create Milsonyujiaoki/42-ai-distributed_training --public
gh repo create Milsonyujiaoki/42-ai-inference_engine --public
gh repo create Milsonyujiaoki/42-ai-llm_runtime --public
gh repo create Milsonyujiaoki/42-ai-neural_network --public
gh repo create Milsonyujiaoki/42-ai-vector_database --public
gh repo create Milsonyujiaoki/42-cybersecurity-exploit_lab --public
gh repo create Milsonyujiaoki/42-cybersecurity-malware_analysis --public
gh repo create Milsonyujiaoki/42-cybersecurity-packet_sniffer --public
gh repo create Milsonyujiaoki/42-cybersecurity-reverse_engineering --public
gh repo create Milsonyujiaoki/42-cybersecurity-secure_server --public
gh repo create Milsonyujiaoki/42-devops-ci_cd --public
gh repo create Milsonyujiaoki/42-devops-kubernetes --public
gh repo create Milsonyujiaoki/42-devops-monitoring --public
gh repo create Milsonyujiaoki/42-devops-observability --public
gh repo create Milsonyujiaoki/42-devops-terraform --public
gh repo create Milsonyujiaoki/42-graphics-doom_engine --public
gh repo create Milsonyujiaoki/42-graphics-game_engine --public
gh repo create Milsonyujiaoki/42-graphics-renderer --public
gh repo create Milsonyujiaoki/42-graphics-vulkan_renderer --public
gh repo create Milsonyujiaoki/42-networking-api_gateway --public
gh repo create Milsonyujiaoki/42-networking-distributed_cache --public
gh repo create Milsonyujiaoki/42-networking-grpc_gateway --public
gh repo create Milsonyujiaoki/42-networking-http_server --public
gh repo create Milsonyujiaoki/42-networking-message_broker --public
gh repo create Milsonyujiaoki/42-networking-reverse_proxy --public
gh repo create Milsonyujiaoki/42-networking-service_mesh --public
gh repo create Milsonyujiaoki/42-networking-websocket_server --public
gh repo create Milsonyujiaoki/42-systems-bootloader --public
gh repo create Milsonyujiaoki/42-systems-compiler --public
gh repo create Milsonyujiaoki/42-systems-container_runtime --public
gh repo create Milsonyujiaoki/42-systems-distributed_runtime --public
gh repo create Milsonyujiaoki/42-systems-filesystem --public
gh repo create Milsonyujiaoki/42-systems-interpreter --public
gh repo create Milsonyujiaoki/42-systems-mini_kernel --public
gh repo create Milsonyujiaoki/42-systems-vm --public
GH_CLI

echo ""
echo ""
echo "Método 2 - API do GitHub (sem gh CLI):"
echo "════════════════════════════════════════════"
echo "Salve em create_repos_api.sh e execute:"
cat << 'API_SCRIPT'

#!/bin/bash
# Requer: token GitHub com permissões de repo
# Criar token em: https://github.com/settings/tokens

read -sp "GitHub Token: " TOKEN
echo ""

create_repo() {
    local name=$1
    curl -s -H "Authorization: token $TOKEN" \
         -H "Accept: application/vnd.github.v3+json" \
         https://api.github.com/user/repos \
         -d "{\"name\":\"$name\",\"private\":false}" > /dev/null
    echo "✓ $name"
}

# Projetos existentes
for repo in pipex push_swap so_long minishell philosophers cub3d miniRT netpractice cpp_modules inception webserv ft_transcendence ft_irc libasm malloc; do
    create_repo "$repo"
done

# Specializations
for repo in 42-ai-distributed_training 42-ai-inference_engine 42-ai-llm_runtime 42-ai-neural_network 42-ai-vector_database 42-cybersecurity-exploit_lab 42-cybersecurity-malware_analysis 42-cybersecurity-packet_sniffer 42-cybersecurity-reverse_engineering 42-cybersecurity-secure_server 42-devops-ci_cd 42-devops-kubernetes 42-devops-monitoring 42-devops-observability 42-devops-terraform 42-graphics-doom_engine 42-graphics-game_engine 42-graphics-renderer 42-graphics-vulkan_renderer 42-networking-api_gateway 42-networking-distributed_cache 42-networking-grpc_gateway 42-networking-http_server 42-networking-message_broker 42-networking-reverse_proxy 42-networking-service_mesh 42-networking-websocket_server 42-systems-bootloader 42-systems-compiler 42-systems-container_runtime 42-systems-distributed_runtime 42-systems-filesystem 42-systems-interpreter 42-systems-mini_kernel 42-systems-vm; do
    create_repo "$repo"
done
API_SCRIPT

echo ""
echo ""
echo "Método 3 - Manual via Browser:"
echo "════════════════════════════════════════════"
echo "https://github.com/new"
echo "Criar um por um (47 repos total)"
echo ""
echo "Depois de criar os repos, execute:"
echo "  ./PUSH_ALL.sh"
echo "  ./CONVERT_TO_SUBMODULES.sh"

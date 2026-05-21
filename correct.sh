#!/bin/bash

SEU_USER="Milsonyujiaoki"

# Lista exata das pastas do Common Core que deram erro fatal
projetos_falhados=(
    "born2beroot" "cpp_modules" "cub3d" "exam_rank" "fractol" 
    "ft_irc" "inception" "miniRT" "minishell" "minitalk" 
    "netpractice" "philosophers" "pipex" "push_swap" "so_long" 
    "transcendence" "webserv"
)

echo "A iniciar a correção dos submódulos falhados..."

for projeto in "${projetos_falhados[@]}"; do
    caminho="42_common_core/$projeto"
    
    echo "----------------------------------------"
    echo "A corrigir: $projeto..."
    
    # 1. Limpa qualquer rasto que tenha ficado preso no índice do Git
    git rm --cached -r "$caminho" 2>/dev/null
    
    # 2. Remove a pasta local que não tinha o .git (Forçado)
    rm -rf "$caminho"
    
    # 3. Adiciona o submódulo do GitHub do zero (isto vai clonar os ficheiros reais)
    git submodule add --force "https://github.com" "$caminho"
done

echo "----------------------------------------"
echo "Processo concluído!"

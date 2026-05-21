#!/bin/bash
SEU_USER="Milsonyujiaoki"

# Navega por todas as subpastas de segundo nível dentro de 42_specializations
for categoria in 42_specializations/*/; do
    for subpasta in "$categoria"*/; do
        [ -d "$subpasta" ] || continue
        
        nome_subpasta=$(basename "$subpasta")
        nome_categoria=$(basename "$categoria")
        caminho_completo="42_specializations/$nome_categoria/$nome_subpasta"
        
        echo "Transformando em submódulo individual: $nome_subpasta"
        
        git rm --cached -r "$caminho_completo" 2>/dev/null
        rm -rf "$caminho_completo"
        git submodule add --force "https://github.com" "$caminho_completo"
    done
done

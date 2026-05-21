#!/bin/bash
# QUICKSTART - Organização rápida de submódulos
# Para usuários que querem execução automática completa

echo "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━"
echo "  42 Submódulos - Quickstart"
echo "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━"
echo ""
echo "Este script vai:"
echo "  ✓ Instalar GitHub CLI (se necessário)"
echo "  ✓ Converter 15 projetos existentes"
echo "  ✓ Criar 32 projetos de specializations"
echo "  ✓ Configurar tudo como submódulos"
echo ""
echo "⏱️  Tempo estimado: 10-15 minutos"
echo ""
echo "Continuar? (y/n)"
read -r response

if [[ ! "$response" =~ ^[Yy]$ ]]; then
    echo "Cancelado."
    exit 0
fi

# Executa o script master
./organize_all.sh

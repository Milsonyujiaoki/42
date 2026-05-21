#!/bin/bash
# Status visual da organização

GREEN='\033[0;32m'
BLUE='\033[0;34m'
YELLOW='\033[1;33m'
BOLD='\033[1m'
NC='\033[0m'

echo ""
echo -e "${BOLD}╔══════════════════════════════════════════════════════════════╗${NC}"
echo -e "${BOLD}║                  STATUS - PROJETO 42                         ║${NC}"
echo -e "${BOLD}╚══════════════════════════════════════════════════════════════╝${NC}"
echo ""

# Submódulos existentes
existing=$(git submodule status 2>/dev/null | wc -l)
echo -e "${GREEN}✓ Submódulos já configurados:${NC} $existing"

# Projetos criados localmente
spec_count=$(find 42_specializations -name .git -type d 2>/dev/null | wc -l)
echo -e "${BLUE}→ Specializations criados:${NC} $spec_count"

# Projetos preparados
prep_count=0
for dir in 42_common_core/rank0{2..6}/*/ extras/*/; do
    [ -d "$dir/.git" ] && ((prep_count++)) || true
done 2>/dev/null
echo -e "${BLUE}→ Projetos preparados:${NC} $prep_count"

total_novo=$((spec_count + prep_count))
total_final=$((existing + total_novo))

echo ""
echo -e "${BOLD}ESTRUTURA:${NC}"
echo ""

# Piscine
piscine=$(git submodule status 2>/dev/null | grep -c "piscine/" || echo 0)
echo -e "  📚 Piscine:           ${GREEN}$piscine submódulos${NC}"

# Common Core
cc_sub=$(git submodule status 2>/dev/null | grep -c "42_common_core/" || echo 0)
cc_local=$(find 42_common_core/rank* -name .git -type d 2>/dev/null | wc -l)
echo -e "  🎓 Common Core:       ${GREEN}$cc_sub submódulos${NC} + ${YELLOW}$cc_local locais${NC}"

# Extras
extras_sub=$(git submodule status 2>/dev/null | grep -c "extras/" || echo 0)
extras_local=$(find extras -name .git -type d 2>/dev/null | wc -l)
echo -e "  ⭐ Extras:            ${GREEN}$extras_sub submódulos${NC} + ${YELLOW}$extras_local locais${NC}"

# Specializations
spec_sub=$(git submodule status 2>/dev/null | grep -c "42_specializations/" || echo 0)
spec_local=$(find 42_specializations -name .git -type d 2>/dev/null | wc -l)
echo -e "  🚀 Specializations:   ${GREEN}$spec_sub submódulos${NC} + ${YELLOW}$spec_local locais${NC}"

echo ""
echo -e "${BOLD}TOTAIS:${NC}"
echo -e "  Atual:  $existing submódulos"
echo -e "  Novos:  $total_novo projetos preparados"
echo -e "  Final:  ${BOLD}${GREEN}$total_final submódulos${NC}"
echo ""

echo -e "${BOLD}BREAKDOWN SPECIALIZATIONS:${NC}"
for cat in ai cybersecurity devops graphics networking systems; do
    count=$(find 42_specializations/$cat -name .git -type d 2>/dev/null | wc -l)
    printf "  %-15s %2d projetos\n" "$cat:" "$count"
done

echo ""
echo -e "${BOLD}╔══════════════════════════════════════════════════════════════╗${NC}"
echo -e "${BOLD}║                    PRÓXIMOS PASSOS                           ║${NC}"
echo -e "${BOLD}╚══════════════════════════════════════════════════════════════╝${NC}"
echo ""
echo "1️⃣  Ver comandos para criar repos:"
echo "    ./QUICK_REPO_CREATE.sh"
echo ""
echo "2️⃣  Push de todos projetos:"
echo "    ./PUSH_ALL.sh"
echo ""
echo "3️⃣  Converter para submódulos:"
echo "    ./CONVERT_TO_SUBMODULES.sh"
echo ""
echo "4️⃣  Push repositório principal:"
echo "    git push origin main"
echo ""
echo "5️⃣  Verificar:"
echo "    git submodule status"
echo ""

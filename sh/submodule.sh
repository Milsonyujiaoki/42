# 1. Defina o seu utilizador do GitHub corretamente
SEU_USER="Milsonyujiaoki"

# 2. Corre o loop por todas as subpastas do Common Core
for pasta in 42_common_core/*/; do
    nome_projeto=$(basename "$pasta")
    
    # Ignora se não for uma pasta válida
    [ -d "$pasta" ] || continue
    
    echo "A processar: $nome_projeto..."
    
    # Remove a pasta do histórico local para o Git aceitar o submódulo
    git rm --cached -r "$pasta" 2>/dev/null
    
    # Comando corrigido com o caminho completo do seu repositório
    git submodule add --force "https://github.com" "42_common_core/$nome_projeto"
done

SEU_USER="Milsonyujiaoki"

for pasta in piscine/*/; do
    nome_projeto=$(basename "$pasta")
    [ -d "$pasta" ] || continue
    
    echo "A processar: $nome_projeto..."
    git rm --cached -r "$pasta" 2>/dev/null
    git submodule add --force "https://github.com" "piscine/$nome_projeto"
done

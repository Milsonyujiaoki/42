#!/bin/bash

# Script para rodar Valgrind em todos os testes
# Flags: --leak-check=full --show-leak-kinds=all --track-origins=yes

VALGRIND_FLAGS="--leak-check=full --show-leak-kinds=all --track-origins=yes --error-exitcode=1"
LOG_DIR="valgrind_logs"
SUMMARY_FILE="valgrind_summary.txt"

# Criar diretório para logs
mkdir -p "$LOG_DIR"

# Limpar resumo anterior
> "$SUMMARY_FILE"

echo "======================================"
echo "Rodando testes com Valgrind"
echo "======================================"
echo ""

# Encontrar todos os testes
tests=$(find build/tests -type f -executable | sort)
total=$(echo "$tests" | wc -l)
count=0
failures=0
leaks_found=0

for test in $tests; do
    count=$((count + 1))
    test_name=$(basename "$test")
    test_dir=$(basename "$(dirname "$test")")
    log_file="$LOG_DIR/${test_dir}_${test_name}.log"
    
    echo "[$count/$total] Testando: $test_dir/$test_name"
    
    # Rodar valgrind
    valgrind $VALGRIND_FLAGS "$test" > "$log_file" 2>&1
    exit_code=$?
    
    if [ $exit_code -ne 0 ]; then
        failures=$((failures + 1))
        
        # Verificar se tem leak
        if grep -q "definitely lost\|indirectly lost\|possibly lost" "$log_file"; then
            leaks_found=$((leaks_found + 1))
            echo "  ❌ MEMORY LEAK detectado!"
            echo "LEAK: $test_dir/$test_name" >> "$SUMMARY_FILE"
            
            # Extrair resumo do leak
            grep -A 5 "LEAK SUMMARY" "$log_file" >> "$SUMMARY_FILE"
            echo "" >> "$SUMMARY_FILE"
        else
            echo "  ⚠️  Erro, mas sem leak"
            echo "ERROR (no leak): $test_dir/$test_name" >> "$SUMMARY_FILE"
        fi
    else
        echo "  ✅ OK - sem leaks"
        echo "OK: $test_dir/$test_name" >> "$SUMMARY_FILE"
    fi
done

echo ""
echo "======================================"
echo "Resumo"
echo "======================================"
echo "Total de testes: $total"
echo "Testes OK: $((total - failures))"
echo "Testes com problemas: $failures"
echo "Testes com memory leaks: $leaks_found"
echo ""
echo "Logs salvos em: $LOG_DIR/"
echo "Resumo salvo em: $SUMMARY_FILE"

exit $failures

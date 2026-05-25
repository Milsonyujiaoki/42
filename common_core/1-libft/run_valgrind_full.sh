#!/usr/bin/bash
# Script para rodar Valgrind em todos os testes com flags completas
# Flags: --leak-check=full --show-leak-kinds=all --track-origins=yes

VALGRIND_FLAGS="--leak-check=full --show-leak-kinds=all --track-origins=yes --error-exitcode=1"
LOG_DIR="valgrind_logs"
SUMMARY_FILE="valgrind_summary.txt"

# Criar diretório para logs
mkdir -p "$LOG_DIR"

# Limpar sumário anterior
> "$SUMMARY_FILE"

echo "========================================" | tee -a "$SUMMARY_FILE"
echo " Executando Valgrind em todos os testes" | tee -a "$SUMMARY_FILE"
echo "========================================" | tee -a "$SUMMARY_FILE"
echo "" | tee -a "$SUMMARY_FILE"

# Contadores
total=0
passed=0
failed=0

# Encontrar todos os executáveis de teste
tests=$(find build/tests -type f -executable | sort)

for test in $tests; do
    test_name=$(basename "$test")
    test_dir=$(dirname "$test" | sed 's|build/tests/||')
    log_file="$LOG_DIR/${test_dir}_${test_name}.log"
    
    total=$((total + 1))
    
    echo -n "[$total] Rodando $test_dir/$test_name ... "
    
    # Rodar valgrind
    valgrind $VALGRIND_FLAGS "$test" > "$log_file" 2>&1
    exit_code=$?
    
    if [ $exit_code -eq 0 ]; then
        echo "✓ PASSED" | tee -a "$SUMMARY_FILE"
        passed=$((passed + 1))
    else
        echo "✗ FAILED (leaks/errors detectados)" | tee -a "$SUMMARY_FILE"
        failed=$((failed + 1))
        echo "  Log: $log_file" | tee -a "$SUMMARY_FILE"
    fi
done

echo "" | tee -a "$SUMMARY_FILE"
echo "========================================" | tee -a "$SUMMARY_FILE"
echo " RESUMO" | tee -a "$SUMMARY_FILE"
echo "========================================" | tee -a "$SUMMARY_FILE"
echo "Total de testes: $total" | tee -a "$SUMMARY_FILE"
echo "Passou: $passed" | tee -a "$SUMMARY_FILE"
echo "Falhou: $failed" | tee -a "$SUMMARY_FILE"
echo "" | tee -a "$SUMMARY_FILE"

if [ $failed -eq 0 ]; then
    echo "✓ TODOS OS TESTES PASSARAM SEM MEMORY LEAKS!" | tee -a "$SUMMARY_FILE"
    exit 0
else
    echo "✗ $failed teste(s) apresentaram memory leaks ou erros" | tee -a "$SUMMARY_FILE"
    echo "" | tee -a "$SUMMARY_FILE"
    echo "Para detalhes, verifique os logs em: $LOG_DIR/" | tee -a "$SUMMARY_FILE"
    exit 1
fi

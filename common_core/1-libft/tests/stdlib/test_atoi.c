#include "libft.h"
#include <stdio.h>

int main() {
    // Testes básicos para ft_atoi
    printf("Testing ft_atoi...\n");
    
    const char *test_cases[] = {
        "42",
        "   -42",
        "4193 with words",
        "words and 987",
        "-91283472332",
        "+123",
        "   +0 123",
        "   -0 123",
        "2147483647", // INT_MAX
        "-2147483648", // INT_MIN
    };

    for (size_t i = 0; i < sizeof(test_cases) / sizeof(test_cases[0]); i++) {
        int result = ft_atoi(test_cases[i]);
        printf("ft_atoi(\"%s\") = %d\n", test_cases[i], result);
    }

    return 0;
}
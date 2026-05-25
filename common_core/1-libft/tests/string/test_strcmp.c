#include "libft.h"
#include <string.h>
#include <stdio.h>


int main() {
    const char *str1 = "Hello, World!";
    const char *str2 = "Hello, World!";
    const char *str3 = "Hello, C!";
    
    // Test ft_strcmp
    printf("Comparing str1 and str2: %d\n", ft_strcmp(str1, str2)); // Should be 0
    printf("Comparing str1 and str3: %d\n", ft_strcmp(str1, str3)); // Should be > 0
    printf("Comparing str3 and str1: %d\n", ft_strcmp(str3, str1)); // Should be < 0
    
    return 0;
}
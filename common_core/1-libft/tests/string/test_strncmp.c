#include "libft.h"
#include <string.h>
#include <stdio.h>


int main() {
    const char *str1 = "Hello, World!";
    const char *str2 = "Hello, World!";
    const char *str3 = "Hello, C!";
    
    // Test ft_strncmp
    printf("Comparing str1 and str2 (first 8 chars): %d\n", ft_strncmp(str1, str2, 8)); //  0
    printf("Comparing str1 and str3 (first 8 chars): %d\n", ft_strncmp(str1, str3, 8)); //  > 0
    printf("Comparing str3 and str1 (first 8 chars): %d\n", ft_strncmp(str3, str1, 8)); //  < 0
    
    return 0;
}
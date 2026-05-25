#include "libft.h"
#include <string.h>
#include <stdio.h> 
#include <stdlib.h>

int main(void) {
    char str[] = "Hello, World!";
    char ch = 'o';

    char *result = ft_strrchr(str, ch);
    if (result) {
        printf("Character '%c' found at position: %ld\n", ch, result - str);
    } else {
        printf("Character '%c' not found\n", ch);
    }

    return 0;
}
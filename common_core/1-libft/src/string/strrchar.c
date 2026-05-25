#include "libft.h"

char *ft_strrchr(const char* str, int ch){
    const char *last_occurrence = NULL;

    while (*str)
    {   // Check if the current character matches ch
        if (*str == (char)ch)
            // If we found the character, update the last occurrence
            last_occurrence = str;
        str++;
    }
    // Check for the null terminator if ch is '\0'
    if (ch == '\0')
        // If ch is the null terminator, return a pointer to it
        return (char *)str;
    // If we found the character, return a pointer to the last occurrence
    return (char *)last_occurrence;
}
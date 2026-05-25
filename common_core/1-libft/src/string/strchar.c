#include "libft.h"

char *ft_strchr(const char* str, int ch)
{   // Iterate through the string until we find the character or reach the null terminator
    while (*str)
    {   // Check if the current character matches ch
        if (*str == (char)ch)
            // If we found the character, return a pointer to it
            return (char *)str;
        str++;
    }
    // Check for the null terminator if ch is '\0'
    if (ch == '\0')
        // If ch is the null terminator, return a pointer to it
        return (char *)str;
    // If we didn't find the character, return NULL
    return NULL;
}
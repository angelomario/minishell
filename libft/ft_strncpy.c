#include "libft.h"

char *ft_strncpy(char *dest, char *source, int n)
{
    int i;

    i = -1;
    while (source[++i] && i < n)
        dest[i] = source[i];
    dest[i] = '\0';
    return (dest);
}
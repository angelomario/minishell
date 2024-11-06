#include "libft.h"

char *ft_strcpy(char *dest, char *source)
{
    int i;

    i = -1;
    while (source[++i])
        dest[i] = source[i];
    dest[i] = '\0';
    return (dest);
}
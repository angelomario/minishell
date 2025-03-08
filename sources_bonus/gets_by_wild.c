/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gets_by_wild.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquissan <aquissan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 11:10:08 by aquissan          #+#    #+#             */
/*   Updated: 2025/03/08 11:12:46 by aquissan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell_bonus.h"

char *get_wildcard_expression(char *input, int wildpos)
{
    int i;
    int j;
    char *expression;

    i = wildpos;
    while (input[wildpos] && input[wildpos] != ' ')
        wildpos++;
    while (input[i] && i > 0 && input[i] != ' ')
        i--;
    expression = (char *)malloc(sizeof(char) * (wildpos - i + 1));
    j = 0;
    while (i < wildpos)
        expression[j++] = input[i++];
    expression[j] = '\0';
    return (expression);
}

char *get_pathdir(char *input, int j)
{
    int i;
    int len;
    char *path;

    i = j;
    len = 0;
    while (--i >= 0)
    {
        if (input[i] && (input[i] == ' ' || input[i] == '\t'))
            break;
        len++;
    }
    if (len)
    {
        path = (char *)malloc(sizeof(char) * (len + 1));
        i = 0;
        while (i < len && input[j - len])
            path[i++] = input[j++ - len];
        path[i] = '\0';
        return (path);
    }
    return (NULL);
}

char *get_pos_wild(char *input, int j)
{
    int i;

    i = j;
    if (input && input[i])
    {
        if (input[i + 1])
            return (ft_strdup(&input[i + 1]));
    }
    return (NULL);
}

int append_pattern(char **str, char *pattern)
{
    char *tmp;

    if (pattern)
    {
        if ((pattern[0] != '/'))
            return (1);
        tmp = ft_strjoin(*str, pattern);
        free(*str);
        *str = tmp;
        return (0);
    }
    return (0);
}

char *get_rest(char *input)
{
    int i;

    i = -1;
    while (input && input[++i])
    {
        if (input[i] == '*')
        {
            while (input[i] && (input[i] != ' ' && input[i] != '\t'))
                i++;
            if (input[i])
                return (ft_strdup(&input[i]));
            return (NULL);
        }
    }
    return (NULL);
}
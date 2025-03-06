/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquissan <aquissan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 06:35:27 by aquissan          #+#    #+#             */
/*   Updated: 2025/03/06 18:20:08 by aquissan         ###   ########.fr       */
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
    if (len && input[j - 1] == '/')
    {
        path = (char *)malloc(sizeof(char) * (len + 1));
        i = 0;
        while (i < len && input[j - len])
            path[i++] = input[j++ - len];
        path[i] = '\0';
        return (path);
    }
    return (ft_strdup("./"));
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
        if ((pattern[0] == '.'))
            return (1);
        tmp = ft_strjoin(*str, pattern);
        free(*str);
        *str = tmp;
        return (0);
    }
    return (0);
}

char *sep_pattern(char **pattern)
{
    int i;
    char *pos;

    i = 0;
    while (*pattern && (*pattern)[i])
    {
        if ((*pattern)[i] == '*')
        {
            pos = ft_strdup(&(*pattern)[i]);
            (*pattern)[i] = '\0';
            return (pos);
        }
        i++;
    }
    return (NULL);
}

int append_pos_pattern(char **str, char *pos)
{
    char *tmp;

    if (pos)
    {
        tmp = ft_strjoin(*str, pos);
        free(*str);
        *str = tmp;
        return (0);
    }
    return (1);
}

int check_inclusion(char **str, char *pattern)
{
    int lenstr;
    int lenpatt;

    if (pattern && *str)
    {
        if (append_pattern(str, pattern) == 0)
        {
            return (1);
        }
        lenpatt = ft_strlen(pattern) - 1;
        lenstr = ft_strlen((*str)) - 1;
        while ((*str)[lenstr] && pattern[lenpatt] && ((*str)[lenstr] == pattern[lenpatt]))
        {
            lenpatt--;
            lenstr--;
        }
        return (lenpatt < 0);
    }
    return ((*str) != NULL);
}

char **addstronmat(char ***mat, char *str)
{
    int i;
    char **matrix;

    if (str)
    {
        matrix = (char **)malloc((ft_count_matriz(*mat) + 2) * sizeof(char *));
        i = 0;
        while ((*mat) && (*mat)[i])
        {
            matrix[i] = ft_strdup((*mat)[i]);
            i++;
        }
        matrix[i++] = ft_strdup(str);
        matrix[i] = NULL;
        free(str);
        ft_arrtab(matrix);
        free_matriz(*mat);
        *mat = matrix;
        return (matrix);
    }
    return (NULL);
}

int include_pos(char **mat, char *pos)
{
    int i;
    char *tmp;

    i = -1;
    if (!pos)
        return (1);
    while (mat && mat[++i])
    {
        tmp = ft_strjoin(mat[i], pos);
        free(mat[i]);
        mat[i] = tmp;
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

int update_expression(char **expression, char **mat, t_wild *wild)
{
    int i;
    int j;
    int k;
    int len;
    char *expr;

    i = 0;
    len = 0;
    while (mat && mat[i])
        len += ft_strlen(mat[i++]);
    expr = (char *)malloc(sizeof(char) * (len + 1 + i));
    i = 0;
    k = 0;
    (void)wild;
    while (mat && mat[i])
    {
        j = -1;
        while (mat[i][++j])
            expr[k++] = mat[i][j];
        i++;
        if (mat[i])
            expr[k++] = ' ';
    }
    free_matriz(mat);
    return (expr[k] = '\0', free(*expression), *expression = expr, 0);
}

int set_waldcards(t_wild *wild, char **input)
{
    struct dirent *entry;
    char *full_path;
    DIR *dir;
    char **mat;

    dir = opendir(wild->path);
    if (!dir)
        return (perror("Error to open directory"), 1);
    mat = (char **)malloc(sizeof(char *) * 1);
    mat = NULL;
    while ((entry = readdir(dir)) != NULL)
    {
        if (entry->d_name && entry->d_name[0] != '.')
        {
            full_path = ft_strjoin(wild->path, entry->d_name);
            if (wild->pattern)
            {
                if (check_inclusion(&full_path, wild->pattern))
                    addstronmat(&mat, full_path);
                else
                    free(full_path);
            }
            else
                addstronmat(&mat, full_path);
        }
    }
    update_expression(input, mat, wild);
    return (closedir(dir), 0);
}

int construct_wild(char **expression, int *i, t_wild *wild)
{
    char *tmp;

    if (set_waldcards(wild, expression) == 1)
        return (1);
    if (wild->pre != NULL)
    {
        tmp = ft_strjoin(wild->pre, *expression);
        free(*expression);
        *expression = tmp;
    }
    if (wild->pos != NULL)
    {
        tmp = ft_strjoin(*expression, wild->pos);
        free(*expression);
        *expression = tmp;
    }
    (void)i;
    return (0);
}

char *get_pre_wild(char *expr, int pos)
{
    int i;
    char *pre;

    i = 0;
    while (expr && pos >= 0 && (expr[pos] != ' ' && expr[pos] != '\t'))
        --pos;
    if (pos >= 0)
    {
        pre = (char *)malloc(sizeof(char) * (pos + 2));
        while (expr && expr[i] && i <= pos)
        {
            pre[i] = expr[i];
            i++;
        }
        pre[i] = '\0';
        return (pre);
    }
    return (NULL);
}

char *get_pattern(char **pos, int i)
{
    // int j;
    char *pattern;
    char *tmp2;
    // char*   patt;

    // patt = *pos;
    tmp2 = NULL;
    if ((*pos) && (*pos)[i] != ' ')
    {
        pattern = get_wildcard_expression(*pos, i);
        if (ft_strlen(pattern) != ft_strlen(*pos))
        {
            tmp2 = ft_strdup(&(*pos)[ft_strlen(pattern)]);
        }
        free(*pos);
        if (tmp2)
            *pos = tmp2;
        else
            *pos = NULL;
        return (pattern);
    }
    return (NULL);
    // j = --i;
    // while (patt && patt[++i])
    // {
    //     if (patt[i] == ' ' && i > 0)
    //     {
    //         tmp = (char*)malloc(sizeof(char) * (i - j + 2));
    //         *pos = get_pos_wild(patt, i - 1);
    //         while (++j < i)
    //             tmp[j] = patt[j];
    //         tmp[j] = '\0';
    //         free(patt);
    //         return (tmp);
    //     }
    // }
    // tmp = ft_strdup(*pos);
    // if (*pos)
    //     return(free(*pos), *pos = NULL, tmp);
    // return (NULL);
}

// void    remove_word(char* str, int index)
// {
//     if (str)
//     {
//         while (str[index] && (str[index] != ' ' && str[index] != '\t'))
//             index++;
//         --index;
//         while (index >= 0 && str[index])
//         {
//             if (str[index] == ' ')
//                 break;
//             str[index] = ' ';
//             index--;
//         }
//     }
// }

void remove_word(char *str, int index)
{
    int start;
    int end;
    int i;

    if (!str)
        return;

    start = index;
    if (str[index] == '*')
        str[index] = ' ';
    while (start > 0 && str[start - 1] != ' ' && str[start - 1] != '\t')
        start--;
    end = index;
    while (str[end] && str[end] != ' ' && str[end] != '\t')
        end++;
    i = start;
    while (str[end])
        str[i++] = str[end++];
    str[i] = '\0';
}

int proccess_wildcard(t_master *master, char *input, int *j)
{
    int i;
    t_wild wild;
    char *expression;

    (void)master;
    expression = get_wildcard_expression(input, *j);
    i = 0;
    while (expression[i])
    {
        // printf("\n\n-- %i - %s\n\n", i, expression);
        if (expression[i] == '*')
        {
            wild.path = get_pathdir(expression, i);
            wild.pre = get_pre_wild(expression, i);
            wild.pos = get_pos_wild(expression, i);
            wild.pattern = get_pattern(&wild.pos, 0);
            // wild.expr = get_wildcard_expression(expression, i);
            // if (wild.path)
            //     printf("\nPath - %s\n", wild.path);
            // if (wild.pos)
            //     printf("\n\nPos - %s\n\n", wild.pos);
            // if (wild.pre)
            //     printf("Pre - %s\n", wild.pre);
            // if (wild.pattern)
            //     printf("Pattern - %s\n", wild.pattern);
            if (construct_wild(&expression, &i, &wild) == 1)
            {
                printf("Debug %i - %s\n", i, &expression[i]);
                remove_word(expression, i);
                i = -1;
            }
            if (wild.pos)
                free(wild.pos);
        }
        i++;
    }
    printf("\n--|%s|--\n\n", expression);
    return (0);
}

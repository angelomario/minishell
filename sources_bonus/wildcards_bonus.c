/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquissan <aquissan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 06:35:27 by aquissan          #+#    #+#             */
/*   Updated: 2025/03/08 11:24:28 by aquissan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell_bonus.h"

int check_inclusion(char **str, t_wild *wild)
{
    int lenstr;
    int lenpatt;

    if (wild->pattern && *str)
    {
        if (append_pattern(str, wild->pattern) == 0)
            return (1);
        lenpatt = ft_strlen(wild->pattern) - 1;
        lenstr = ft_strlen((*str)) - 1;
        while ((lenpatt >= 0 && lenstr >= 0) && ((*str)[lenstr] == wild->pattern[lenpatt]))
        {
            lenpatt--;
            lenstr--;
        }
        return (lenpatt < 0);
    }
    return ((*str) != NULL);
}

int update_expression(char **expression, char **mat)
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

int check_path(char **full, char *to_cmp)
{
    int i;
    int len;
    char *tmp;

    i = 0;
    len = ft_strlen(to_cmp);
    if (!to_cmp)
        return (0);
    if (to_cmp && to_cmp[len - 1] == '/')
    {
        tmp = ft_strjoin(to_cmp, *full);
        free(*full);
        *full = tmp;
        return (0);
    }
    while ((*full)[i] && to_cmp[i] && ((*full)[i] == to_cmp[i]))
        i++;
    if (to_cmp[i] == '\0')
        return (0);
    return (free(*full), 1);
}

int set_waldcards(t_wild *wild, char **input)
{
    struct dirent *entry;
    char *full_path;
    DIR *dir;
    char **mat;
    if (wild->path && wild->path[ft_strlen(wild->path) - 1] == '/')
        dir = opendir(wild->path);
    else
        dir = opendir("./");
    if (!dir)
        return (1);
    mat = (char **)malloc(sizeof(char *) * 1);
    mat[0] = NULL;
    while ((entry = readdir(dir)) != NULL)
    {
        if (entry->d_name && entry->d_name[0] != '.')
        {
            full_path = ft_strdup(entry->d_name);
            if (check_path(&full_path, wild->path))
                continue;
            if (wild->pattern)
            {
                if (check_inclusion(&full_path, wild))
                    addstronmat(&mat, full_path);
                else
                    free(full_path);
            }
            else
                addstronmat(&mat, full_path);
        }
    }
    update_expression(input, mat);
    return (closedir(dir), 0);
}

char *proccess_wildcard(char *input)
{
    int i;
    t_wild wild;

    i = -1;
    while (input && input[++i])
    {
        if (input[i] == '*')
        {
            wild.path = get_pathdir(input, i);
            wild.pre = get_pre_wild(input, i);
            wild.pos = get_pos_wild(input, i);
            wild.pattern = get_pattern(&wild.pos, 0);
            if (construct_wild(&input, &wild) == 1)
                i = remove_word(input, i);
            clean_wild(&wild);
        }
    }
    i = 0;
    while (input[i] && (input[i] == ' ' || input[i] == '\t'))
        i++;
    if (input[i] == '\0')
        return (free(input), NULL);
    return (input);
}

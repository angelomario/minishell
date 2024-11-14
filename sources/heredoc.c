/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquissan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 15:00:26 by aquissan          #+#    #+#             */
/*   Updated: 2024/11/12 15:01:02 by aquissan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int is_normal(char *del)
{
    int i;

    i = -1;
    if (!del)
        return (0);
    while (del[i] && (del[i] == ' ' || del[i] == '\t'))
        i++;
    return (del[i] != '\0');
}

char    *get_delimiter(char *str)
{
    char    ch;
    while(*str == ' ' || *str == '\t')
        str++;
    if ((ft_strcmp(str, "''") == 0) || (ft_strcmp(str, "\"\"") == 0))
    {
        ch = 10;
        return (ft_strdup(&(ch)));
    }
    else
        return (ft_strdup(str));
}

int ft_heredoc(t_master *master)
{
    char    **in;
    char    *del;

    in = ft_strsplit(master->imput, "<<");
    rm_void(in);
    if (ft_count_matriz(in) >= 2)
    {
        while(*(++in))
        {
            del = get_delimiter(*in);
            printf("delimiter: %s\n", del);
            free(del);
        }
    }
    return (-1);
}


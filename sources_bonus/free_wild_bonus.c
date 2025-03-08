/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_wild_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquissan <aquissan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 11:22:01 by aquissan          #+#    #+#             */
/*   Updated: 2025/03/08 11:23:27 by aquissan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell_bonus.h"

int clean_wild(t_wild *wild)
{
    if (wild->path)
        free(wild->path);
    if (wild->pattern)
        free(wild->pattern);
    if (wild->pos)
        free(wild->pos);
    if (wild->pre)
        free(wild->pre);
    wild->path = NULL;
    wild->pattern = NULL;
    wild->pos = NULL;
    wild->pre = NULL;
    return (0);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_extra.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquissan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 17:12:58 by aquissan          #+#    #+#             */
/*   Updated: 2025/01/07 17:13:02 by aquissan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_cleanredchild(t_master *master, char **command, char *tmp, char **in)
{
	free_matriz(command);
	free(tmp);
	free_matriz(master->in);
	free_matriz(master->options);
	free_matriz(master->environ);
	free(master->history);
	free_matriz(in);
	free(master->imput);
	return (0);
}

int	ft_cleanpipechild(t_master *master, char **command, char *tmp, char **in)
{
	(void)command;
	free(tmp);
	free_matriz(master->in);
	free_matriz(master->options);
	free_matriz(master->environ);
	free(master->history);
	free_matriz(in);
	free(master->imput);
	return (0);
}

int	quit_of_conf(t_master *master, char **in)
{
	ft_cleanredchild(master, in, ft_strdup("Angelo"), ft_arrdup(in));
	return (1);
}

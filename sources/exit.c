/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquissan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 14:58:42 by aquissan          #+#    #+#             */
/*   Updated: 2024/10/29 14:58:58 by aquissan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// This function simplily exit of the actual proccess
void	ft_exit(t_master *master)
{
	free_matriz(master->in);
	free(master->imput);
	exit(0);
}

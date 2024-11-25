/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquissan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 16:29:23 by aquissan          #+#    #+#             */
/*   Updated: 2024/11/19 16:29:47 by aquissan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sigint_handler(int sig)
{
    (void)sig;
	printf("\nRecebi SIGINT (Ctrl-C)! Continuando...\n");
}

void	sigquit_handler(int sig)
{
    (void)sig;
	printf("\nRecebi SIGQUIT (Ctrl-\\)! Saindo...\n");
}

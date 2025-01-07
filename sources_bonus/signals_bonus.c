/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joandre <joandre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 16:29:23 by aquissan          #+#    #+#             */
/*   Updated: 2024/12/11 01:37:02 by joandre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell_bonus.h"

extern volatile sig_atomic_t	g_sig;

void	exit_130(int sig)
{
	g_sig = sig;
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		exit(130);
	}
}

void	sigint_handler(int sig)
{
	g_sig = sig;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	breaker(int sig)
{
	g_sig = sig;
	printf("\n");
}

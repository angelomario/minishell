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

#include "minishell.h"

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

int	kill_proccess(int pid, char *del, int stdout)
{
	if (del && (stdout))
	{
		ft_putstr_fd("bash: warning:  by EOF (expected `',", stdout);
		ft_putstr_fd(del, stdout);
		ft_putstr_fd("')\n", stdout);
	}
	if (pid > 0)
	{
		kill(pid, SIGKILL);
		return (0);
	}
	return (-1);
}

void	breaker(int sig)
{
	g_sig = sig;
	printf("\n");
}

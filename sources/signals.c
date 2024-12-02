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

void	exit_130(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		exit(1);
	}
}

void	sigint_handler(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}


int	kill_proccess(int pid, char *del, int stdout)
{
	if (del && (stdout))
	{
		ft_putstr_fd("bash: warning: here-document at line 5 delimited by end-of-file (wanted `",
			stdout);
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

void	breaker(int	sig)
{
	(void)sig;
	write(1, "\n", 1);
}

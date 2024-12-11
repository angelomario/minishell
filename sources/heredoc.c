/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joandre <joandre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 07:31:20 by aquissan          #+#    #+#             */
/*   Updated: 2024/12/11 01:40:04 by joandre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	child(t_master *master, char *del, int pipe_fd[2])
{
	char	*input;

	close(pipe_fd[0]);
	signal(SIGINT, exit_130);
	dup2(master->stdin_fd, STDIN_FILENO);
	dup2(master->stdout_fd, STDOUT_FILENO);
	while (1)
	{
		input = readline("heredoc> ");
		if (!input)
		{
			print_default_fd(master,
				ft_strjoin("bash: warning: here-doc at EOF (wanted `",
					del));
			print_default_fd(master, ft_strdup("')\n"));
			exit(127);
		}
		input = expan_env(master, input);
		if (ft_strcmp(input, del) == 0)
			break ;
		write(pipe_fd[1], input, ft_strlen(input));
		write(pipe_fd[1], "\n", 1);
		free(input);
	}
	return (close(pipe_fd[1]), free(input), 0);
}

int	ft_heredoc(t_master *master, char *del)
{
	int	pipe_fd[2];

	if (pipe(pipe_fd) == -1)
		return (perror("Pipe"), -1);
	master->pid_child = fork();
	if (master->pid_child == 0)
	{
		signal(SIGINT, sigint_handler);
		exit(child(master, del, pipe_fd));
	}
	else
	{
		close(pipe_fd[1]);
		if (dup2(pipe_fd[0], STDIN_FILENO) == -1)
			return (perror("Pipe"), close(pipe_fd[1]), -1);
		close(pipe_fd[0]);
		waitpid(master->pid_child, &master->status, 0);
	}
	return (0);
}

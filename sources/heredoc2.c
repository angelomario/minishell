/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquissan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 07:31:20 by aquissan          #+#    #+#             */
/*   Updated: 2024/11/23 07:31:29 by aquissan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	child(char *del, int pipe_fd[2])
{
	char	*input;

	close(pipe_fd[0]);
	input = readline("heredoc> ");
	while (1)
	{
		if (ft_strcmp(input, del) == 0)
			break ;
		write(pipe_fd[1], input, ft_strlen(input));
		write(pipe_fd[1], "\n", 1);
		free(input);
		input = readline("heredoc> ");
	}
	close(pipe_fd[1]);
	free(input);
	return (0);
}

int	ft_heredoc(char *del)
{
	int	pipe_fd[2];
	pid_t	pid;
	if (pipe(pipe_fd) == -1)
		return (perror("Pipe"), -1);
	pid = fork();
	if (pid == 0)
	{
		exit(child(del, pipe_fd));
	}
	else
	{
		close(pipe_fd[1]);
		if (dup2(pipe_fd[0], STDIN_FILENO) == -1)
			return (perror("Pipe"), close(pipe_fd[1]), -1);
		close(pipe_fd[0]);
		waitpid(pid, NULL, 0);
	}
	return (0);
}

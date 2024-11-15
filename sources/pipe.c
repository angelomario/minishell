/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquissan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 11:51:06 by aquissan          #+#    #+#             */
/*   Updated: 2024/11/13 11:51:31 by aquissan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cur_instruction(t_master *master, int pipefd[2], int input_fd)
{
	char	**tmp;

	if (input_fd != STDIN_FILENO)
	{
		if (dup2(input_fd, STDIN_FILENO) == -1)
		{
			perror("Dup2 input error");
			exit(1);
		}
		close(input_fd);
	}
	if (*(master->in + 1) != NULL)
	{
		close(pipefd[0]);
		if (dup2(pipefd[1], STDOUT_FILENO) == -1)
		{
			perror("Dup2 output error");
			exit(1);
		}
		close(pipefd[1]);
	}
	tmp = ft_split(*(master->in), ' ');
	ft_bin(tmp);
	return (free(tmp), exit(0), 0);
}

int	reset_fd(t_master *master, int pipefd[2], int *input_fd)
{
	if (*input_fd != STDIN_FILENO)
		close(*input_fd);
	if (*(master->in + 1) != NULL)
	{
		close(pipefd[1]);
		*input_fd = pipefd[0];
	}
	return (0);
}

int	ft_pipe(t_master *master)
{
	int	pipefd[2];
	int	input_fd;
	int	pid;

	input_fd = STDIN_FILENO;
	while (*(master->in) != NULL)
	{
		if (*(master->in + 1) != NULL)
			if (pipe(pipefd) == -1)
				return (perror("Pipe error"), -1);
		pid = fork();
		if (pid == -1)
			return (perror("Fork error"), -1);
		if (pid == 0)
			cur_instruction(master, pipefd, input_fd);
		else
		{
			waitpid(pid, NULL, 0);
			reset_fd(master, pipefd, &input_fd);
			master->in++;
		}
	}
	return (0);
}

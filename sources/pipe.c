/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joandre <joandre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 11:51:06 by aquissan          #+#    #+#             */
/*   Updated: 2024/12/11 01:04:05 by joandre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cur_instruction(t_master *master, int pipefd[2], int input_fd, char **input)
{
	ft_replace_c(*input);
	if (ft_strcmp(*input, "\"\"") == 0)
	{
		return (print_default_fd(master,
				ft_strdup("bash: : command not found\n")), exit(127), 0);
	}
	if (input_fd != STDIN_FILENO)
	{
		if (dup2(input_fd, STDIN_FILENO) == -1)
		{
			perror("Dup2 input error");
			exit(1);
		}
		close(input_fd);
	}
	if (*(input + 1) != NULL)
	{
		close(pipefd[0]);
		if (dup2(pipefd[1], STDOUT_FILENO) == -1)
			return (perror("Dup2 output error"), exit(1), -1);
		close(pipefd[1]);
	}
	ft_redirect(master, *input);
	return (exit(0), 0);
}

int	reset_fd(t_master *master, int pipefd[2], int *input_fd)
{
	close(pipefd[1]);
	if (*input_fd != STDIN_FILENO)
		close(*input_fd);
	if (*(master->in + 1) != NULL)
	{
		*input_fd = pipefd[0];
	}
	else
	{
		dup2(*input_fd, STDIN_FILENO);
	}
	return (0);
}

int	ft_pipe(t_master *master)
{
	int	pipefd[2];
	int	*pid;
	int	i;

	pid = malloc(sizeof(int) * ft_count_matriz(master->in));
	i = -1;
	while (master->in[++i] != NULL)
	{
		if (master->in[i + 1] != NULL)
			if (pipe(pipefd) == -1)
				return (perror("Pipe"), -1);
		pid[i] = fork();
		if (pid[i] == -1)
			return (free(pid), perror("Fork"), -1);
		if (pid[i] == 0)
			cur_instruction(master, pipefd, master->stdin_fd, &master->in[i]);
		else
			reset_fd(master, pipefd, &master->stdin_fd);
	}
	while (i-- != 0)
	{
		waitpid(pid[i], &master->status, 0);
		master->status = WEXITSTATUS(master->status);
	}
	return (free(pid), 0);
}

int	ft_find_way(t_master *master)
{
	if ((ft_count_matriz(master->in) >= 2 || ft_countchar(master->imput, 127))
		&& ft_valid_args(master->in))
	{
		do_pipe(master);
	}
	else
	{
		if (ft_redirect(master, master->imput) == -1)
			return (-1);
	}
	return (0);
}

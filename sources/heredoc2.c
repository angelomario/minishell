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

// int	creat_file_tmp(char *nome_arquivo)
// {
// 	int	fd;

// 	fd = open(nome_arquivo, O_CREAT | O_WRONLY | O_APPEND, 0644);
// 	if (fd == -1)
// 	{
// 		perror("Erro ao abrir ou criar o arquivo");
// 		return (-1);
// 	}
// 	return (fd);
// }

// int	child(char *del)
// {
// 	char	*input;
// 	int		fd;

// 	fd = creat_file_tmp("/tmp/.heredoc.txt");
// 	if (fd == -1)
// 		return (perror("Erro ao criar arquivo temporário"), 1);
// 	// perror("chegou");
// 	input = readline("heredoc> ");
// 	while (input && del && ft_strcmp(input, del) != 0)
// 	{
// 		write(fd, input, strlen(input));
// 		write(fd, "\n", 1);
// 		free(input);
// 		input = readline("heredoc> ");
// 	}
// 	free(input);
// 	close(fd);
// 	fd = open("/tmp/.heredoc.txt", O_RDONLY);
// 	if (fd == -1)
// 		return (perror("Erro ao reabrir o arquivo"), 1);
// 	if (dup2(fd, STDIN_FILENO) == -1)
// 		return (perror("Erro ao redirecionar stdin"), close(fd), 1);
// 	close(fd);
// 	free(del);
// 	return (0);
// }

// int	ft_heredoc(char *del)
// {
// 	if (del)
// 	{
// 		child(del);
// 		return (0);
// 	}
// 	return (1);
// }

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

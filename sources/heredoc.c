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

int	child(t_master *master, char *del, int pipe_fd[2])
{
	char	*input;

	close(pipe_fd[0]);
	signal(SIGINT, exit_130);
	if ((dup2(master->stdin_fd, STDIN_FILENO) == -1) || (dup2(master->stdout_fd,
				STDOUT_FILENO) == -1))
	{
		print_default_fd(master,
			ft_strdup("Erro ao restaurar as saidas padrao\n"));
	}
	while (1)
	{
		input = readline("heredoc> ");
		if (ft_strcmp(input, del) == 0)
			break ;
		if (!input)
		{
			print_default_fd(master, ft_strjoin("bash: warning: here-document at line 5 delimited by end-of-file (wanted `", del));
			print_default_fd(master, ft_strdup("')\n"));
			exit(127);
		}
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

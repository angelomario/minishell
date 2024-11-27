/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquissan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 15:00:26 by aquissan          #+#    #+#             */
/*   Updated: 2024/11/12 15:01:02 by aquissan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_normal(char *del)
{
	int	i;

	i = -1;
	if (!del)
		return (0);
	while (del[i] && (del[i] == ' ' || del[i] == '\t'))
		i++;
	return (del[i] != '\0');
}

char	*get_delimiter(char *str)
{
	char	ch;

	while (*str == ' ' || *str == '\t')
		str++;
	if ((ft_strcmp(str, "''") == 0) || (ft_strcmp(str, "\"\"") == 0))
	{
		ch = 10;
		return (ft_strdup(&(ch)));
	}
	else
		return (ft_strdup(str));
}

int	father(t_master *master, int pipe_fd[2], int default_stdin, char **command)
{
	// Processo pai: redireciona o pipe para o stdin
	close(pipe_fd[1]); // Fecha o lado de escrita do pipe no pai
	// Redireciona o lado de leitura do pipe para o stdin
	if (dup2(pipe_fd[0], STDIN_FILENO) == -1)
	{
		perror("Dup2");
		close(pipe_fd[0]);
		return (-1);
	}
	close(pipe_fd[0]); // Fecha o lado de leitura do pipe após redirecionar
	// Aguarda o término do processo filho
	waitpid(master->pid_child, &master->status, 0);
	if ((master->pid_child = fork()) == 0)
		ft_bin(master, command);
	else
		waitpid(master->pid_child, NULL, 0);
	// Após o término do heredoc, restaura o stdin original
	if (dup2(default_stdin, STDIN_FILENO) == -1)
	{
		perror("Dup2 restore");
		close(default_stdin);
		return (-1);
	}
	close(default_stdin);
	return (0);
}

int	child2(t_master *master, int pipe_fd[2], char **in)
{
	char	*del;
	char	*imput;

	close(pipe_fd[0]);
	in = ft_strsplit(master->imput, "<<");
	if (ft_count_matriz(in) >= 2)
	{
		del = get_delimiter(in[1]);
		rm_void(in);
		// Captura as entradas até o delimitador
		imput = readline("heredoc> ");
		while (imput && ft_strcmp(imput, del) != 0)
		{
			write(pipe_fd[1], imput, ft_strlen(imput));
			write(pipe_fd[1], "\n", 1);
			free(imput);
			imput = readline("heredoc> ");
		}
		free(imput);
	}
	free(del);
	close(pipe_fd[1]); // Fecha o lado de escrita do pipe no filho
	return (0);
}

int	heredoc(t_master *master, char **in)
{
	int		pipe_fd[2];
	int		default_stdin;
	char	**command;

	default_stdin = dup(STDIN_FILENO);
	if (ft_count_matriz(in) >= 2)
	{
		command = ft_split(in[0], ' ');
		if (pipe(pipe_fd) == -1)
			return (perror("Pipe"), -1);
		if ((master->pid_child = fork()) == 0)
		{
			exit(child2(master, pipe_fd, in));
		}
		else
			father(master, pipe_fd, default_stdin, command);
		return (free_matriz(in), 0);
	}
	return (free_matriz(in), 1);
}

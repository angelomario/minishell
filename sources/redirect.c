/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joandre <joandre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 09:00:25 by aquissan          #+#    #+#             */
/*   Updated: 2024/11/26 08:10:16 by joandre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int	creat_file(char *name, char **msg, int append)
// {
// 	int	fd;
// 	int	default_fd;

// 	default_fd = STDOUT_FILENO;
// 	if (!name)
// 		return (-1);
// 	if (append)
// 		fd = open(name, O_CREAT | O_WRONLY | O_APPEND, 0644);
// 	else
// 		fd = open(name, O_CREAT | O_WRONLY | O_TRUNC, 0644);
// 	if (fd < 0)
// 		return (perror("Erro ao abrir o arquivo"), -1);
// 	// Redireciona stdout
// 	dup2(fd, STDOUT_FILENO);
// 	// Redireciona stderr
// 	dup2(fd, STDERR_FILENO);
// 	while (msg && *msg)
// 		printf("%s", *msg++);
// 	close(fd);
// 	dup2(default_fd, STDOUT_FILENO);
// 	return (0);
// }

int	redir_input(char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (-1);
	if (dup2(fd, STDIN_FILENO) == -1)
	{
		perror("Dup2");
		close(fd);
		return (-1);
	}
	close(fd);
	return (0);
}

int	redir_output(char *name, int append)
{
	int	fd;

	if (!name)
		return (-1);
	if (append)
		fd = open(name, O_CREAT | O_WRONLY | O_APPEND, 0644);
	else
		fd = open(name, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd < 0)
	{
		return (perror("Erro ao abrir o arquivo"), -1);
	}
	if (dup2(fd, STDOUT_FILENO) < 0)
	{
		perror("Erro ao redirecionar stdout");
		close(fd);
		return (-1);
	}
	return (close(fd), 0);
}

int	configure(char **in)
{
	int	i;

	i = 0;
	if (!in || !(*in))
		return (-1);
	while (in[i])
	{
		if (ft_strcmp(in[i], ">") == 0 && in[i + 1] != NULL)
			redir_output(in[++i], 0);
		else if (ft_strcmp(in[i], ">>") == 0 && in[i + 1] != NULL)
			redir_output(in[++i], 1);
		else if (ft_strcmp(in[i], "<") == 0 && in[i + 1] != NULL)
		{
			if (redir_input(in[++i]) == -1)
				return (-1);
		}
		else
			i++;
	}
	return (0);
}

int	there_is_redirect(char **in)
{
	int	there_is;
	int	i;

	i = 0;
	there_is = 0;
	while (in[i])
	{
		if (ft_strcmp(in[i], ">") == 0 && in[i + 1] != NULL)
			there_is = 1;
		else if (ft_strcmp(in[i], ">>") == 0 && in[i + 1] != NULL)
			there_is = 1;
		else if (ft_strcmp(in[i], "<") == 0 && in[i + 1] != NULL)
			there_is = 1;
		i++;
	}
	return (there_is);
}

int	do_heredoc(char **in)
{
	int	i;

	i = 0;
	while (in[i])
	{
		// if (ft_strcmp(in[i], "<<") == 0 && in[i + 1] != NULL)
		// 	return (ft_heredoc(in[++i]));
		i++;
	}
	return (1);
}

int	do_redirect(t_master *master, char **in)
{
	char	**command;

	master->pid_child = fork();
	if (master->pid_child == 0)
	{
		// do_heredoc(in);
		if (configure(in) == -1)
		{
			dup2(master->stdout_fd, STDOUT_FILENO);
			printf("bash: %s: No such file or directory\n", in[0]);
			return (-1);
		}
		format_imput(&in[0], 127);
		in[0] = expanded(master, in[0]);
		command = ft_split(in[0], 127);
		if (is_built_in(master, command) == 42 && (!is_redirect(in[0])
			|| (ft_count_matriz(in) < 2)))
		{
			ft_bin(master, command);
		}
		exit(0);
	}
	else
		waitpid(master->pid_child, &master->status, 0);
	return (0);
}

int	is_redirect(char *str)
{
	if (str)
	{
		if ((ft_strcmp(str, ">") == 0) || (ft_strcmp(str, ">>") == 0)
			|| (ft_strcmp(str, "<") == 0))
			return (1);
	}
	return (0);
}

int	ft_redirect(t_master *master, char *str)
{
	char	*tmp;
	char	**in;

	tmp = ft_format_in_redir(str, 0, 0, 127);
	in = ft_split(tmp, 127);
	rm_void(in);
	if (there_is_redirect(in))
	{
		if (do_redirect(master, in) == -1)
			return (-1);
	}
	else
	{
		free_matriz(in);
		format_imput(&tmp, 127);
		tmp = expanded(master, tmp);
		in = ft_split(tmp, 127);
		if ((is_built_in(master, in) == 42) && (!is_redirect(in[0])
			|| (ft_count_matriz(in) < 2)))
		{
			master->pid = fork();
			if (master->pid == 0)
				ft_bin(master, in);
			else
				waitpid(master->pid, &master->status, 0);
		}
	}
	return (0);
}

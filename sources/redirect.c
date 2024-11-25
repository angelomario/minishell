/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquissan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 09:00:25 by aquissan          #+#    #+#             */
/*   Updated: 2024/11/21 09:00:54 by aquissan         ###   ########.fr       */
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

char	*get_1word(char *in)
{
	char	*tmp;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (in)
	{
		while ((in[i] == ' ' || in[i] == '\t') && in[i])
			i++;
		tmp = (char *)malloc((ft_strlen(&in[i]) + 1) * sizeof(char));
		while ((in[i] != ' ' && in[i] != '\t') && in[i])
			tmp[j++] = in[i++];
		tmp[j] = '\0';
		return (tmp);
	}
	return (in);
}

int	redir_input(char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		perror("bash");
		return (-1);
	}
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
	if (dup2(fd, STDERR_FILENO) < 0)
	{
		perror("Erro ao redirecionar stderr");
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
			redir_input(in[++i]);
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
		if (ft_strcmp(in[i], "<<") == 0 && in[i + 1] != NULL)
			return (ft_heredoc(in[++i]));
		i++;
	}
	return (1);
}

int	do_redirect(t_master *master, char **in)
{
	int	i;

	i = 0;
	master->pid_child = fork();
	if (master->pid_child == 0)
	{
		if (!in || ft_count_matriz(in) < 1)
			return (0);
		do_heredoc(in);
		configure(in);
		while (in[i] != NULL)
		{
			printf("%ld %s\n", ft_strlen(in[i]), in[i]);
			i++;
		}
		exit(0);
	}
	else
		waitpid(master->pid_child, &master->status, 0);
	return (0);
}

int	ft_redirect(t_master *master, char *str)
{
	char	**in;

	(void)master;
	in = parsedel(str);
	if (there_is_redirect(in))
	{
		do_redirect(master, in);
	}
	else
	{
		master->pid_child = fork();
		if (master->pid_child == 0)
			ft_bin(ft_split(*in, ' '));
		else
			waitpid(master->pid_child, &master->status, 0);
	}
	return (0);
}

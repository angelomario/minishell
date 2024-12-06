/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joandre <joandre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 09:00:25 by aquissan          #+#    #+#             */
/*   Updated: 2024/12/03 08:33:19 by joandre          ###   ########.fr       */
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

char	*ft_check_type_redir(char *type_redir)
{
	char	*redir[5];
	char	*str;
	int		i;

	i = 0;
	redir[0] = ">";
	redir[1] = "<";
	redir[2] = ">>";
	redir[3] = "<<";
	redir[4] = NULL;
	while (redir[i])
	{
		str = redir[i];
		if (ft_strcmp(str, type_redir) == 0)
			return (str);
		i++;
	}
	return (NULL);
}

int	ft_len_redir(t_master *master, char **in)
{
	int	i;

	i = 0;
	while (in[i])
	{
		if (is_redirect(in[i]) && ((is_redirect(in[i + 1]) || !in[i + 1])))
		{
			print_default_fd(master, ft_strdup("bash: parse error near: "));
			if (ft_check_type_redir(in[i + 1]))
				i++;
			print_default_fd(master, ft_strdup(in[i]));
			print_default_fd(master, ft_strdup("\n"));
			return (1);
		}
		i++;
	}
	return (0);
}

int	redir_input(char *filename, int flag)
{
	int	fd;

	(void)flag;
	if (!filename)
		return (-1);
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

char	**add_str(char **matrix, char *new_string)
{
	char	**new_matrix;
	int		len;
	int		i;

	len = ft_count_matriz(matrix);
	i = -1;
	new_matrix = (char **)malloc((len + 2) * sizeof(char *));
	while (matrix[++i] != NULL)
		new_matrix[i] = ft_strdup(matrix[i]);
	new_matrix[i++] = ft_strdup(new_string);
	new_matrix[i] = NULL;
	free_matriz(matrix);
	return (new_matrix);
}

int	to_configure(t_master *master, char *param, int flag, int (*f)(char *, int))
{
	int		i;
	char	**mat;

	mat = ft_split(param, ' ');
	i = 1;
	(void)flag;
	(void)f;
	if (f(mat[0], flag) == -1)
		return (-1);
	if (ft_count_matriz(mat) > 1)
	{
		while (mat[i])
		{
			master->options = add_str(master->options, mat[i++]);
		}
	}
	free_matriz(mat);
	return (0);
}

int	configure(t_master *master, char **in)
{
	int	i;

	i = 0;
	if (!in || !(*in))
		return (-1);
	while (in[i])
	{
		if (ft_strcmp(in[i], ">") == 0 && in[i + 1] != NULL)
			to_configure(master, in[++i], 0, redir_output);
		else if (ft_strcmp(in[i], ">>") == 0 && in[i + 1] != NULL)
			to_configure(master, in[++i], 1, redir_output);
		else if (ft_strcmp(in[i], "<") == 0 && in[i + 1] != NULL)
		{
			if (to_configure(master, in[++i], 0, redir_input) == -1)
			{
				print_default_fd(master, ft_strjoin("bash: ", in[i]));
				print_default_fd(master,
					ft_strdup(": No such file or directory\n"));
				exit(127);
			}
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
		else if (ft_strcmp(in[i], "<<") == 0 && in[i + 1] != NULL)
			there_is = 1;
		i++;
	}
	return (there_is);
}

int	do_heredoc(t_master *master, char **in)
{
	int	i;

	i = 0;
	signal(SIGINT, exit_130);
	while (in[i])
	{
		if (ft_strcmp(in[i], "<<") == 0 && in[i + 1] != NULL)
		{
			ft_heredoc(master, in[++i]);
		}
		i++;
	}
	return (1);
}

char	**concatmatrix(t_master *master, char **mat1, char **mat2)
{
	char	*exp;
	int		i;

	i = 0;
	while (mat2[i] && mat2)
	{
		exp = expanded(master, mat2[i]);
		mat1 = add_str(mat1, exp);
		free(exp);
		i++;
	}
	return (mat1);
}

int	do_redirect(t_master *master, char **in)
{
	char	**command;

	master->pid_child = fork();
	if (master->pid_child == 0)
	{
		do_heredoc(master, in);
		configure(master, in);
		format_imput(&in[0], 127);
		in[0] = expanded(master, in[0]);
		command = concatmatrix(master, ft_split(in[0], 127), master->options);
		if (is_built_in(master, command) == 42 && (!is_redirect(in[0])
				|| ((ft_count_matriz(in) < 2))))
		{
			ft_bin(master, command);
		}
		exit(0);
	}
	else
	{
		signal(SIGINT, SIG_IGN);
		waitpid(master->pid_child, &master->status, 0);
		master->status = WEXITSTATUS(master->status);
		signal(SIGINT, sigint_handler);
	}
	return (0);
}

int	is_redirect(char *str)
{
	if (str)
	{
		if ((ft_strcmp(str, ">") == 0) || (ft_strcmp(str, ">>") == 0)
			|| (ft_strcmp(str, "<") == 0) || (ft_strcmp(str, "<<") == 0))
			return (1);
	}
	return (0);
}

// int	is_heredoc(char **in)
// {
// 	int	i;

// 	i = 0;
// 	while (in[i])
// 	{
// 		if ((ft_strcmp(in[i], "<<") == 0))
// 			return (1);
// 		i++;
// 	}
// 	return (0);
// }

int	only_cmd(t_master *master, char *tmp, char **in)
{
	free_matriz(in);
	format_imput(&tmp, 127);
	tmp = expanded(master, tmp);
	in = ft_split(tmp, 127);
	if ((is_built_in(master, in) == 42) && (!is_redirect(in[0])
			|| (ft_count_matriz(in) < 2)))
	{
		master->pid_child = fork();
		if (master->pid_child == 0)
		{
			ft_bin(master, in);
			exit(127);
		}
		else
		{
			signal(SIGINT, breaker);
			waitpid(master->pid_child, &master->status, 0);
			if (WIFEXITED(master->status))
				master->status = WEXITSTATUS(master->status);
			signal(SIGINT, sigint_handler);
		}
	}
	return (free_matriz(in), free(tmp), 0);
	
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
		if (!ft_len_redir(master, in))
			if (do_redirect(master, in) == -1)
				return (free(tmp), free_matriz(in), -1);
	}
	else
	{
		only_cmd(master, tmp, in);
	}
	//free_matriz(in);
	return (free(tmp), 0);
}

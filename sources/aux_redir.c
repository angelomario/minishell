/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux_redir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joandre <joandre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 20:36:52 by joandre           #+#    #+#             */
/*   Updated: 2024/12/11 01:45:05 by joandre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	filename = remove_if_even(filename, '\"');
	filename = remove_if_even(filename, '\'');
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
	name = remove_if_even(name, '\"');
	name = remove_if_even(name, '\'');
	if (append)
		fd = open(name, O_CREAT | O_WRONLY | O_APPEND, 0644);
	else
		fd = open(name, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd < 0)
	{
		return (perror("bash"), -1);
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux_redir2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joandre <joandre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 20:40:34 by joandre           #+#    #+#             */
/*   Updated: 2024/12/10 20:48:31 by joandre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	to_configure(t_master *master, char *param, int flag, int (*f)(char *, int))
{
	int		i;
	char	**mat;

	if (ft_strcmp(param, "\"\"") == 0)
	{
		print_default_fd(master,
			ft_strdup("bash: : No such file or directory\n"));
		return (-1);
	}
	format_imput(&param, 127);
	mat = ft_split(param, 127);
	i = 1;
	if (f(mat[0], flag) == -1)
		return (print_default_fd(master, ft_strjoin("bash: ", param)),
			print_default_fd(master,
				ft_strdup(": No such file or directory\n")), free_matriz(mat),
			-1);
	if (ft_count_matriz(mat) > 1)
	{
		while (mat[i])
			master->options = add_str(master->options, mat[i++]);
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
		{
			if (to_configure(master, in[i + 1], 0, redir_output) == -1)
				exit(127);
		}
		else if (ft_strcmp(in[i], ">>") == 0 && in[i + 1] != NULL)
		{
			if (to_configure(master, in[i + 1], 1, redir_output) == -1)
				exit(127);
		}
		else if (ft_strcmp(in[i], "<") == 0 && in[i + 1] != NULL)
		{
			if (to_configure(master, in[i + 1], 0, redir_input) == -1)
				exit(127);
		}
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

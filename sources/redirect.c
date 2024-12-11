/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joandre <joandre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 09:00:25 by aquissan          #+#    #+#             */
/*   Updated: 2024/12/11 13:07:20 by joandre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	do_redirect(t_master *master, char **in)
{
	char	*tmp;
	char	**command;

	master->output = (char *)malloc(sizeof(char) * 1);
	master->pid_child = fork();
	if (master->pid_child == 0)
	{
		free(master->output);
		do_heredoc(master, in);
		configure(master, in);
		if (is_redirect(in[0]) && ft_count_matriz(master->options) >= 1)
			ft_memset(in[0], ' ', ft_strlen(in[0]));
		format_imput(&in[0], 127);
		tmp = expanded(master, in[0]);
		command = concatmatrix(master, ft_split(tmp, 127), master->options);
		free(tmp);
		if (is_built_in(master, command) == 42 && (!is_redirect(in[0])
				|| ((ft_count_matriz(in) < 2))))
			ft_bin(master, command);
		exit(0);
	}
	else
		wait_sons(master);
	return (0);
}

int	is_redirect(char *str)
{
	if (str)
	{
		if ((ft_strcmp(str, ">") == 0) || (ft_strcmp(str, ">>") == 0)
			|| (ft_strcmp(str, "<") == 0) || (ft_strcmp(str, "<<") == 0))
		{
			return (1);
		}
	}
	return (0);
}

int	only_cmd(t_master *master, char *tmp, char **in)
{
	free_matriz(in);
	format_imput(&tmp, 127);
	ft_replace_c(tmp);
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
			master->status = WEXITSTATUS(master->status);
			signal(SIGINT, sigint_handler);
		}
	}
	return (free_matriz(in), 0);
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
		master->red = 1;
		if (!ft_len_redir(master, in))
			if (do_redirect(master, in) == -1)
				return (free(tmp), free_matriz(in), -1);
		return (free(tmp), free_matriz(in), 0);
	}
	else
	{
		only_cmd(master, tmp, in);
	}
	return (free(tmp), 0);
}

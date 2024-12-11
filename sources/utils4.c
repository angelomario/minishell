/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joandre <joandre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 00:12:25 by joandre           #+#    #+#             */
/*   Updated: 2024/12/11 01:48:58 by joandre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	do_pipe(t_master *master)
{
	rm_void(master->in);
	master->output = (char *)malloc(sizeof(char) * 1);
	master->pid_child = fork();
	if (master->pid_child == 0)
	{
		free(master->output);
		signal(SIGINT, exit_130);
		if ((ft_countchar(master->imput, 127) > 0)
			&& (ft_countchar(master->imput,
					127) >= ft_count_matriz(master->in)))
		{
			wait_prompt(master);
			if (!its_ok(master->imput))
				return (printf("Error\n"), 1);
		}
		return (ft_pipe(master), exit(0), 0);
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

int	validpipe(char *str)
{
	int		i;
	t_data	s;

	s.q_duo = 0;
	s.q_s = 0;
	i = -1;
	while (str && str[++i])
	{
		if (str[i] == '"' && !s.q_s)
			s.q_duo = !s.q_duo;
		else if (str[i] == '\'' && !s.q_duo)
			s.q_s = !s.q_s;
		else if (str[i] == '|' && !s.q_s && !s.q_duo)
		{
			i++;
			while (str[i] && (str[i] == ' ' || str[i] == '\t'))
				i++;
			if (str[i] == '|')
				return (0);
			else if (str[i] == '\0')
				return (1);
		}
	}
	return (1);
}

int	correct_pipes(char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		while (str[i] != '\0' && str[i] == ' ')
			i++;
		if (str[i] == '\0')
			return (1);
		if (str[i] == '|')
			return (0);
		else
			return (1);
	}
	return (1);
}

int	its_ok(char *str)
{
	int		i;
	t_data	data;

	i = 0;
	data.q_duo = 0;
	data.q_s = 0;
	while (str[i])
	{
		if (str[i] == '"' && !data.q_s)
			data.q_duo = !data.q_duo;
		else if (str[i] == '\'' && !data.q_duo)
			data.q_s = !data.q_s;
		i++;
	}
	if (data.q_s || data.q_duo)
		return (0);
	return (validpipe(str) && correct_pipes(str));
}

int	is_built_in(t_master *master, char **in)
{
	if (ft_strcmp(in[0], "export") == 0)
		return ((master->status = filter_export(master, in)));
	else if (ft_strcmp(in[0], "env") == 0)
	{
		if (ft_count_matriz(in) > 1)
		{
			print_default_fd(master, ft_strdup("env: ‘"));
			print_default_fd(master, ft_strdup(in[1]));
			print_default_fd(master,
				ft_strdup("’: No such file or directory\n"));
			return (master->status = 127);
		}
		return ((master->status = ft_env(master)), 0);
	}
	else if (ft_strcmp(in[0], "unset") == 0)
		return ((master->status = ft_unset(master, in)));
	else if (ft_strcmp(in[0], "cd") == 0)
		return ((master->status = ft_cd(master, in)));
	else if (ft_strcmp(in[0], "pwd") == 0)
		return ((master->status = ft_pwd(master, in)));
	else if (ft_strcmp(in[0], "echo") == 0)
		return ((master->status = ft_echo(in)));
	else if (ft_strcmp(in[0], "exit") == 0)
		return (ft_exit(master, in), 0);
	return (42);
}

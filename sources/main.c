/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joandre <joandre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 16:07:25 by joandre           #+#    #+#             */
/*   Updated: 2024/12/03 09:10:28 by joandre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t	g_sig = 0;

int	ft_countchar(char *str, char ch)
{
	int	i;

	i = 0;
	while (str && *str)
	{
		if (*str == ch)
			i++;
		str++;
	}
	return (i);
}

void	str_replace_del(char *str, char target, char to_replace)
{
	int	i;
	int	simple_asp;
	int	double_asp;

	simple_asp = 0;
	double_asp = 0;
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\'')
			simple_asp = !simple_asp;
		else if (str[i] == '"')
			double_asp = !double_asp;
		if (!simple_asp && !double_asp && str[i] == target)
		{
			str[i] = to_replace;
		}
		i++;
	}
}

void	rm_void(char **mat)
{
	int	i;
	int	j;

	i = -1;
	if (!mat || !*mat)
		return ;
	while (mat[++i])
	{
		j = 0;
		trim_whitespace(mat[i]);
		while (mat[i][j] == ' ' || mat[i][j] == '\t')
			j++;
		if (mat[i][j] == '\0')
		{
			while (mat[i + 1] != NULL)
			{
				mat[i] = mat[i + 1];
				i++;
			}
			mat[i] = NULL;
			free(mat[i + 1]);
		}
	}
}

int	currect_tmp(char *tmp)
{
	int	i;

	i = 0;
	if (ft_strcmp(tmp, "") == 0)
		return (0);
	while (tmp[i] && (tmp[i] == ' ' || tmp[i] == '\t'))
		i++;
	return (tmp[i] != '\0');
}

int	wait_prompt(t_master *master)
{
	char	*tmp;
	char	*new_input;

	tmp = readline("> ");
	if (!tmp)
		exit(42);
	if (correct_pipes(tmp) == 0 || validpipe(tmp) == 0)
		return (printf("Error\n"), free(tmp), free_matriz(master->in), exit(1),
			1);
	if (!currect_tmp(tmp))
		return (free(tmp), wait_prompt(master));
	add_history(tmp);
	str_replace_del(tmp, '|', 127);
	new_input = ft_strjoin(master->imput, tmp);
	free(master->imput);
	free(tmp);
	master->imput = new_input;
	free_matriz(master->in);
	master->in = ft_split(master->imput, 127);
	if (!validpipe(master->imput))
		return (1);
	if ((ft_countchar(master->imput, 127) > 0) && (ft_countchar(master->imput,
				127) >= ft_count_matriz(master->in)))
		wait_prompt(master);
	return (0);
}

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

int	ft_valid_args(char **in)
{
	int	i;

	i = 0;
	while (in[i])
	{
		if (its_ok(in[i]) == 0)
			return (0);
		i++;
	}
	return (1);
}

int	ft_find_way(t_master *master)
{
	if ((ft_count_matriz(master->in) >= 2 || ft_countchar(master->imput, 127))
		&& ft_valid_args(master->in))
	{
		do_pipe(master);
	}
	else
	{
		if (ft_redirect(master, master->imput) == -1)
			return (-1);
	}
	return (0);
}

int	ft_aux_main(t_master *master)
{
	if (!master->imput)
		return (printf("exit\n"), exit(0), 0);
	trim_whitespace(master->imput);
	if (ft_strcmp(master->imput, "") == 0)
		return (free(master->imput), 0);
	add_history(master->imput);
	if (its_ok(master->imput))
	{
		master->imput = expan_env(master, master->imput);
		ft_replace_c(master->imput);
		trim_whitespace(master->imput);
		str_replace_del(&master->imput[0], '|', 127);
		trim_whitespace(master->imput);
		master->in = ft_split(master->imput, 127);
		if (ft_find_way(master) == -1)
			return (0);
	}
	else
	{
		printf("Error\n");
		master->output = (char *)malloc(sizeof(char) * 1);
	}
	return (ft_clean_master(master), 0);
}

void	process_signal(t_master *master)
{
	if (g_sig == SIGINT)
		master->status = 130;
	if (master->status == 42)
	{
		print_default_fd(master, ft_strdup("exit\n"));
		exit(2);
	}
	g_sig = 42;
}

int	initialize_struture(t_master *master)
{
	master->history = NULL;
	master->output = NULL;
	master->in = NULL;
	master->status = 0;
	master->options[0] = NULL;
	master->stdin_fd = dup(STDIN_FILENO);
	master->stdout_fd = dup(STDOUT_FILENO);
	return (0);
}

int	main(int ac, char **av, char **env)
{
	t_master	*master;

	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
	master = (t_master *)malloc(sizeof(t_master));
	master->environ = ft_arrdup(env);
	master->options = (char **)malloc(sizeof(char *) * 1);
	initialize_struture(master);
	while (1 && av && ac)
	{
		master->imput = readline("minishell% ");
		process_signal(master);
		if (master->imput)
			trim_whitespace(master->imput);
		if (!((ft_strcmp(master->imput, "\"\"") == 0)
				|| (ft_strcmp(master->imput, "\'\'") == 0)))
			ft_aux_main(master);
		else
		{
			printf("command not found: \'\'\n");
			free(master->imput);
		}
		process_signal(master);
	}
	return (0);
}

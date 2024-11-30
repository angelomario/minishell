/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joandre <joandre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 16:07:25 by joandre           #+#    #+#             */
/*   Updated: 2024/11/29 09:10:52 by joandre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int	wait_prompt(t_master *master)
{
	char	*tmp;

	tmp = readline("\033[32m> \033[0m");
	if (!tmp)
	{
		exit(0);
	}
	master->imput = (char *)ft_realloc(master->imput, (ft_strlen(master->imput)
				+ ft_strlen(tmp) + 1));
	ft_strcat(master->imput, tmp);
	add_history(master->imput);
	free_matriz(master->in);
	master->in = ft_split(master->imput, '|');
	rm_void(master->in);
	if (!validpipe(master->imput))
		return (1);
	if ((ft_countchar(master->imput, '|') > 0) && (ft_countchar(master->imput,
				'|') >= ft_count_matriz(master->in)))
	{
		wait_prompt(master);
	}
	return (0);
}

int	do_pipe(t_master *master)
{
	rm_void(master->in);
	master->pid_child = fork();
	if (master->pid_child == 0)
	{
		signal(SIGINT, exit_130);
		if ((ft_countchar(master->imput, '|') > 0) && (ft_countchar(master->imput,
					'|') >= ft_count_matriz(master->in)))
		{
			if (wait_prompt(master))
			{
				return (printf("bash: syntax error near unexpected token `|'\n"),
					1);
			}
			if (!its_ok(master->imput))
				return (printf("Error\n"), 1);
		}
		ft_pipe(master);
		exit(0);
	}
	else
	{
		signal(SIGINT, SIG_IGN);
		waitpid(master->pid_child, &master->status, 0);
		signal(SIGINT, sigint_handler);
	}
	return (0);
}

int	validpipe(char *str)
{
	int	i;

	i = -1;
	while (str && str[++i])
	{
		if (str[i] == '|')
		{
			i++;
			while (str[i] == ' ' || str[i] == '\t')
				i++;
			if (str[i] == '|')
				return (0);
		}
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
	return (validpipe(str));
}

int	is_built_in(t_master *master, char **in)
{
	if (ft_strcmp(in[0], "export") == 0)
		return ((master->status = filter_export(master, in)));
	else if (ft_strcmp(in[0], "env") == 0)
		return ((master->status = ft_env(master)));
	else if (ft_strcmp(in[0], "unset") == 0)
		return ((master->status = ft_unset(master, in)));
	else if (ft_strcmp(in[0], "cd") == 0)
		return ((master->status = ft_cd(master, in)));
	else if (ft_strcmp(in[0], "pwd") == 0)
		return ((master->status = ft_pwd(master, in)));
	else if (ft_strcmp(in[0], "echo") == 0)
		return ((master->status = ft_echo(in)));
	else if (ft_strcmp(in[0], "exit") == 0)
		return (ft_exit(master), 0);
	return (42);
}

int	only_comands(t_master *master, char *input)
{
	int		built_in;
	char	*tmp;

	free_matriz(master->in);
	format_imput(&input, 127);
	tmp = expanded(master, input);
	master->in = ft_split(tmp, 127);
	free(tmp);
	built_in = 42;
	if (master->in && master->in[0])
	{
		built_in = is_built_in(master, master->in);
		if (built_in == 42)
		{
			if ((master->pid_child = fork()) == 0)
				ft_bin(master, master->in);
			else
				waitpid(master->pid_child, &master->status, 0);
		}
	}
	printf("%d\n", master->status);
	return (0);
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

int	main(int ac, char **av, char **env)
{
	t_master	*master;

	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
	// pid_address = (int *)malloc(sizeof(int) * 1);
	master = (t_master *)malloc(sizeof(t_master));
	master->environ = ft_arrdup(env);
	env = master->environ;
	master->status = 0;
	// pid_address = &master->pid_child;
	master->stdin_fd = dup(STDIN_FILENO);
	master->stdout_fd = dup(STDOUT_FILENO);
	while (1 && av && ac)
	{
		g_func(0);
		master->imput = readline("minishell% ");
		if (!master->imput)
		{
			kill_proccess(master->pid_child, NULL, master->stdout_fd);
			printf("exit\n");
			exit(0);
		}
		master->history = ft_strdup(master->imput);
		trim_whitespace(master->imput);
		if (ft_strcmp(master->imput, "") == 0)
			continue ;
		if (its_ok(master->imput))
		{
			master->in = ft_split(master->imput, '|');
			if ((ft_count_matriz(master->in) >= 2 || ft_countchar(master->imput,
					'|')) && ft_valid_args(master->in))
				do_pipe(master);
			else
			{
				if (ft_redirect(master, master->imput) == -1)
					break ;
			}
		}
		else
			printf("Error\n");
		// free_matriz(master->in);
		add_history(master->history);
	}
	return (free(master->imput), 0);
}

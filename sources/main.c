/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joandre <joandre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 16:07:25 by joandre           #+#    #+#             */
/*   Updated: 2024/12/11 13:04:29 by joandre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t	g_sig = 0;

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
		if (!master->imput)
			return (free(master->imput), 0);
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
	master->red = 0;
	master->pid_child = 0;
	master->options[0] = NULL;
	master->stdin_fd = dup(STDIN_FILENO);
	master->stdout_fd = dup(STDOUT_FILENO);
	signal(SIGQUIT, SIG_IGN);
	return (0);
}

int	main(int ac, char **av, char **env)
{
	t_master	*master;

	signal(SIGINT, sigint_handler);
	master = (t_master *)malloc(sizeof(t_master));
	master->environ = ft_arrdup(env);
	master->options = (char **)malloc(sizeof(char *) * 1);
	initialize_struture(master);
	while (1 && av && ac)
	{
		master->imput = readline("Cortana> ");
		process_signal(master);
		if (master->imput)
			trim_whitespace(master->imput);
		if (!((ft_strcmp(master->imput, "\"\"") == 0)
				|| (ft_strcmp(master->imput, "\'\'") == 0)))
			ft_aux_main(master);
		else
		{
			add_history(master->imput);
			printf("command not found: \'\'\n");
			free(master->imput);
		}
		process_signal(master);
	}
	return (0);
}

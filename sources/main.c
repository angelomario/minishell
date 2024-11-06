/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joandre <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 16:07:25 by joandre           #+#    #+#             */
/*   Updated: 2024/10/23 06:13:25 by joandre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **env)
{
	t_master	*master;

	(void)ac;
	(void)av;
	master = (t_master *)malloc(sizeof(t_master));
	master->environ = ft_arrdup(env);
	env = master->environ;
	while (1)
	{
		master->imput = readline("\033[32mminishell% \033[0m");
		if (!master->imput)
			break ;
		master->in = ft_split(master->imput, ' ');
		if (ft_strcmp(master->in[0], "exit") == 0)
			ft_exit(master);
		if (ft_strcmp(master->in[0], "unset") == 0)
			ft_unset(master, &master->in[1]);
		else if (ft_strcmp(master->in[0], "env") == 0)
			ft_env(master);
		else if (ft_strcmp(master->in[0], "export") == 0)
			filter_export(master);
		else if (master->in && master->in[0])
		{
			if (fork() == 0)
				ft_bin(master->in);
			else
				wait(NULL);
		}
		add_history(master->imput);
	}
	free(master->imput);
}

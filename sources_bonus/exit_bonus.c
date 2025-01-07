/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquissan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 14:58:42 by aquissan          #+#    #+#             */
/*   Updated: 2024/10/29 14:58:58 by aquissan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell_bonus.h"

int	str_true(char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		if ((str[0] == '-' || str[0] == '+') && i == 0)
			i++;
		else if (!ft_isdigit(str[i]))
			return (0);
		else
			i++;
	}
	return (1);
}

int	quit(t_master *master, int status, char **in)
{
	if (status < 0)
		status += 256;
	free_matriz(in);
	print_default_fd(master, ft_strdup("exit\n"));
	free_matriz(master->options);
	free_matriz(master->in);
	free_matriz(master->environ);
	free(master->history);
	free(master->imput);
	exit(status);
	return (0);
}

int	error_non_numeric(t_master *master, int num, char **in)
{
	master->status = 2;
	free_matriz(master->options);
	free_matriz(master->in);
	free_matriz(master->environ);
	free(master->history);
	free(master->imput);
	return (print_default_fd(master, ft_strjoin("exit\n", "bash: exit: ")),
		print_default_fd(master, ft_strdup(in[1])), print_default_fd(master,
			ft_strdup(": numeric argument required\n")), free_matriz(in),
		exit(num), 0);
}

// This function simplily exit of the actual proccess
int	ft_exit(t_master *master, char **in, char *tmp)
{
	if (master->red)
		return (free(tmp), exit(24), 0);
	if (ft_count_matriz(in) == 2)
	{
		if (str_true(in[1]))
			return (free(tmp), quit(master, ft_atoi(in[1]), in), 0);
		else
			return (free(tmp), error_non_numeric(master, 2, in));
	}
	else if (ft_count_matriz(in) == 1)
		return (free(tmp), quit(master, 0, in), 0);
	if (str_true(in[1]) == 0)
	{
		return (free(tmp), print_default_fd(master, ft_strjoin("exit\n",
					"bash: exit: ")), print_default_fd(master,
				ft_strdup(in[1])), print_default_fd(master,
				ft_strdup(": numeric argument required\n")), exit(2), 0);
	}
	else
	{
		master->status = 1;
		return (print_default_fd(master, ft_strjoin("exit\n",
					"bash: exit: too many arguments\n")), 1);
	}
}

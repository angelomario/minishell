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

#include "minishell.h"

int	valide_exit(char *str)
{
	int	i;

	i = 0;
	if (ft_atoi(str) == 0)
		return (1);
	while (str && str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	str_true(char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		if (!ft_isdigit(str[i]))
			return (1);
		i++;
	}
	return (0);
}

int	array_exit(char **in)
{
	int	i;

	i = 0;
	if (!in || !(*in))
		return (0);
	while (in && in[i])
	{
		if (ft_count_matriz(in) >= 2)
		{
			if (str_true(in[0]))
				return (1);
			else
				return (0);
		}
		if (!valide_exit(in[i]))
		{
			return (0);
		}
		i++;
	}
	return (1);
}

// This function simplily exit of the actual proccess
int	ft_exit(t_master *master, char **in)
{
	if (ft_count_matriz(in) <= 2)
	{
		if (ft_count_matriz(in) == 2 && valide_exit(in[1]))
		{
			free_matriz(master->in);
			free(master->imput);
			if (str_true(in[1]) == 0)
				exit(ft_atoi(in[1]));
			else
				exit(0);
		}
		else if (ft_count_matriz(in) == 1)
		{
			free_matriz(master->in);
			free(master->imput);
			exit(0);
		}
	}
	else if (array_exit(&in[1]))
		return (print_default_fd(master, ft_strjoin("exit\n",
					"bash: exit: too many arguments\n")), exit(1), 0);
	return (print_default_fd(master, ft_strjoin("exit\n",
				"bash: exit: too many arguments\n")));
}

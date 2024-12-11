/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joandre <joandre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 08:38:29 by aquissan          #+#    #+#             */
/*   Updated: 2024/12/11 08:33:56 by joandre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Here is command unset behavior
// This command removes enviroment variable by actual running proccess

int	compare(char **next_env)
{
	free(*next_env);
	while (*(next_env + 1) != NULL)
	{
		*next_env = *(next_env + 1);
		next_env++;
	}
	*next_env = NULL;
	return (0);
}

int	ft_unset(t_master *master, char **str)
{
	char	**env;
	char	**next_env;

	while (*str != NULL)
	{
		env = master->environ;
		if (*str == NULL || ft_strchr(*str, '=') != NULL)
			return (-1);
		while (*env != NULL)
		{
			if (ft_strncmp(*(env), *str, ft_strlen(*str)) == 0
				&& ((*env)[ft_strlen(*str)] == '='
				|| ft_strlen(*env) == ft_strlen(*str)))
			{
				next_env = env;
				compare(next_env);
			}
			env++;
		}
		str++;
	}
	return (!(*str == NULL));
}

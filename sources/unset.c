/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquissan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 08:38:29 by aquissan          #+#    #+#             */
/*   Updated: 2024/10/30 08:40:07 by aquissan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Here is command unset behavior
// This command removes enviroment variable by actual running proccess

int	ft_unset(t_master *master, char **str)
{
	char	**env;
	char	**next_env;

	while (*str != NULL)
	{
		env = master->environ;
		if (*str == NULL || strchr(*str, '=') != NULL)
			return (-1);
		while (*env != NULL)
		{
			if (ft_strncmp(*(env), *str, ft_strlen(*str)) == 0 && (*env)[ft_strlen(*str)] == '=')
			{
				next_env = env;
				while (*(next_env + 1) != NULL)
				{
					*next_env = *(next_env + 1);
					next_env++;
				}
				*next_env = NULL;
				free(*(next_env + 1));
			}
			env++;
		}
		str++;
	}
	return (!(*str == NULL));
}

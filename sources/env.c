/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joandre <joandre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 10:48:00 by aquissan          #+#    #+#             */
/*   Updated: 2024/12/06 07:31:46 by joandre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// This is the funcion that replicates the behavior of the env function
// This function shows all enviroment variables available in the actual proccess
int	ft_env(t_master *master)
{
	char	**env;
	char	*tmp;

	env = master->environ;
	if (env && *env)
	{
		while (*env)
		{
			tmp = ft_strrchr(*env, '=');
			if (tmp != NULL)
			{
				if (ft_strcmp(tmp, "=''") != 0)
					printf("%s\n", *env);
			}
			env++;
		}
		return (0);
	}
	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquissan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 10:48:00 by aquissan          #+#    #+#             */
/*   Updated: 2024/10/30 10:48:42 by aquissan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// This is the funcion that replicates the behavior of the env function
// This function shows all enviroment variables available in the actual proccess

int	ft_env(t_master *master)
{
	char	**get;

	if (master->in[0] != NULL && (strcmp(master->in[0], "env") == 0))
	{
		get = master->environ;
		while (*get)
		{
			if (ft_strcmp(ft_strrchr(*get, '='), "=''") != 0)
				printf("%s\n", *get);
			get++;
		}
		return (0);
	}
	return (0);
}

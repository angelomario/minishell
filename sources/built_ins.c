/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joandre <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 16:43:19 by joandre           #+#    #+#             */
/*   Updated: 2024/10/22 19:59:31 by joandre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_builting(char **args)
{
	int	i;

	i = 0;
	if (ft_strcmp(args[i], "pwd") == 0)
	{
		if (ft_strcmp(args[i], "pwd") == 0 && args[i + 1])
			printf("pwd: too many arguments\n");
		else
			printf("%s\n", getcwd(NULL, 0));
		return (1);
	}
	else if (ft_strcmp(args[i], "cd") == 0)
	{
		i++;
		if (args[i] == NULL)
			chdir(getenv("HOME"));
		else if (args[i])
		{
			if (chdir(args[i]) == -1)
				printf("cd: no such file or directory: %s\n", args[i]);
		}
		return (1);
	}
	return (0);
}

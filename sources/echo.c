/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquissan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 08:25:32 by aquissan          #+#    #+#             */
/*   Updated: 2024/10/30 10:50:32 by aquissan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// This is the function that repicates the behavior of the echo function
// It's shows the message by terminal (CLI)

int	ft_echo(char **av)
{
	int	i;

	i = 1;
	
	if ( !av[1] && ft_strcmp(av[0], "echo") == 0)
	{
		printf("\n");
		return (1);
	}
	if (ft_strcmp(av[0], "echo") == 0)
	{
		while (av[i])
		{
			while(ft_strcmp(av[i], "-n") == 0)
				i++;
			printf("%s", av[i]);
			if (av[i + 1])
				printf(" ");
			i++;
		}
		if (ft_strcmp(av[1], "-n") == 0)
		{
			printf("%%");
		}
			printf("\n");
		return (1);
	}
	return (0);
}

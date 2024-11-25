/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquissan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 08:47:46 by aquissan          #+#    #+#             */
/*   Updated: 2024/11/19 08:48:49 by aquissan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pwd(t_master *master, char **in)
{
	(void)master;
	if (in && *in)
	{
		if (ft_strcmp(in[0], "pwd") == 0)
		{
			if (ft_count_matriz(in) >= 2)
				printf("pwd: too many arguments\n");
			else
				printf("%s\n", getcwd(NULL, 0));
			return (1);
		}
	}
	return (0);
}

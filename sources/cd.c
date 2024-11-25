/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquissan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 08:54:42 by aquissan          #+#    #+#             */
/*   Updated: 2024/11/19 08:55:39 by aquissan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_cd(t_master *master, char **in)
{
	(void)master;
	if (ft_strcmp(*in, "cd") == 0)
	{
		in++;
		if (*in == NULL)
			chdir(getenv("HOME"));
		else if (*in)
		{
			if (chdir(*in) == -1)
				printf("cd: no such file or directory: %s\n", *in);
		}
		return (1);
	}
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joandre <joandre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 00:34:41 by joandre           #+#    #+#             */
/*   Updated: 2024/12/11 00:34:46 by joandre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_pwd(t_master *master, char **in)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	(void)master;
	if (ft_strcmp(in[0], "pwd") == 0)
	{
		printf("%s\n", cwd);
		free(cwd);
		return (0);
	}
	free(cwd);
	return (0);
}

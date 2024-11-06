/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   teste2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joandre <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 04:58:30 by joandre           #+#    #+#             */
/*   Updated: 2024/10/23 05:52:37 by joandre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_very_and_bar(char *cmd)
{
	char	*w;

	w = malloc(sizeof(char) * ft_strlen(cmd) + 2);
	w = ft_strcpy(w, cmd);
	w = ft_strcat(cmd, "/");
	return (w);
}

void	ft_current_dir(char **av)
{
	char	*cmd;
	char	*path;
	int		len;
	int		cwd;

	cmd = av[0];
	cwd = ft_strlen(getcwd(NULL, 0));
	len = ft_strlen(cmd);
	path = malloc(sizeof(char) * (cwd + len) + 3);
	if (!path)
	{
		free(path);
		return ;
	}
	ft_strlcpy(path, getcwd(NULL, 0), cwd + 1);
	ft_strcat(path, "/");
	ft_strcat(path, cmd);
	if (execv(path, av) != 0)
	{
		printf("command not found: %s\n", av[0]);
		free(path);
		return ;
	}
}

int	ft_bin_(char **av, char *path)
{
	char	*cmd_new;

	cmd_new = malloc(sizeof(char) * ft_strlen(av[0]) + ft_strlen(path) + 1);
	cmd_new = ft_strcpy(cmd_new, path);
	cmd_new = ft_strcat(cmd_new, ft_strstr(cmd_new, av[0]));
	if(execv(cmd_new, av) != 0)
	{
		free(path);
		free(cmd_new);
		return (-1);
	}
	return (0);
}

void	ft_bin(char **av)
{
	char	*path;
	char	**paths;
	int		i;

	i = 1;
	path = getenv("PATH");
	paths = ft_split(path, ':');
	while (paths[i])
	{
		path = ft_very_and_bar(paths[i]);

		if (ft_bin_(av, path) != 0)
			i++;
	}
	ft_current_dir(av);
}

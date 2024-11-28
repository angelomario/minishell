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

// char	*ft_very_and_bar(char *cmd)
// {
//     char	*w;
//     size_t len = ft_strlen(cmd);

//     w = malloc(len + 2);  // Aloca espaço suficiente para cmd + '/'
//     if (!w) {
//         return (NULL);  // Verifica falha de alocação
//     }
//     ft_strcpy(w, cmd);  // Copia cmd para w
//     ft_strcat(w, "/");  // Adiciona '/' no final
//     return (w);
// }

// void	ft_current_dir(char **av)
// {
// 	char	*cmd;
// 	char	*path;
// 	int		len;
// 	int		cwd;

// 	cmd = av[0];
// 	cwd = ft_strlen(getcwd(NULL, 0));
// 	len = ft_strlen(cmd);
// 	path = malloc(sizeof(char) * (cwd + len) + 3);
// 	if (!path)
// 	{
// 		free(path);
// 		return ;
// 	}
// 	ft_strlcpy(path, getcwd(NULL, 0), cwd + 1);
// 	ft_strcat(path, "/");
// 	ft_strcat(path, cmd);
// 	if (execv(path, av) != 0)
// 	{
// 		printf("command not found: %s\n", av[0]);
// 		free(path);
// 		return ;
// 	}
// }

// int	ft_bin_(char **av, char *path)
// {
// 	char	*cmd_new;

// 	cmd_new = malloc(sizeof(char) * ft_strlen(av[0]) + ft_strlen(path) + 1);
// 	cmd_new = ft_strcpy(cmd_new, path);
// 	cmd_new = ft_strcat(cmd_new, ft_strstr(cmd_new, av[0]));
// 	if(execv(cmd_new, av) != 0)
// 	{
// 		free(path);
// 		free(cmd_new);
// 		return (-1);
// 	}
// 	return (0);
// }

// void	ft_bin(char **av)
// {
// 	char	*path;
// 	char	**paths;
// 	int		i;

// 	i = 1;
// 	path = getenv("PATH");
// 	paths = ft_split(path, ':');
// 	while (paths[i])
// 	{
// 		path = ft_very_and_bar(paths[i]);

// 		if (ft_bin_(av, path) != 0)
// 			i++;
// 	}
// 	ft_current_dir(av);
// }

char	*ft_very_and_bar(char *cmd)
{
	char	*w;
	size_t	len;

	len = ft_strlen(cmd);
	w = malloc(len + 2);
	if (!w)
	{
		return (NULL);
	}
	ft_strcpy(w, cmd);
	ft_strcat(w, "/");
	return (w);
}

void	ft_current_dir(t_master *master, char **av)
{
	char	*cmd;
	char	*path;
	char	*get;
	int		len;
	int		cwd;

	get = getcwd(NULL, 0);
	cmd = av[0];
	cwd = ft_strlen(get);
	len = ft_strlen(cmd);
	path = malloc(cwd + len + 2);
	ft_strlcpy(path, get, cwd + 1);
	ft_strcat(path, "/");
	ft_strcat(path, cmd);
	if (execv(path, av) == -1)
	{
		print_default_fd(master, ft_strjoin("command not found: ", av[0]));
		printf("\n");
		free(path);
		free(get);
		return ;
	}
}

int	built_in_path(char *cmd_new)
{
	int	len_path;

	len_path = ft_strlen(cmd_new);
	if (ft_strcmp(&(cmd_new[len_path - ft_strlen("env")]), "env") == 0)
		return (1);
	if (ft_strcmp(&(cmd_new[len_path - ft_strlen("export")]), "export") == 0)
		return (1);
	if (ft_strcmp(&(cmd_new[len_path - ft_strlen("echo")]), "echo") == 0)
		return (1);
	if (ft_strcmp(&(cmd_new[len_path - ft_strlen("cd")]), "cd") == 0)
		return (1);
	if (ft_strcmp(&(cmd_new[len_path - ft_strlen("pwd")]), "pwd") == 0)
		return (1);
	if (ft_strcmp(&(cmd_new[len_path - ft_strlen("unset")]), "unset") == 0)
		return (1);
	return (0);
}

int	ft_bin_(char **av, char *path)
{
	char	*cmd_new;

	cmd_new = malloc(ft_strlen(path) + ft_strlen(av[0]) + 2);
	if (!cmd_new)
		return (-1);
	ft_strcpy(cmd_new, path);
	ft_strcat(cmd_new, ft_strstr(cmd_new, av[0]));
	if (built_in_path(cmd_new))
	{
		free(cmd_new);
		return (-1);
	}
	if (execv(cmd_new, av) != 0)
	{
		free(cmd_new);
		return (-1);
	}
	free(cmd_new);
	return (0);
}

void	ft_bin(t_master *master, char **av)
{
	char	*path;
	char	**paths;
	int		i;

	i = 0;
	path = ft_getenv(master->environ, "PATH");
	paths = ft_split(path, ':');
	while (paths[i])
	{
		path = ft_very_and_bar(paths[i]);
		if (!path)
		{
			i++;
			continue ;
		}
		if (ft_bin_(av, path) != 0)
		{
			free(path);
			i++;
		}
		else
			break ;
	}
	free_matriz(paths);
	ft_current_dir(master, av);
}

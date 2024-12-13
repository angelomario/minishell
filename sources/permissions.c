/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   permissions.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joandre <joandre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 16:12:18 by aquissan          #+#    #+#             */
/*   Updated: 2024/12/13 07:10:19 by joandre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_permission(t_master *master, char *str)
{
	struct stat	file;

	if (str)
		trim_whitespace(str);
	if (stat(str, &file) != -1)
	{
		if (S_ISDIR(file.st_mode))
		{
			return (print_default_fd(master, ft_strjoin("bash: ", str)),
				print_default_fd(master, ft_strdup(": Is a directory\n")), 1);
		}
	}
	if ((access(str, F_OK) == 0) && (access(str, X_OK) != 0 || access(str,
				R_OK) != 0 || access(str, W_OK) != 0))
	{
		print_default_fd(master, ft_strjoin("bash: Permission denied: ", str));
		printf("\n");
		return (1);
	}
	print_default_fd(master, ft_strjoin("bash: ", str));
	print_default_fd(master, ft_strdup(": No such file or directory\n"));
	return (1);
}

int	ft_is_directory(t_master *master, char *str)
{
	struct stat	file;

	if (stat(str, &file) != -1)
	{
		trim_whitespace(str);
		if (S_ISDIR(file.st_mode) == 0)
		{
			master->status = 1;
			return (print_default_fd(master, ft_strjoin("bash: ", str)),
				print_default_fd(master, ft_strdup(": Is no a directory\n")),
				1);
		}
	}
	return (0);
}

int	check_commander(t_master *master, char *str)
{
	struct stat	file;

	if (str)
		trim_whitespace(str);
	if (stat(str, &file) != -1)
	{
		if (S_ISDIR(file.st_mode) && ft_strncmp(str, "./", 2) == 0)
		{
			print_default_fd(master, ft_strjoin("bash: ", str));
			print_default_fd(master, ft_strdup(": is a directory\n"));
			exit(126);
		}
	}
	if ((access(str, F_OK) == 0) && (access(str, X_OK) != 0 || access(str,
				R_OK) != 0 || access(str, W_OK) != 0) && ft_strncmp(str, "./",
			2) == 0)
	{
		print_default_fd(master, ft_strjoin("bash: Permission denied: ", str));
		printf("\n");
		exit(126);
	}
	print_default_fd(master, ft_strjoin("bash: ", str));
	print_default_fd(master, ft_strdup(": command not found\n"));
	exit(127);
	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   permissions.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquissan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 16:12:18 by aquissan          #+#    #+#             */
/*   Updated: 2024/12/12 16:12:55 by aquissan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_permission(t_master *master, char *str)
{
	struct stat	file;

	if (str)
		trim_whitespace(str);
	printf("%c\n", str[0]);
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

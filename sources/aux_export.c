/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joandre <joandre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 17:34:01 by aquissan          #+#    #+#             */
/*   Updated: 2024/12/11 00:51:59 by joandre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_name(char *str)
{
	int		i;
	int		j;
	char	*name;

	i = 0;
	if (str == NULL || !str[0])
		return (NULL);
	while (str[i] && str[i] != '=')
		i++;
	if (str[i] == '=')
		i++;
	j = -1;
	name = (char *)malloc(sizeof(char) * i + 2);
	while (++j < i)
		name[j] = str[j];
	name[j] = '\0';
	return (name);
}

int	list_dirs(void)
{
	struct dirent	*entry;
	struct stat		info;
	DIR				*dir;

	dir = opendir(".");
	if (!dir)
		return (1);
	entry = readdir(dir);
	while (entry != NULL)
	{
		if (ft_strcmp(entry->d_name, ".") != 0 && ft_strcmp(entry->d_name,
				"..") != 0)
		{
			if (stat(entry->d_name, &info) == 0 && S_ISDIR(info.st_mode))
			{
				printf("bash: export: `%s': not a valid identifier\n",
					entry->d_name);
			}
		}
		entry = readdir(dir);
	}
	closedir(dir);
	return (1);
}

int	check_identifiers(t_master *master, char *str)
{
	int	i;

	i = 0;
	if (str && !ft_isalpha(str[0]))
	{
		return (print_default_fd(master, ft_strdup("bash: export: `")),
			print_default_fd(master, ft_strdup(str)), print_default_fd(master,
				ft_strdup("': not a valid identifier\n")), 1);
	}
	while (str != NULL && str[i])
	{
		if (str[i] == '=')
			return (0);
		if (ft_isalnum(str[i]) || str[i] == '_')
			i++;
		else
		{
			return (print_default_fd(master, ft_strdup("bash: export: `")),
				print_default_fd(master, ft_strdup(str)),
				print_default_fd(master,
					ft_strdup("': not a valid identifier\n")), 1);
		}
	}
	return (0);
}

int	do_export(t_master *master, char *in)
{
	int		i;
	char	*name;

	i = 0;
	in = remove_if_even(in, '\"');
	name = get_name(in);
	if ((ft_strchr(in, '=')) == NULL)
		i = ft_export(master, name, NULL);
	else
	{
		if (ft_strlen(ft_strchr(in, '=')) <= 1)
			i = ft_export(master, name, NULL);
		else
			i = ft_export(master, name, &(ft_strchr(in, '=')[1]));
	}
	return (free(name), i);
}

int	filter_export(t_master *master, char **in)
{
	int	i;

	i = 1;
	if (ft_count_matriz(in) <= 1)
		ft_export(master, NULL, NULL);
	else
	{
		while (in && in[i] != NULL)
		{
			if (check_identifiers(master, in[i]))
				i++;
			else
				do_export(master, in[i++]);
		}
	}
	return (0);
}

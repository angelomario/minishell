/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joandre <joandre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 14:06:21 by aquissan          #+#    #+#             */
/*   Updated: 2024/12/11 01:28:54 by joandre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// This is the function
// that reproduces the behavior of the default export function
// This function set any variable with your
// value available in any child proccess

void	ft_putstrenv(char *str, int asp)
{
	int	i;

	i = 0;
	while (str[i])
	{
		write(1, &str[i], 1);
		if (((str[i] == '=') || (str[i + 1] == '\0' && ft_strchr(str, '=')))
			&& asp && ft_strchr(str, '\"') == NULL)
			write(1, "\"", 1);
		i++;
	}
}

int	showenv(char **env)
{
	int		i;
	char	**tmp;

	i = -1;
	tmp = ft_arrdup(env);
	ft_arrtab(tmp);
	if (!env || !(*env))
		return (-1);
	while (tmp[++i] != NULL)
	{
		ft_putstrenv("declare -x ", 0);
		ft_putstrenv(tmp[i], 1);
		ft_putstrenv("\n", 0);
	}
	free_matriz(tmp);
	return (0);
}

int	has_variable(char **environ, char *new_var, char *name)
{
	int	env_count;

	env_count = 0;
	while (environ[env_count] != NULL)
	{
		if (ft_strncmp(environ[env_count], name, ft_strlen(new_var)) == 0
			&& environ[env_count][ft_strlen(new_var)] == '=')
		{
			free(environ[env_count]);
			environ[env_count] = new_var;
			return (0);
		}
		env_count++;
	}
	(void)environ;
	return (env_count);
}

char	*ft_joincheck(char *name, char *value)
{
	char	*new_var;

	new_var = (char *)malloc(sizeof(char) * (ft_strlen(name) + ft_strlen(value)
				+ 4));
	if (!new_var || !name)
		return (NULL);
	ft_memset(new_var, 0, ft_strlen(name) + ft_strlen(value) + 2);
	ft_strcat(new_var, name);
	if ((value == NULL) && (ft_strchr(name, '=') == NULL))
		return (new_var);
	if (name != NULL && value != NULL)
		ft_strcat(new_var, value);
	else
		ft_strcat(new_var, "\"\"");
	return (new_var);
}

int	ft_export(t_master *master, char *name, char *value)
{
	char	*new_var;
	char	**new_environ;
	int		env_count;

	env_count = 0;
	if (name == NULL && value == NULL)
		return (showenv(master->environ));
	if (replace_env(master, name, value) == 0)
		return (0);
	new_var = ft_joincheck(name, value);
	env_count = has_variable(master->environ, new_var, name);
	if (!(env_count))
		return (0);
	new_environ = (char **)ft_realloc(master->environ, (sizeof(char **)
				* ft_count_matriz(master->environ)), (env_count + 2)
			* sizeof(char *));
	if (new_environ == NULL)
		return (free(new_var), (-1));
	master->environ = new_environ;
	master->environ[env_count] = new_var;
	master->environ[env_count + 1] = NULL;
	return (0);
}

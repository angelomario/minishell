/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joandre <joandre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 01:12:35 by joandre           #+#    #+#             */
/*   Updated: 2024/12/11 01:16:53 by joandre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	print_default_fd(t_master *master, char *msg)
{
	if (dup2(master->stdout_fd, STDOUT_FILENO) == -1)
	{
		perror("Dup2");
		return (free(msg), -1);
	}
	printf("%s", msg);
	return (free(msg), 0);
}

char	*ft_getenv(char **env, char *name)
{
	int	len;
	int	i;

	i = 0;
	len = ft_strlen(name);
	while (env && env[i])
	{
		if ((ft_strncmp(env[i], name, ft_strlen(name)) == 0)
			&& env[i][len] == '=')
		{
			return (&env[i][len + 1]);
		}
		i++;
	}
	return (NULL);
}

void	ft_setenv(t_master *master, char *name_var, char *new_value)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(name_var);
	while (master->environ[i])
	{
		if (ft_strncmp(master->environ[i], name_var, len) == 0)
		{
			free(master->environ[i]);
			master->environ[i] = ft_strdup(new_value);
			return ;
		}
		i++;
	}
}

int	ft_cd_(t_master *master, char *cwd, char *cmd, char **in)
{
	t_data	data;
	int		i;

	i = 0;
	data.oldpwd = ft_strjoin(cmd, cwd);
	if (data.oldpwd)
		ft_setenv(master, "OLDPWD=", data.oldpwd);
	free(data.oldpwd);
	i++;
	if (in[i] == NULL)
		chdir(ft_getenv(master->environ, "HOME"));
	else if (in[i])
	{
		if (chdir(in[i]) == -1)
		{
			print_default_fd(master,
				ft_strjoin("cd: no such file or directory: ", in[i]));
			printf("\n");
		}
	}
	data.dir = getcwd(NULL, 0);
	data.pwd = ft_strjoin("PWD=", data.dir);
	return (ft_setenv(master, "PWD=", data.pwd), free(cwd), free(cmd),
		free(data.pwd), free(data.dir), 0);
}

int	ft_cd(t_master *master, char **in)
{
	int	i;

	i = 0;
	if (ft_strcmp(in[i], "cd") == 0)
	{
		if (!in[1])
		{
			print_default_fd(master, ft_strdup("cd: HOME not set\n"));
			return (127);
		}
		if (ft_cd_(master, getcwd(NULL, 0), ft_strdup("OLDPWD="), in) == -1)
		{
			master->status = 127;
			return (1);
		}
		return (0);
	}
	return (1);
}

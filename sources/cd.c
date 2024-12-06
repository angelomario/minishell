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
	int		i;
	char	*oldpwd;
	char	*pwd;
	char	*dir;
	char	*error_msg;

	i = 0;
	if (!cwd)
		return (free(cmd), 0);
	oldpwd = ft_strjoin(cmd, cwd);
	if (oldpwd)
		ft_setenv(master, "OLDPWD=", oldpwd);
	free(oldpwd);
	i++;
	if (in[i] == NULL)
		chdir(ft_getenv(master->environ, "HOME"));
	else if (in[i])
	{
		if (chdir(in[i]) == -1)
		{
			error_msg = ft_strjoin("cd: no such file or directory: ", in[i]);
			if (error_msg)
			{
				print_default_fd(master, error_msg);
				free(error_msg);
			}
			printf("\n");
		}
	}
	dir = getcwd(NULL, 0);
	pwd = ft_strjoin("PWD=", dir);
	return (ft_setenv(master, "PWD=", pwd), free(cwd), free(cmd), free(pwd), free(dir), 0);
}

int	ft_cd(t_master *master, char **in)
{
	int	i;

	i = 0;
	if (ft_strcmp(in[i], "cd") == 0)
	{
		ft_cd_(master, getcwd(NULL, 0), ft_strdup("OLDPWD="), in);
		return (1);
	}
	return (0);
}

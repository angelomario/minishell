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
			if (ft_strlen(ft_strchr(env[i], '=')) > 1)
			{
				return (ft_strdup(&((ft_strchr(env[i], '='))[1])));
			}
			else
				return (NULL);
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
			master->environ[i] = new_value;
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

	i = 0;
	if (!(cwd))
		return (free((cmd)), 0);
	oldpwd = ft_strjoin(cmd, cwd);
	ft_setenv(master, "OLDPWD=", oldpwd);
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
	dir = getcwd(NULL, 0);
	pwd = ft_strjoin("PWD=", dir);
	return (ft_setenv(master, "PWD=", pwd), free(cwd), free(cmd), free(dir), 0);
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

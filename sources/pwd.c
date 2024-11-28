#include "../includes/minishell.h"

int	ft_pwd(t_master *master, char **in)
{
	char *cwd;

	cwd = getcwd(NULL, 0);
	if (ft_strcmp(in[0], "pwd") == 0)
	{
		if (ft_strcmp(in[0], "pwd") == 0 && in[1])
		{
			print_default_fd(master, ft_strdup("pwd: too many arguments"));
			printf("\n");
		}
		else
		{
			printf("%s\n", cwd);
			free(cwd);
			return (1);
		}
	}
	free(cwd);
	return (0);
}

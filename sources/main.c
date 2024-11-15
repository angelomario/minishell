/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joandre <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 16:07:25 by joandre           #+#    #+#             */
/*   Updated: 2024/10/23 06:13:25 by joandre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int	main(int ac, char **av, char **env)
// {
// 	t_master	*master;

// 	(void)ac;
// 	(void)av;
// 	master = (t_master *)malloc(sizeof(t_master));
// 	master->environ = ft_arrdup(env);
// 	env = master->environ;
// 	while (1)
// 	{
// 		master->imput = readline("\033[32mminishell% \033[0m");
// 		if (!master->imput)
// 			break ;
// 		master->in = ft_split(master->imput, ' ');
// 		if (ft_strcmp(master->in[0], "exit") == 0)
// 			ft_exit(master);
// 		if (ft_strcmp(master->in[0], "unset") == 0)
// 			ft_unset(master, &master->in[1]);
// 		else if (ft_strcmp(master->in[0], "env") == 0)
// 			ft_env(master);
// 		else if (ft_strcmp(master->in[0], "export") == 0)
// 			filter_export(master);
// 		else if (master->in && master->in[0])
// 		{
// 			if (fork() == 0)
// 				ft_bin(master->in);
// 			else
// 				wait(NULL);
// 		}
// 		add_history(master->imput);
// 	}
// 	free(master->imput);
// }

int	ft_countchar(char *str, char ch)
{
	int	i;

	i = 0;
	while (str && *str)
	{
		if (*str == ch)
			i++;
		str++;
	}
	return (i);
}

void	rm_void(char **mat)
{
	int	i;
	int	j;

	i = -1;
	if (!mat || !*mat)
		return ;
	while (mat[++i])
	{
		j = 0;
		while (mat[i][j] == ' ' || mat[i][j] == '\t')
			j++;
		if (mat[i][j] == '\0')
		{
			while (mat[i + 1] != NULL)
			{
				mat[i] = mat[i + 1];
				i++;
			}
			mat[i] = NULL;
			free(mat[i + 1]);
			return ;
		}
	}
}

int	wait_prompt(t_master *master)
{
	char	*tmp;

	tmp = readline("\033[32m> \033[0m");
	master->imput = (char *)ft_realloc(master->imput, (ft_strlen(master->imput)
				+ ft_strlen(tmp) + 1));
	ft_strcat(master->imput, tmp);
	free_matriz(master->in);
	master->in = ft_split(master->imput, '|');
	rm_void(master->in);
	if (!validpipe(master->imput))
		return (1);
	if ((ft_countchar(master->imput, '|') > 0) && (ft_countchar(master->imput,
				'|') >= ft_count_matriz(master->in)))
	{
		wait_prompt(master);
	}
	return (0);
}

int	do_pipe(t_master *master)
{
	rm_void(master->in);
	if ((ft_countchar(master->imput, '|') > 0) && (ft_countchar(master->imput,
				'|') >= ft_count_matriz(master->in)))
	{
		if (wait_prompt(master))
		{
			return (printf("bash: syntax error near unexpected token `|'\n"), 1);
		}
		if (!its_ok(master->imput))
			return (printf("Error\n"), 1);
	}
	ft_pipe(master);
	return (0);
}

int	validpipe(char *str)
{
	int	i;

	i = -1;
	while (str && str[++i])
	{
		if (str[i] == '|')
		{
			i++;
			while (str[i] == ' ' || str[i] == '\t')
				i++;
			if (str[i] == '|')
				return (0);
		}
	}
	return (1);
}

int	its_ok(char *str)
{
	int	i;
	int	asp;

	i = 0;
	asp = 0;
	while (str[i])
	{
		if (str[i] == '\"' || str[i] == '\'')
		{
			if (asp)
				asp = 0;
			else
				asp = 1;
		}
		if ((str[i] == '>' || str[i] == '<' || str[i] == '|') && asp)
			return (0);
		i++;
	}
	if (asp)
		return (0);
	return (validpipe(str));
}

int	main(int ac, char **av, char **env)
{
	t_master	*master;

	master = (t_master *)malloc(sizeof(t_master));
	master->environ = ft_arrdup(env);
	env = master->environ;
	while (1 && av && ac)
	{
		master->imput = readline("minishell% ");
		if (!master->imput)
			break ;
		if (its_ok(master->imput))
		{
			master->in = ft_split(master->imput, '|');
			if (ft_count_matriz(master->in) >= 2 || ft_countchar(master->imput, '|'))
				do_pipe(master);
			else
			{
				free_matriz(master->in);
				master->in = ft_split(master->imput, ' ');
				if (master->in && master->in[0])
				{
					if (fork() == 0)
						ft_bin(master->in);
					else
						wait(NULL);
				}
			}
		}
		else
			printf("ERROR\n");
		add_history(master->imput);
	}
	free(master->imput);
}

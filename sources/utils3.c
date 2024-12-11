/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joandre <joandre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 21:10:56 by joandre           #+#    #+#             */
/*   Updated: 2024/12/11 01:47:49 by joandre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	str_replace_del(char *str, char target, char to_replace)
{
	int	i;
	int	simple_asp;
	int	double_asp;

	simple_asp = 0;
	double_asp = 0;
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\'')
			simple_asp = !simple_asp;
		else if (str[i] == '"')
			double_asp = !double_asp;
		if (!simple_asp && !double_asp && str[i] == target)
		{
			str[i] = to_replace;
		}
		i++;
	}
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
		trim_whitespace(mat[i]);
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
		}
	}
}

int	currect_tmp(char *tmp)
{
	int	i;

	i = 0;
	if (ft_strcmp(tmp, "") == 0)
		return (0);
	while (tmp[i] && (tmp[i] == ' ' || tmp[i] == '\t'))
		i++;
	return (tmp[i] != '\0');
}

int	wait_prompt(t_master *master)
{
	char	*tmp;
	char	*new_input;

	tmp = readline("> ");
	if (!tmp)
		exit(42);
	if (correct_pipes(tmp) == 0 || validpipe(tmp) == 0)
		return (printf("Error\n"), free(tmp), free_matriz(master->in), exit(1),
			1);
	if (!currect_tmp(tmp))
		return (free(tmp), wait_prompt(master));
	add_history(tmp);
	str_replace_del(tmp, '|', 127);
	new_input = ft_strjoin(master->imput, tmp);
	free(master->imput);
	free(tmp);
	master->imput = new_input;
	free_matriz(master->in);
	master->in = ft_split(master->imput, 127);
	if (!validpipe(master->imput))
		return (1);
	if ((ft_countchar(master->imput, 127) > 0) && (ft_countchar(master->imput,
				127) >= ft_count_matriz(master->in)))
		wait_prompt(master);
	return (0);
}

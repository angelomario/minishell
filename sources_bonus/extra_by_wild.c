/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra_by_wild.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquissan <aquissan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 11:15:04 by aquissan          #+#    #+#             */
/*   Updated: 2025/03/12 15:37:23 by aquissan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell_bonus.h"

char	**addstronmat(char ***mat, char *str)
{
	int		i;
	char	**matrix;

	if (str)
	{
		matrix = (char **)malloc((ft_count_matriz(*mat) + 2) * sizeof(char *));
		i = 0;
		while ((*mat) && (*mat)[i])
		{
			matrix[i] = ft_strdup((*mat)[i]);
			i++;
		}
		matrix[i++] = ft_strdup(str);
		matrix[i] = NULL;
		free(str);
		ft_arrtab(matrix);
		free_matriz(*mat);
		*mat = matrix;
		return (matrix);
	}
	return (*mat);
}

int	construct_wild(char **expression, t_wild *wild)
{
	char	*tmp;

	if (set_waldcards(wild, expression) == 1)
		return (1);
	if (wild->pre != NULL)
	{
		tmp = ft_strjoin(wild->pre, *expression);
		free(*expression);
		*expression = tmp;
	}
	if (wild->pos != NULL)
	{
		tmp = ft_strjoin(*expression, wild->pos);
		free(*expression);
		*expression = tmp;
	}
	return (0);
}

char	*get_pre_wild(char *expr, int pos)
{
	int		i;
	char	*pre;

	i = 0;
	while (expr && pos >= 0 && (expr[pos] != ' ' && expr[pos] != '\t'))
		--pos;
	if (pos >= 0)
	{
		pre = (char *)malloc(sizeof(char) * (pos + 2));
		while (expr && expr[i] && i <= pos)
		{
			pre[i] = expr[i];
			i++;
		}
		pre[i] = '\0';
		return (pre);
	}
	return (NULL);
}

char	*get_pattern(char **pos, int i)
{
	char	*pattern;
	char	*tmp2;

	tmp2 = NULL;
	if ((*pos) && (*pos)[i] != ' ')
	{
		pattern = get_wildcard_expression(*pos, i);
		if (ft_strlen(pattern) != ft_strlen(*pos))
		{
			tmp2 = ft_strdup(&(*pos)[ft_strlen(pattern)]);
		}
		free(*pos);
		if (tmp2)
			*pos = tmp2;
		else
			*pos = NULL;
		return (pattern);
	}
	return (NULL);
}

int	remove_word(char *str, int index)
{
	int	start;
	int	end;
	int	i;

	if (!str)
		return (index);
	start = index;
	while (start > 0 && str[start - 1] != ' ' && str[start - 1] != '\t')
		start--;
	end = index;
	while (str[end] && str[end] != ' ' && str[end] != '\t')
		end++;
	i = start;
	while (str[end])
		str[i++] = str[end++];
	str[i] = '\0';
	return (-1);
}

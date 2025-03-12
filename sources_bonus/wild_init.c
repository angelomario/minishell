/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wild_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquissan <aquissan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 13:52:42 by aquissan          #+#    #+#             */
/*   Updated: 2025/03/12 15:35:46 by aquissan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell_bonus.h"

int	subst_word(char **str, char *to_add, int start)
{
	char	*tmp;
	char	*tmp2;
	char	*expr;
	int		end;

	end = start;
	tmp = NULL;
	while ((*str)[end] && ((*str)[end] != ' ' && (*str)[end] != '\t'))
		end++;
	if ((*str)[end])
		tmp = ft_strdup(&(*str)[end]);
	(*str)[start] = '\0';
	expr = ft_strjoin(*str, to_add);
	if (tmp)
	{
		tmp2 = ft_strjoin(expr, tmp);
		free(expr);
		free(tmp);
		free(*str);
		*str = tmp2;
		return (0);
	}
	return (free(*str), *str = expr, 0);
}

int	concert_expr(char **expr)
{
	int	i;

	i = 0;
	while ((*expr)[i])
	{
		if ((*expr)[i] == '*')
		{
			while ((*expr)[i + 1] && (*expr)[i + 1] == '*')
			{
				ft_memmove((*expr) + i, (*expr) + i + 1, ft_strlen((*expr)
						+ i));
			}
		}
		i++;
	}
	return (0);
}

void	do_wildcard(char **input)
{
	int		i;
	char	*tmp;

	i = 0;
	while ((*input) && (*input)[i])
	{
		tmp = NULL;
		if ((*input)[i] == '*')
			tmp = proccess_wildcard(get_wildcard_expression(*input, i));
		if (tmp)
		{
			while (i > 0 && ((*input)[i] != ' ' && (*input)[i] != '\t'))
				i--;
			if (i == 0)
				subst_word(input, tmp, i);
			else
				subst_word(input, tmp, i + 1);
			free(tmp);
			i = -1;
		}
		i++;
	}
}

int	compare_append(char **str, char *pattern)
{
	int		lens;
	int		lenp;
	char	*full_pattern;
	char	*tmp;

	tmp = ft_strchr(pattern, '/');
	lens = ft_strlen(*str) - 1;
	lenp = ft_strlen(pattern) - ft_strlen(tmp) - 1;
	while (lenp >= 0 && lens >= 0 && (*str)[lens] == pattern[lenp])
	{
		lenp--;
		lens--;
	}
	if (lenp == -1)
	{
		full_pattern = ft_strjoin(*str, tmp);
		free(*str);
		*str = full_pattern;
		return (1);
	}
	return (0);
}

int	update_expression(char **expression, char **mat)
{
	int		i;
	int		j;
	int		k;
	int		len;
	char	*expr;

	i = 0;
	len = 0;
	while (mat && mat[i])
		len += ft_strlen(mat[i++]);
	expr = (char *)malloc(sizeof(char) * (len + 1 + i));
	i = 0;
	k = 0;
	while (mat && mat[i])
	{
		j = -1;
		while (mat[i][++j])
			expr[k++] = mat[i][j];
		i++;
		if (mat[i])
			expr[k++] = ' ';
	}
	free_matriz(mat);
	return (expr[k] = '\0', free(*expression), *expression = expr, 0);
}

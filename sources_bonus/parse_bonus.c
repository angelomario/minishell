/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joandre <joandre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 16:58:07 by aquissan          #+#    #+#             */
/*   Updated: 2024/12/11 08:37:05 by joandre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	countdels(char *in)
{
	int	i;
	int	word;

	i = -1;
	word = 1;
	if (!in)
		return (0);
	while (in && in[++i])
	{
		if (in[i] == '>')
		{
			while (in[i] == '>')
				i++;
			word += 2;
		}
		else if (in[i] == '<')
		{
			while (in[i] == '<')
				i++;
			word += 2;
		}
	}
	return (word);
}

void	trim_whitespace(char *str)
{
	char	*end;
	char	*start;

	start = str;
	while (*start && *start == ' ')
		start++;
	if (*start == '\0')
	{
		str[0] = '\0';
		return ;
	}
	end = start + ft_strlen(start) - 1;
	while (end > start && *end == ' ')
		end--;
	*(end + 1) = '\0';
	ft_memmove(str, start, end - start + 2);
}

char	*getdel(char *input, char del, int *pos)
{
	char	*tmp;
	int		i;
	int		word;

	i = *pos;
	word = 0;
	if (input && pos && input[i])
	{
		while (input[i] && (input[i] == del))
		{
			i++;
			word++;
		}
		tmp = (char *)malloc((word + 1) * sizeof(char));
		if (!tmp)
			return (NULL);
		i = 0;
		while (input[*pos] == del)
			tmp[i++] = input[(*pos)++];
		tmp[i] = '\0';
		return (tmp);
	}
	return (NULL);
}

char	*getnodel(char *input, int *pos)
{
	char	*tmp;
	int		i;
	int		word;

	i = *pos;
	word = 0;
	if (input && pos && input[i])
	{
		while (input[i] && (input[i] != '<' && input[i] != '>'))
		{
			i++;
			word++;
		}
		tmp = (char *)malloc((word + 1) * sizeof(char));
		if (!tmp)
			return (NULL);
		i = 0;
		while (input[*pos] && (input[*pos] != '<' && input[*pos] != '>'))
			tmp[i++] = input[(*pos)++];
		tmp[i] = '\0';
		trim_whitespace(tmp);
		return (tmp);
	}
	return (NULL);
}

char	**parsedel(char *imput)
{
	int		i;
	int		index;
	char	**in;

	if (!imput)
		return (NULL);
	in = (char **)malloc((countdels(imput) + 1) * sizeof(char *));
	i = 0;
	index = 0;
	while (imput[i])
	{
		if ((imput[i] == '>') || (imput[i] == '<'))
		{
			in[index++] = getdel(imput, imput[i], &i);
		}
		else
			in[index++] = getnodel(imput, &i);
	}
	in[index] = NULL;
	return (in);
}

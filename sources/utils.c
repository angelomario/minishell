/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joandre <joandre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 15:00:04 by joandre           #+#    #+#             */
/*   Updated: 2024/11/25 22:11:52 by joandre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	format_imput(char **s, int n)
{
	int	s_quote;
	int	d_quote;
	int	i;

	i = 0;
	s_quote = 0;
	d_quote = 0;
	while ((*s)[i])
	{
		if ((*s)[i] == '"' && !s_quote)
			d_quote = !d_quote;
		else if ((*s)[i] == '\'' && !d_quote)
			s_quote = !s_quote;
		if ((*s)[i] == ' ' && !d_quote && !s_quote)
			(*s)[i] = n;
		i++;
	}
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
		if (str[i] == '\'' && !simple_asp)
			simple_asp = !simple_asp;
		else if (str[i] == '"' && !simple_asp)
			double_asp = !double_asp;
		if (!simple_asp && !double_asp && str[i] == target)
		{
			str[i] = to_replace;
		}
		i++;
	}
}

char	*ft_format_quotes(char *s, char *c)
{
	char	quote;
	int		i;
	int		j;
	char	*str;
	int		len;

	j = 0;
	len = ft_strlen(s);
	str = malloc(sizeof(char) * (len + 1));
	i = 0;
	quote = 0;
	while (s[i])
	{
		if (quote == 0)
		{
			if (s[i] == '\'' || s[i] == '"')
			{
				quote = s[i];
				i++;
			}
			else
				str[j++] = s[i++];
		}
		else
		{
			if (s[i] == quote)
			{
				quote = 0;
				i++;
			}
			else
				str[j++] = s[i++];
		}
	}
	*c = quote;
	str[j] = '\0';
	return (str);
}

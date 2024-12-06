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

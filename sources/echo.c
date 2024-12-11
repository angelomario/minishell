/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joandre <joandre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 08:25:32 by aquissan          #+#    #+#             */
/*   Updated: 2024/12/11 00:07:24 by joandre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_isalnum_more(int c)
{
	if ((c >= 48 && c <= 57) || (c >= 65 && c <= 90) || (c >= 97 && c <= 122)
		|| c == '_' || c == '?' || c == '\'' || c == '"')
		return (1);
	else
		return (0);
}

void	str_replace_all(char *str, char target, char to_replace)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == target)
		{
			str[i] = to_replace;
		}
		i++;
	}
}

void	ft_flag_echo(char **s, int *i)
{
	int	j;

	j = 0;
	while (s[(*i)])
	{
		j = 0;
		if (s[(*i)][j] == '-' && s[(*i)][j + 1] == 'n')
		{
			j++;
			while (s[(*i)][j])
			{
				if (s[(*i)][j] != 'n')
					return ;
				j++;
			}
		}
		if (j < 1)
			return ;
		(*i)++;
	}
}

int	ft_echo(char **in)
{
	int		i;
	char	c;

	if (ft_strncmp(in[0], "echo", ft_strlen("echo")) == 0)
	{
		i = 1;
		c = '\n';
		if (in[i] == NULL)
			return (ft_putchar_fd('\n', 1), 1);
		ft_flag_echo(in, &i);
		if (i > 1)
			c = '\0';
		else
			i = 1;
		while (in[i])
		{
			ft_putstr_fd(in[i++], 1);
			if (in[i])
				ft_putchar_fd(' ', 1);
		}
		return (printf("%c", c), 0);
	}
	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strsplit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joandre <joandre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 12:49:05 by aquissan          #+#    #+#             */
/*   Updated: 2024/12/11 01:38:43 by joandre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_delimiter(char *s, char *delimiter)
{
	return (ft_strncmp(s, delimiter, ft_strlen(delimiter)) == 0);
}

static char	**ft_sep_words(char **strs, int size, char *s, char *delimiter)
{
	int	count;
	int	c_word;
	int	temp;

	count = 0;
	c_word = 0;
	while (c_word < size)
	{
		while (s[count] != '\0' && is_delimiter(&s[count], delimiter))
			count += ft_strlen(delimiter);
		temp = count;
		while (s[temp] != '\0' && !is_delimiter(&s[temp], delimiter))
			temp++;
		strs[c_word] = malloc((temp - count + 1) * sizeof(char));
		if (strs[c_word] == NULL)
			return (NULL);
		ft_memcpy((void *)strs[c_word], (void *)&s[count], temp - count);
		strs[c_word][temp - count] = '\0';
		count = temp;
		c_word++;
	}
	strs[c_word] = NULL;
	return (strs);
}

char	**ft_strsplit(char *s, char *delimiter)
{
	char	**strs;
	int		pos;
	int		size;

	pos = 0;
	size = 0;
	if (s == NULL || delimiter == NULL)
		return (NULL);
	while (s[pos] != '\0')
	{
		if (is_delimiter(&s[pos], delimiter))
		{
			size++;
			pos += ft_strlen(delimiter);
		}
		else
			pos++;
	}
	if (s[pos - 1] != '\0')
		size++;
	strs = (char **)malloc((size + 1) * sizeof(char *));
	if (strs == NULL)
		return (NULL);
	return (ft_sep_words(strs, size, (char *)s, delimiter));
}

int	replace_env(t_master *master, char *name, char *value)
{
	char	**env;
	int		nlen;

	env = master->environ;
	if (ft_strchr(name, '=') == NULL)
		nlen = ft_strlen(name);
	else
		nlen = ft_strlen(name) - 1;
	while (*env)
	{
		if ((ft_strncmp(*env, name, nlen) == 0) && ((*env)[nlen] == '='
			|| (*env)[nlen] == '\0'))
		{
			if (value == NULL && ft_strchr(name, '='))
				return (free(*env), (*env = ft_joincheck(name, value)), 0);
			if (ft_strlen(ft_strchr(*env, '=')) > 1 && !value)
				return (0);
			free(*env);
			*env = ft_joincheck(name, value);
			return (0);
		}
		env++;
	}
	return (-1);
}

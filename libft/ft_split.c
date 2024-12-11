/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joandre <joandre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 10:23:17 by joandre           #+#    #+#             */
/*   Updated: 2024/12/11 00:28:36 by joandre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	**ft_sep_words(char **strs, int size, char *s, char c);
static void	ft_free_strs(char **strs, int size);

char	**ft_split(char const *s, char c)
{
	char	**strs;
	int		pos;
	int		size;

	if (s == NULL)
		return (NULL);
	pos = -1;
	size = 0;
	while (s[++pos] != '\0')
	{
		if (s[pos] != c && (s[pos + 1] == c || s[pos + 1] == '\0'))
			size++;
	}
	strs = malloc((size + 1) * sizeof(char *));
	if (strs == NULL)
		return (NULL);
	strs = ft_sep_words(strs, size, (char *)s, c);
	return (strs);
}

static char	**ft_sep_words(char **strs, int size, char *s, char c)
{
	int	count;
	int	c_word;
	int	temp;

	count = 0;
	c_word = 0;
	while (c_word < size)
	{
		while (s[count] == c)
			count++;
		temp = count;
		while (s[temp] != c && s[temp] != '\0')
			temp++;
		strs[c_word] = malloc((temp - count + 1) * sizeof(char));
		if (strs[c_word] == NULL)
		{
			ft_free_strs(strs, c_word);
			return (NULL);
		}
		ft_memcpy((void *)strs[c_word], (const void *)&s[count], temp - count);
		strs[c_word][temp - count] = '\0';
		count = temp;
		c_word++;
	}
	return (strs[c_word] = NULL, strs);
}

static void	ft_free_strs(char **strs, int size)
{
	int	i;

	i = 0;
	while (strs[i] != NULL && i < size)
	{
		free(strs[i]);
	}
	free(strs);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joandre <joandre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 01:46:33 by joandre           #+#    #+#             */
/*   Updated: 2024/12/11 01:46:34 by joandre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strstr(char *s1, char *s2)
{
	int	i;

	i = 0;
	if ((!s1 || !s2) || (!s1[0] || !s2[0]))
		return (NULL);
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return (&s2[i]);
}

void	*ft_realloc(void *ptr, size_t old_size, size_t new_size)
{
	void	*new_ptr;
	size_t	size_to_copy;

	if (new_size == 0)
	{
		free(ptr);
		return (NULL);
	}
	if (ptr == NULL)
		return (malloc(new_size));
	new_ptr = malloc(new_size);
	if (!new_ptr)
		return (NULL);
	if (old_size < new_size)
		size_to_copy = old_size;
	else
		size_to_copy = new_size;
	ft_memcpy(new_ptr, ptr, size_to_copy);
	free(ptr);
	return (new_ptr);
}

void	ft_arrtab(char **arr)
{
	char	*temp;
	int		i;
	int		j;

	i = -1;
	while (++i < ft_count_matriz(arr))
	{
		j = i + 1;
		while (j < ft_count_matriz(arr))
		{
			if (ft_strcmp(arr[i], arr[j]) > 0)
			{
				temp = arr[i];
				arr[i] = arr[j];
				arr[j] = temp;
			}
			j++;
		}
	}
}

int	ft_countrp(char *str, char *to_find)
{
	int	i;
	int	k;
	int	j;

	i = -1;
	k = 0;
	j = 0;
	while (str && str[++i])
	{
		k = 0;
		while ((str[i] == to_find[k]) && to_find[k])
		{
			i++;
			k++;
		}
		if (str[i] == to_find[0])
			return (-1);
		if (to_find[k] == '\0')
			j++;
	}
	return (j);
}

void	ft_concert_env(t_master *master)
{
	char	**env;

	env = master->environ;
	while (*env)
	{
		remove_if_even(*env, '"');
		env++;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquissan <aquissan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 15:05:49 by aquissan          #+#    #+#             */
/*   Updated: 2025/03/07 18:15:44 by aquissan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell_bonus.h"

int	ft_count_matriz(char **mat)
{
	int	i;

	i = 0;
	if (mat == NULL || (*mat) == NULL)
		return (0);
	while (mat[i] != NULL)
		i++;
	return (i);
}

char	**ft_arrdup(char **arr)
{
	int		i;
	char	**tmp;

	if (arr == NULL || *arr == NULL)
		return (NULL);
	tmp = (char **)malloc((ft_count_matriz(arr) + 1) * sizeof(char *));
	i = 0;
	while (arr[i] != NULL)
	{
		tmp[i] = ft_strdup(arr[i]);
		i++;
	}
	tmp[i] = NULL;
	return (tmp);
}

void	free_matriz(char **mat)
{
	int	i;

	i = 0;
	if (mat == NULL || *mat == NULL)
	{
		free(mat);
		return ;
	}
	while (mat[i])
		free(mat[i++]);
	free(mat);
}

int	ft_clean_master(t_master *master)
{
	if (master->in && *master->in)
	{
		free_matriz(master->in);
		master->in = NULL;
	}
	if (master->options)
	{
		free_matriz(master->options);
		master->options = (char **)malloc(sizeof(char *) * 1);
		*master->options = NULL;
	}
	if (master->output)
	{
		free(master->output);
		master->output = NULL;
	}
	if (master->imput)
	{
		free(master->imput);
		master->imput = NULL;
	}
	return (0);
}

int	ft_masterclean(t_master *master)
{
	if (master->in && *master->in)
	{
		free_matriz(master->in);
		master->in = NULL;
	}
	if (master->options)
	{
		free_matriz(master->options);
		master->options = (char **)malloc(sizeof(char *) * 1);
		*master->options = NULL;
	}
	if (master->output)
	{
		free(master->output);
		master->output = NULL;
	}
	return (0);
}

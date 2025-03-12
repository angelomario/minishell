/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquissan <aquissan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 06:35:27 by aquissan          #+#    #+#             */
/*   Updated: 2025/03/12 15:35:07 by aquissan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell_bonus.h"

int	check_inclusion(char **str, t_wild *wild)
{
	int	lenstr;
	int	lenpatt;

	if (wild->pattern && *str)
	{
		if (append_pattern(str, wild->pattern) == 0)
			return (1);
		if (ft_strchr(wild->pattern, '/') && compare_append(str, wild->pattern))
			return (1);
		lenpatt = ft_strlen(wild->pattern) - 1;
		lenstr = ft_strlen((*str)) - 1;
		while ((lenpatt >= 0 && lenstr >= 0)
			&& ((*str)[lenstr] == wild->pattern[lenpatt]))
		{
			lenpatt--;
			lenstr--;
		}
		return (lenpatt < 0);
	}
	return ((*str) != NULL);
}

int	check_path(char **full, char *to_cmp)
{
	int		i;
	int		len;
	char	*tmp;

	i = 0;
	len = ft_strlen(to_cmp);
	if (!to_cmp)
		return (0);
	if (to_cmp && to_cmp[len - 1] == '/')
	{
		tmp = ft_strjoin(to_cmp, *full);
		free(*full);
		*full = tmp;
		return (0);
	}
	while ((*full)[i] && to_cmp[i] && ((*full)[i] == to_cmp[i]))
		i++;
	if (to_cmp[i] == '\0')
		return (0);
	return (free(*full), 1);
}

int	before_add_expr(char **full_path, t_wild *wild, char ***mat)
{
	if (check_path(full_path, wild->path))
		return (1);
	if (wild->pattern)
	{
		if (check_inclusion(full_path, wild))
			addstronmat(mat, *full_path);
		else
			free(*full_path);
	}
	else
		addstronmat(mat, *full_path);
	return (0);
}

int	set_waldcards(t_wild *wild, char **input)
{
	struct dirent	*entry;
	char			*full_path;
	DIR				*dir;
	char			**mat;

	if (wild->path && wild->path[ft_strlen(wild->path) - 1] == '/')
		dir = opendir(wild->path);
	else
		dir = opendir("./");
	if (!dir)
		return (1);
	mat = (char **)malloc(sizeof(char *) * 1);
	mat[0] = NULL;
	while (1)
	{
		entry = readdir(dir);
		if (entry == NULL)
			break ;
		if (entry->d_name[0] == '.')
			continue ;
		full_path = ft_strdup(entry->d_name);
		if (before_add_expr(&full_path, wild, &mat))
			continue ;
	}
	return (closedir(dir), update_expression(input, mat), 0);
}

char	*proccess_wildcard(char *input)
{
	int		i;
	t_wild	wild;

	i = -1;
	concert_expr(&input);
	while (input && input[++i])
	{
		if (input[i] == '*')
		{
			wild.path = get_pathdir(input, i);
			wild.pre = get_pre_wild(input, i);
			wild.pos = get_pos_wild(input, i);
			wild.pattern = get_pattern(&wild.pos, 0);
			if (construct_wild(&input, &wild) == 1)
				i = remove_word(input, i);
			clean_wild(&wild);
		}
	}
	i = 0;
	while (input[i] && (input[i] == ' ' || input[i] == '\t'))
		i++;
	if (input[i] == '\0')
		return (free(input), NULL);
	return (input);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanded.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joandre <joandre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 20:40:48 by joandre           #+#    #+#             */
/*   Updated: 2024/12/11 11:58:25 by joandre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	append_char(char **output, int *j, char c)
{
	char	*temp;

	temp = malloc(*j + 2);
	if (!temp)
		return ;
	if (*output)
	{
		ft_strcpy(temp, *output);
		free(*output);
	}
	temp[*j] = c;
	temp[*j + 1] = '\0';
	*output = temp;
	(*j)++;
}

void	append_str(char **output, int *j, char *str)
{
	int		len;
	char	*temp;

	len = ft_strlen(str);
	temp = malloc(*j + len + 1);
	if (!temp)
		return ;
	if (*output)
	{
		ft_strcpy(temp, *output);
		free(*output);
	}
	ft_strcpy(&temp[*j], str);
	*output = temp;
	*j += len;
}

void	process_var(char *input, int *i, t_master *master, int *j)
{
	t_data	data;

	data.var_start = ++(*i);
	if (input[data.var_start] == '?')
	{
		data.value = ft_itoa(master->status);
		append_str(&master->output, j, data.value);
		free(data.value);
	}
	else
	{
		while (input[*i] && (isalnum(input[*i]) || input[*i] == '_'))
			(*i)++;
		ft_strncpy(data.var_name, &input[data.var_start], *i - data.var_start);
		data.var_name[*i - data.var_start] = '\0';
		data.value = ft_getenv(master->environ, data.var_name);
		if (data.value)
		{
			str_replace_all(data.value, '\'', 27);
			str_replace_all(data.value, '|', 23);
			append_str(&master->output, j, data.value);
		}
		(*i)--;
	}
}

char	*expanded(t_master *master, char *imput)
{
	int		i;
	int		j;
	t_data	data;

	master->output = NULL;
	i = 0;
	j = 0;
	data.q_s = 0;
	data.q_duo = 0;
	while (imput[i])
	{
		if (imput[i] == '\'' && !data.q_duo)
			data.q_s = !data.q_s;
		else if (imput[i] == '"' && !data.q_s)
			data.q_duo = !data.q_duo;
		else
			append_char(&master->output, &j, imput[i]);
		i++;
	}
	str_replace_all(master->output, 20, '"');
	str_replace_all(master->output, 21, '\'');
	str_replace_all(master->output, 27, '\'');
	str_replace_all(master->output, 23, '|');
	return (master->output);
}

char	*expan_env(t_master *master, char *imput)
{
	t_data	s;

	master->output = NULL;
	s = (t_data){0, 0, 0, 0, 0, NULL, 0, NULL, {0}, NULL, NULL, NULL, NULL};
	while (imput[s.i])
	{
		if (imput[s.i] == '\'' && !s.q_duo)
		{
			s.q_s = !s.q_s;
			append_char(&master->output, &s.j, imput[s.i]);
		}
		else if (imput[s.i] == '"' && !s.q_s)
		{
			s.q_duo = !s.q_duo;
			append_char(&master->output, &s.j, imput[s.i]);
		}
		else if (imput[s.i] == '$' && (imput[s.i + 1] != '\0'
				&& ft_isalnum_more(imput[s.i + 1])) && !s.q_s)
			process_var(imput, &s.i, master, &s.j);
		else
			append_char(&master->output, &s.j, imput[s.i]);
		s.i++;
	}
	return (free(imput), master->output);
}

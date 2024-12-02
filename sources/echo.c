/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joandre <joandre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 08:25:32 by aquissan          #+#    #+#             */
/*   Updated: 2024/11/25 21:49:04 by joandre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	char	var_name[100];
	int		var_start;
	char	*value;

	var_start = ++(*i);
	if (input[var_start] == '?')
	{
		value = ft_itoa(master->status);
		append_str(&master->output, j, value);
		free(value);
	}
	else
	{
		while (input[*i] && (isalnum(input[*i]) || input[*i] == '_'))
			(*i)++;
		ft_strncpy(var_name, &input[var_start], *i - var_start);
		var_name[*i - var_start] = '\0';
		value = ft_getenv(master->environ, var_name);
		if (value)
			append_str(&master->output, j, value);
		(*i)--;
	}
}

char	*expanded(t_master *master, char *imput)
{
	int	i;
	int	j;
	int	in_single_quotes;
	int	in_double_quotes;

	master->output = NULL;
	i = 0;
	j = 0;
	in_single_quotes = 0;
	in_double_quotes = 0;
	(void)master;
	while (imput[i])
	{
		if (imput[i] == '\'' && !in_double_quotes)
			in_single_quotes = !in_single_quotes;
		else if (imput[i] == '"' && !in_single_quotes)
			in_double_quotes = !in_double_quotes;
		else if (imput[i] == '$' && !in_single_quotes)
			process_var(imput, &i, master, &j);
		else
			append_char(&master->output, &j, imput[i]);
		i++;
	}
	return (master->output);
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
		if (ft_strcmp(in[i], "-n") == 0)
		{
			i = 2;
			c = '\0';
		}
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

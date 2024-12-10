/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joandre <joandre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 08:25:32 by aquissan          #+#    #+#             */
/*   Updated: 2024/12/06 07:49:35 by joandre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_isalnum_more(int c)
{
	if ((c >= 48 && c <= 57) || (c >= 65 && c <= 90) || (c >= 97 && c <= 122)
		|| c == '_')
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

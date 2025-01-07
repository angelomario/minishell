/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joandre <joandre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 15:00:04 by joandre           #+#    #+#             */
/*   Updated: 2024/12/11 01:39:18 by joandre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell_bonus.h"

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
		if (((*s)[i] == ' ' || (*s)[i] == '\t') && !d_quote && !s_quote)
			(*s)[i] = n;
		i++;
	}
}

int	is_red(char *str)
{
	if (!str)
		return (0);
	if (ft_strlen(str) >= 2)
	{
		if ((str[0] == '>') && (str[1] == '>'))
			return (1);
		else if ((str[0] == '<') && (str[1] == '<'))
			return (1);
	}
	if (str[0] == '<')
		return (1);
	if (str[0] == '>')
		return (1);
	return (0);
}

void	ft_replace_c(char *s)
{
	int	i;

	i = 0;
	if ((ft_strncmp(s, "\"\"", 2) == 0 || ft_strncmp(s, "\'\'", 2) == 0)
		&& (s[2] == ' ' || is_red(&s[2])))
	{
		while ((s[i] == '"' || s[i] == '\'') && s[i])
		{
			if (s[i] == '"')
				s[i] = 20;
			if (s[i] == '\'')
				s[i] = 21;
			i++;
		}
	}
}

int	wait_sons(t_master *master)
{
	signal(SIGINT, SIG_IGN);
	waitpid(master->pid_child, &master->status, 0);
	master->status = WEXITSTATUS(master->status);
	if (master->status == 24)
	{
		print_default_fd(master, ft_strdup("exit\n"));
		exit(0);
	}
	else
		master->red = 0;
	signal(SIGINT, sigint_handler);
	return (0);
}

char	*remove_if_even(char *str, char ch)
{
	int	count;
	int	i;
	int	j;

	if (!str)
		return (NULL);
	count = 0;
	i = -1;
	while (str[++i])
		if (str[i] == ch)
			count++;
	if (count % 2 == 0 && count > 1)
	{
		i = 0;
		j = 0;
		while (str[i])
		{
			if (str[i] != ch)
				str[j++] = str[i];
			i++;
		}
		str[j] = '\0';
	}
	return (str);
}

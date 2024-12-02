/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joandre <joandre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 05:48:49 by joandre           #+#    #+#             */
/*   Updated: 2024/11/26 07:44:20 by joandre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_count_redir(char *s)
{
	int	i;
	int	count;
	int	q_duo;
	int	q_s;

	i = 0;
	count = 0;
	q_s = 0;
	q_duo = 0;
	while (s[i])
	{
		if (s[i] == '"' && !q_s)
			q_duo = !q_duo;
		else if (s[i] == '\'' && !q_duo)
			q_s = !q_s;
		else if ((s[i] == '>' || s[i] == '<') && (!q_s && !q_duo))
			count++;
		i++;
	}
	return (count);
}
char	*ft_format_in_redir(char *s, int i, int j, char c)
{
	t_data	data;

	data.len = strlen(s) + (ft_count_redir(s) * 2) + 1;
	data.q_s = 0;
	data.q_duo = 0;
	data.imput = malloc(sizeof(char) * data.len);
	if (!data.imput)
		return (NULL);
	while (s[i])
	{
		if (s[i] == '"' && !data.q_s)
			data.q_duo = !data.q_duo;
		else if (s[i] == '\'' && !data.q_duo)
			data.q_s = !data.q_s;
		if ((s[i] == '>' || s[i] == '<') && (!data.q_s && !data.q_duo))
		{
			data.imput[j++] = c;
			data.imput[j++] = s[i++];
			if (s[i] == '>' || s[i] == '<')
				data.imput[j++] = s[i++];
			if (s[i] != '\0')
				data.imput[j++] = c;
		}
		else
			data.imput[j++] = s[i++];
	}
	return (data.imput[j] = '\0', data.imput);
}

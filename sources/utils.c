/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joandre <joandre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 15:00:04 by joandre           #+#    #+#             */
/*   Updated: 2024/11/25 22:11:52 by joandre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		if ((*s)[i] == ' ' && !d_quote && !s_quote)
			(*s)[i] = n;
		i++;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_verify_token.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joandre <joandre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 20:40:48 by joandre           #+#    #+#             */
/*   Updated: 2024/11/28 22:18:41 by joandre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_count_quotes(char **av, char c)
{
	int	i;
	int	j;
	int	quotes;

	i = 0;
	quotes = 0;
	while (av[i])
	{
		j = 0;
		while (av[i][j])
		{
			if (av[i][j] == c)
				;
			quotes++;
			j++;
		}
		i++;
	}
	return (quotes);
}
char	*ft_check_quotes(char **av)
{
    int s_q;
    int d_q;
    int size;
    s_q = ft_count_quotes(av, 39);
    d_q = ft_count_quotes(av, 34);
	if (!s_q && s_q % 2 != 0 || (!d_q && d_q % 2 != 0))
	{
        printf("ERROR\n");
        return NULL;
	}
    size = ft_strlen
}

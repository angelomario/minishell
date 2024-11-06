/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joandre <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 10:14:52 by joandre           #+#    #+#             */
/*   Updated: 2024/05/23 10:14:54 by joandre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *destino, const void *origem, size_t quantidade)
{
	char	*convert_destino;
	char	*convert_origem;
	size_t	a;

	a = 0;
	convert_destino = (char *)destino;
	convert_origem = (char *)origem;
	while (a < quantidade)
	{
		convert_destino[a] = convert_origem[a];
		a++;
	}
	return (destino);
}

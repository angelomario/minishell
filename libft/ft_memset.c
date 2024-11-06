/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joandre <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 10:14:20 by joandre           #+#    #+#             */
/*   Updated: 2024/05/23 10:14:22 by joandre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *p, int valor, size_t tamanho)
{
	char	*conversor;

	conversor = (char *)p;
	while (tamanho > 0)
	{
		conversor[tamanho - 1] = valor;
		tamanho--;
	}
	return (p);
}

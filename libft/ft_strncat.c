/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joandre <joandre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 10:18:56 by joandre           #+#    #+#             */
/*   Updated: 2024/12/11 00:29:57 by joandre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncat(char *dest, char *source, size_t dest_size)
{
	size_t	i;
	size_t	j;

	if (!dest || !source || dest_size == 0)
		return (NULL);
	i = 0;
	while (i < dest_size && dest[i])
		i++;
	j = 0;
	while (i + 1 < dest_size && source[j])
		dest[i++] = source[j++];
	if (i < dest_size)
		dest[i] = '\0';
	else if (dest_size > 0)
		dest[dest_size - 1] = '\0';
	return (dest);
}

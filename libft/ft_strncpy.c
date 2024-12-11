/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joandre <joandre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 00:24:05 by joandre           #+#    #+#             */
/*   Updated: 2024/12/11 00:30:57 by joandre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncpy(char *dest, char *source, int n)
{
	int	i;

	i = -1;
	while (source[++i] && i < n)
		dest[i] = source[i];
	dest[i] = '\0';
	return (dest);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joandre <joandre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 00:22:20 by joandre           #+#    #+#             */
/*   Updated: 2024/12/11 00:31:57 by joandre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcpy(char *dest, char *source)
{
	int	i;

	i = -1;
	while (source[++i])
		dest[i] = source[i];
	dest[i] = '\0';
	return (dest);
}

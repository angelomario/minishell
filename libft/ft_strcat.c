/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joandre <joandre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 00:21:24 by joandre           #+#    #+#             */
/*   Updated: 2024/12/11 00:23:09 by joandre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
#include <stdlib.h>

char	*ft_strcat(char *dest, char *source)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	if (!source)
		return (NULL);
	while (dest[i])
		i++;
	while (source[j])
		dest[i++] = source[j++];
	dest[i] = '\0';
	return (dest);
}

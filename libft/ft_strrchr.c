/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joandre <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 10:16:47 by joandre           #+#    #+#             */
/*   Updated: 2024/05/23 10:16:49 by joandre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		count;
	char	*str;
	char	character;

	str = (char *)s;
	character = (unsigned char)c;
	count = ft_strlen(str);
	if (character == '\0')
		return (&str[count]);
	while (--count >= 0)
		if (s[count] == character)
			return (&str[count]);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquissan <aquissan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 10:16:35 by joandre           #+#    #+#             */
/*   Updated: 2025/03/06 15:30:30 by aquissan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int		count;
	char	*str;
	char	character;

	str = (char *)s;
	character = ((unsigned char)c);
	count = 0;
	if (!str)
		return (NULL);
	while ((s[count] != '\0') && s[count])
	{
		if (s[count] == character)
			return (&str[count]);
		count++;
	}
	if (character == '\0')
		return (&str[count]);
	return (0);
}

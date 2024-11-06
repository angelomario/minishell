/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   teste.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joandre <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 13:22:06 by joandre           #+#    #+#             */
/*   Updated: 2024/10/24 13:28:21 by joandre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <readline/readline.h>
int main(int ac, char **av)
{
	int i;
	char	*imput;
	while(1)
	{
		imput = readline("teste> ");
		printf("%s\n", imput);
	}
	return (0);

}


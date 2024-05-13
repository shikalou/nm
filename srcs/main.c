/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldinaut <ldinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 17:43:29 by ldinaut           #+#    #+#             */
/*   Updated: 2024/05/13 19:47:54 by ldinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/nm.h"

int	main(int ac, char **av, char **envp)
{
	(void)ac;
	(void)av;
	(void)envp;

	if (ac == 1)
	{
		int fd = open("a.out", O_RDONLY);
		if (fd == -1)
		{
			printf("nm: 'a.out': %s\n", strerror(errno));
			return (1);
		}
	}
	else
	{
		
		printf("one or more\n");
	}
}
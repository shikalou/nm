/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldinaut <ldinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 17:43:29 by ldinaut           #+#    #+#             */
/*   Updated: 2024/05/14 17:40:24 by ldinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/nm.h"

void	init_struct(int ac, char **av, char **envp)
{
	(void)envp;
	av = parse_params(ac, av);
}

int	main(int argc, char **argv, char **envp)
{
	int		ac;
	char	**av;
	t_data	*data;

	av = argv + 1;
	ac = argc - 1;
	data = malloc(sizeof(t_data));
	init_struct(ac, av, envp);

	av = parse_params(ac, av);

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

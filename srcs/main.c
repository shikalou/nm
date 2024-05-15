/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldinaut <ldinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 17:43:29 by ldinaut           #+#    #+#             */
/*   Updated: 2024/05/15 17:07:24 by ldinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/nm.h"

void	init_struct(t_data *data)
{
	data->g = false;
	data->u = false;
	data->r = false;
	data->p = false;
	data->files = NULL;
}

int	main(int argc, char **argv, char **envp)
{
	(void)envp;
	int		ac;
	int		nb_params;
	char	**av;
	t_data	*data;

	av = argv + 1;
	ac = argc - 1;
	data = malloc(sizeof(t_data));
	if (!data)
		return (1);
	init_struct(data);
	nb_params = parse_params(ac, av, data);
	if (ac - nb_params == 0)
	{
		int fd = open("a.out", O_RDONLY);
		if (fd == -1)
		{
			printf("nm: 'a.out': %s\n", strerror(errno));
			free_struct(data);
			return (1);
		}
		free_struct(data);
		return (0);
	}
	data->files = lst_init(data, ac, av);
	free_struct(data);
	return (0);
}

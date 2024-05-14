/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldinaut <ldinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 17:09:26 by ldinaut           #+#    #+#             */
/*   Updated: 2024/05/14 17:41:01 by ldinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/nm.h"

char	**parse_params(int ac, char **av)
{
	for (int i = 0; i < ac; ++i)
	{
		if (av[i][0] == '-')
		{
			if (ft_strchr(av[i], 'g'))
				printf("LOLOLOL\n");
		}
	}
	return(NULL);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldinaut <ldinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 17:09:26 by ldinaut           #+#    #+#             */
/*   Updated: 2024/05/15 16:34:33 by ldinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/nm.h"

int	parse_params(int ac, char **av, t_data *data)
{
	int ret = 0;

	for (int i = 0; i < ac; ++i)
	{
		if (av[i][0] == '-')
		{
			ret++;
			if (ft_strchr(av[i], 'g'))
				data->g = true;
			if (ft_strchr(av[i], 'u'))
				data->u = true;
			if (ft_strchr(av[i], 'r'))
				data->r = true;
			if (ft_strchr(av[i], 'p'))
				data->p = true;
		}
	}
	return (ret);
}

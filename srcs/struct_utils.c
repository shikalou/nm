/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldinaut <ldinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 16:49:50 by ldinaut           #+#    #+#             */
/*   Updated: 2024/05/15 17:42:39 by ldinaut          ###   ########.fr       */
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

void	freetab(char **tab)
{
	int	i = 0;

	while (tab && tab[i])
	{
		free(tab[i]);
		tab[i] = NULL;
		i++;
	}
	free(tab);
}

void	free_struct(t_data *data)
{
	lstclear(&data->files);
	free(data);
}

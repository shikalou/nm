/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldinaut <ldinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 17:40:35 by ldinaut           #+#    #+#             */
/*   Updated: 2024/06/12 15:09:56 by ldinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/nm.h"

static void	ft_swap64(Elf64_Sym **strs, int i, int j)
{
	Elf64_Sym	*temp;

	temp = strs[i];
	strs[i] = strs[j];
	strs[j] = temp;
}

void	sort_tab64(Elf64_Sym **all_sym, int size, char *str)
{
	int	j;

	for (int i = 0; i < size - 1; ++i)
	{
		j = i + 1;
		while (j < size)
		{
			// if (ft_strncmp(ft_strtrim(str+all_sym[i]->st_name, "_"), ft_strtrim(str+all_sym[j]->st_name, "_"), 10000) > 0)
			if (ft_strncmp(str+all_sym[i]->st_name, str+all_sym[j]->st_name, 10000) > 0)
				ft_swap64(all_sym, i, j);
			j++;
		}
	}
}

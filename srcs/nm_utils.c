/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldinaut <ldinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 17:40:35 by ldinaut           #+#    #+#             */
/*   Updated: 2024/11/04 18:25:47 by ldinaut          ###   ########.fr       */
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

static void	ft_swap32(Elf32_Sym **strs, int i, int j)
{
	Elf32_Sym	*temp;

	temp = strs[i];
	strs[i] = strs[j];
	strs[j] = temp;
}

void	sort_tab64(Elf64_Sym **all_sym, int size, char *str)
{
	int		j;
	char	*i_name;
	char	*j_name;

	for (int i = 0; i < size - 1; ++i)
	{
		j = i + 1;
		while (j < size)
		{
			i_name = str+all_sym[i]->st_name;
			j_name = str+all_sym[j]->st_name;
			// if (ft_strncmp(ft_strtrim(str+all_sym[i]->st_name, "_"), ft_strtrim(str+all_sym[j]->st_name, "_"), 10000) > 0)
			if (ft_strncmp(i_name, j_name, 10000) == 0)
			{
				i_name = all_sym[i]->st_value;
				j_name = all_sym[j]->st_value;
			}
			if (ft_strncmp(i_name, j_name, 10000) > 0)
				ft_swap64(all_sym, i, j);
			j++;
		}
	}
}

void	sort_tab32(Elf32_Sym **all_sym, int size, char *str)
{
	int	j;

	for (int i = 0; i < size - 1; ++i)
	{
		j = i + 1;
		while (j < size)
		{
			// if (ft_strncmp(ft_strtrim(str+all_sym[i]->st_name, "_"), ft_strtrim(str+all_sym[j]->st_name, "_"), 10000) > 0)
			if (ft_strncmp(str+all_sym[i]->st_name, str+all_sym[j]->st_name, 10000) > 0)
				ft_swap32(all_sym, i, j);
			j++;
		}
	}
}

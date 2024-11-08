/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_funcs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldinaut <ldinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 14:48:40 by ldinaut           #+#    #+#             */
/*   Updated: 2024/11/08 15:45:35 by ldinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/nm.h"

void	sort_tab64(Elf64_Sym **all_sym, int size, char *str)
{
	int		j;

	for (int i = 0; i < size - 1; ++i)
	{
		j = i + 1;
		while (j < size)
		{
			// if (ft_strncmp(trimstart(str+all_sym[i]->st_name), trimstart(str+all_sym[j]->st_name), 10000) == 0)
			if (ft_strncmp(str+all_sym[i]->st_name, str+all_sym[j]->st_name, 10000) == 0)
			{
				if (all_sym[i]->st_value > all_sym[j]->st_value)
					ft_swap64(all_sym, i, j);
			}
			// else if (ft_strncmp(trimstart(str+all_sym[i]->st_name), trimstart(str+all_sym[j]->st_name), 10000) > 0)
			else if (ft_strncmp(str+all_sym[i]->st_name, str+all_sym[j]->st_name, 10000) > 0)
				ft_swap64(all_sym, i, j);
			j++;
		}
	}
}

void	revsort_tab64(Elf64_Sym **all_sym, int size, char *str)
{
	int		j;

	for (int i = 0; i < size - 1; ++i)
	{
		j = i + 1;
		while (j < size)
		{
			// if (ft_strncmp(trimstart(str+all_sym[i]->st_name), trimstart(str+all_sym[j]->st_name), 10000) == 0)
			if (ft_strncmp(str+all_sym[i]->st_name, str+all_sym[j]->st_name, 10000) == 0)
			{
				if (all_sym[i]->st_value > all_sym[j]->st_value)
					ft_swap64(all_sym, i, j);
			}
			// else if (ft_strncmp(trimstart(str+all_sym[i]->st_name), trimstart(str+all_sym[j]->st_name), 10000) > 0)
			else if (ft_strncmp(str+all_sym[i]->st_name, str+all_sym[j]->st_name, 10000) < 0)
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
			// if (ft_strncmpalpha(ft_strtrim(str+all_sym[i]->st_name, "_"), ft_strtrim(str+all_sym[j]->st_name, "_"), 10000) == 0)
			if (ft_strncmp(str+all_sym[i]->st_name, str+all_sym[j]->st_name, 10000) == 0)
			{
				if (all_sym[i]->st_value > all_sym[j]->st_value)
					ft_swap32(all_sym, i, j);
			}
			// else if (ft_strncmpalpha(ft_strtrim(str+all_sym[i]->st_name, "_"), ft_strtrim(str+all_sym[j]->st_name, "_"), 10000) > 0)
			else if (ft_strncmp(str+all_sym[i]->st_name, str+all_sym[j]->st_name, 10000) > 0)
				ft_swap32(all_sym, i, j);
			j++;
		}
	}
}

void	revsort_tab32(Elf32_Sym **all_sym, int size, char *str)
{
	int	j;

	for (int i = 0; i < size - 1; ++i)
	{
		j = i + 1;
		while (j < size)
		{
			// if (ft_strncmpalpha(ft_strtrim(str+all_sym[i]->st_name, "_"), ft_strtrim(str+all_sym[j]->st_name, "_"), 10000) == 0)
			if (ft_strncmp(str+all_sym[i]->st_name, str+all_sym[j]->st_name, 10000) == 0)
			{
				if (all_sym[i]->st_value > all_sym[j]->st_value)
					ft_swap32(all_sym, i, j);
			}
			// else if (ft_strncmpalpha(ft_strtrim(str+all_sym[i]->st_name, "_"), ft_strtrim(str+all_sym[j]->st_name, "_"), 10000) > 0)
			else if (ft_strncmp(str+all_sym[i]->st_name, str+all_sym[j]->st_name, 10000) < 0)
				ft_swap32(all_sym, i, j);
			j++;
		}
	}
}

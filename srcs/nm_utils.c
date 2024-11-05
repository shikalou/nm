/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldinaut <ldinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 17:40:35 by ldinaut           #+#    #+#             */
/*   Updated: 2024/11/05 17:08:47 by ldinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/nm.h"

int	ft_strncmpalpha(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	while (isalpha(s1[i]) && isalpha(s2[i]) && s1[i] && i < (n - 1))
	{
		if (s1[i] != s2[i])
			return (((unsigned char *)s1)[i] - ((unsigned char *)s2)[i]);
		i++;
	}
	return (((unsigned char *)s1)[i] - ((unsigned char *)s2)[i]);
}


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

char	*trimstart(char *str)
{
	int k = 0;
	for(int i = 0; !isalnum(str[i]); ++i)
	{
		if (str[i] == '_')
			k++;
	}
	return(str+(k-1));
}

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

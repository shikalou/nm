/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldinaut <ldinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 17:40:35 by ldinaut           #+#    #+#             */
/*   Updated: 2024/11/08 14:54:54 by ldinaut          ###   ########.fr       */
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


void	ft_swap64(Elf64_Sym **strs, int i, int j)
{
	Elf64_Sym	*temp;

	temp = strs[i];
	strs[i] = strs[j];
	strs[j] = temp;
}

void	ft_swap32(Elf32_Sym **strs, int i, int j)
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

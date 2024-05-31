/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldinaut <ldinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 17:59:43 by ldinaut           #+#    #+#             */
/*   Updated: 2024/05/31 18:54:05 by ldinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/nm.h"

void	nm_32(int fd, t_data *data)
{
	(void)data;
	Elf32_Ehdr	*stock;
	struct stat	buf;
	void		*toto;

	int ret = fstat(fd, &buf);
	if (ret == -1)
		return ;
	toto = mmap(NULL, buf.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
	if (toto == MAP_FAILED)
		return ;
	stock = (Elf32_Ehdr*)toto;
}

void	nm_64(int fd, t_data *data)
{
	Elf64_Ehdr	*s_ehdr;//executable header struct
	Elf64_Shdr	*s_shdr;//section header struct
	Elf64_Sym	*s_sym; //symbols struct
	struct stat	buf;
	void		*toto;
	Elf64_Sym		**all_sym;

	int ret = fstat(fd, &buf);
	if (ret == -1)
		return ;
	toto = mmap(NULL, buf.st_size, PROT_READ, MAP_PRIVATE, fd, 0);//map les donnees recup dans le file
	if (toto == MAP_FAILED)
		return ;
	s_ehdr = (Elf64_Ehdr *)toto;
	s_shdr = (Elf64_Shdr *)(toto + s_ehdr->e_shoff);
	for (int i = 0; i < s_ehdr->e_shnum; ++i)//parser les sections
	{
		if (s_shdr[i].sh_type == SHT_SYMTAB)//type de section == table des symbols ?
		{
			int		size = s_shdr[i].sh_size / sizeof(Elf64_Sym);
			char	*str = (char *)(toto + s_shdr[s_shdr[i].sh_link].sh_offset);
			s_sym = malloc(sizeof(Elf64_Sym));
			if (!s_sym)
				return ;
			s_sym = (Elf64_Sym *)(toto + s_shdr[i].sh_offset);
			all_sym = malloc(sizeof(Elf64_Sym *) * size + 1);
			if (!all_sym)
				return ;
			for (int i = 0; i < size; ++i)
			{
				all_sym[i] = &s_sym[i];
				// if (ELF64_ST_TYPE(s_sym[i].st_info) == STT_NOTYPE)
					// printf("%s\n", str+s_sym[i].st_name);
			}
			sort_tab64(all_sym, size, str);
			
		}
	}
	(void)data;
}

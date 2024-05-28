/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldinaut <ldinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 17:59:43 by ldinaut           #+#    #+#             */
/*   Updated: 2024/05/28 18:13:53 by ldinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/nm.h"

void	print_32(int fd, t_data *data)
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

void	print_64(int fd, t_data *data)
{
	Elf64_Ehdr	*s_ehdr;
	Elf64_Shdr	*s_shdr;
	Elf64_Sym	*s_sym;
	struct stat	buf;
	void		*toto;

	int ret = fstat(fd, &buf);
	if (ret == -1)
		return ;
	toto = mmap(NULL, buf.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
	if (toto == MAP_FAILED)
		return ;
	s_ehdr = (Elf64_Ehdr*)toto;
	s_shdr = (Elf64_Shdr*)(toto + s_ehdr->e_shoff);
	for (int i = 0; i < s_ehdr->e_shnum; ++i)
	{
		if (s_shdr[i].sh_type == SHT_SYMTAB)
		{
			int size = s_shdr[i].sh_size / sizeof(Elf64_Sym);
			char	*str = (char*)(toto + ->sh_offset);
			s_sym = (Elf64_Sym *)(toto + s_shdr[i].sh_offset);
			for (int i = 0; i < size; ++i)
			{
				
			}
		}
	}
	(void)data;
}

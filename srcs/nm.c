/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldinaut <ldinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 17:59:43 by ldinaut           #+#    #+#             */
/*   Updated: 2024/06/11 17:39:02 by ldinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/nm.h"

void	nm_32(int fd, t_data *data)
{
	(void)data;
	Elf32_Ehdr	*stock;
	struct stat	buf;
	void		*toto;
	(void)stock;

	int ret = fstat(fd, &buf);
	if (ret == -1)
		return ;
	toto = mmap(NULL, buf.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
	if (toto == MAP_FAILED)
		return ;
	stock = (Elf32_Ehdr*)toto;
	(void)stock;
}

void	print_64(Elf64_Sym **all_sym, int size, char *str, Elf64_Shdr *s_shdr)
{
	for (int i = 0; i < size; ++i)
	{
		int		sym_val = all_sym[i]->st_value;
		char	*name = str+all_sym[i]->st_name;
		char	symbol = '?';
		
		if (ft_strlen(name) < 1)
			continue;
		if (ELF64_ST_TYPE(all_sym[i]->st_info) == STT_FILE)
			continue ;
		if (ELF64_ST_BIND(all_sym[i]->st_info) == STB_WEAK)
			symbol = 'w';
		else if (ELF64_ST_BIND(all_sym[i]->st_info) == STB_GNU_UNIQUE)
			symbol = 'u';
		else if (all_sym[i]->st_shndx == SHN_UNDEF)
			symbol = 'U';
		else if (all_sym[i]->st_shndx == SHN_ABS)
			symbol = 'a';
		else if (all_sym[i]->st_shndx == SHN_COMMON)
			symbol = 'c';
		else if (ELF64_ST_BIND(all_sym[i]->st_info) == STB_WEAK\
			&& ELF64_ST_TYPE(all_sym[i]->st_info) == STT_OBJECT)
			symbol = 'v';
		else if (s_shdr[all_sym[i]->st_shndx].sh_type == SHT_PROGBITS\
			&& s_shdr[all_sym[i]->st_shndx].sh_flags == (SHF_ALLOC | SHF_WRITE))
			symbol = 'd';
		else if (s_shdr[all_sym[i]->st_shndx].sh_type == SHT_PROGBITS \
			&& s_shdr[all_sym[i]->st_shndx].sh_flags == (SHF_ALLOC | SHF_EXECINSTR))
			symbol = 't';
		else if (s_shdr[all_sym[i]->st_shndx].sh_type == SHT_DYNAMIC)
			symbol = 'd';
		else if (s_shdr[all_sym[i]->st_shndx].sh_type == SHT_NOBITS)
			symbol = 'b';
		// else if (ELF64_ST_TYPE(all_sym[i]->st_info) == STT_SECTION)
		// else if (s_ehdr[all_sym[i]->st_shndx].e_flags == PF_R)
		else if ((s_shdr[all_sym[i]->st_shndx].sh_flags & SHF_ALLOC) \
			&& !(s_shdr[all_sym[i]->st_shndx].sh_flags & SHF_WRITE))
			symbol = 'r';
		if (ELF64_ST_BIND(all_sym[i]->st_info) != STB_LOCAL && symbol != '?')
			symbol = ft_toupper(symbol);
		if (sym_val)
			printf("%016x %c %s\n", sym_val, symbol, name);
		else
			printf("%16c %c %s\n", ' ', symbol, name);
	}
}

void	nm_64(int fd, t_data *data)
{
	Elf64_Ehdr	*s_ehdr;//executable header struct
	Elf64_Shdr	*s_shdr;//section header struct
	Elf64_Sym	*s_sym; //symbols struct
	struct stat	buf;
	void		*toto;
	Elf64_Sym	**all_sym;

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
				all_sym[i] = &s_sym[i];
			sort_tab64(all_sym, size, str);
			print_64(all_sym, size, str, s_shdr);
		}
	}
	(void)data;
}

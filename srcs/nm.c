/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldinaut <ldinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 17:59:43 by ldinaut           #+#    #+#             */
/*   Updated: 2024/11/05 17:55:36 by ldinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/nm.h"

void	print_32(Elf32_Sym **all_sym, int size, char *str, Elf32_Shdr *s_shdr)
{
	for (int i = 0; i < size; ++i)
	{
		int		sym_val = all_sym[i]->st_value;
		char	*name = str+all_sym[i]->st_name;
		char	symbol = '?';
		int		stb_info = ELF32_ST_BIND(all_sym[i]->st_info);
		int		stt_info = ELF32_ST_TYPE(all_sym[i]->st_info);

		
		if (ft_strlen(name) < 1)
			continue;
		if (stt_info == STT_FILE)
			continue ;
		if (stb_info == STB_WEAK)
		{
			symbol = 'W';
			if (all_sym[i]->st_shndx == SHN_UNDEF)
				symbol = 'w';
		}
		else if (stb_info == STB_GNU_UNIQUE)
			symbol = 'u';
		else if (all_sym[i]->st_shndx == SHN_UNDEF)
			symbol = 'U';
		else if (all_sym[i]->st_shndx == SHN_ABS)
			symbol = 'a';
		else if (all_sym[i]->st_shndx == SHN_COMMON)
			symbol = 'c';
		else if (stb_info == STB_WEAK && stt_info == STT_OBJECT)
			symbol = 'v';
		// else if (s_shdr[all_sym[i]->st_shndx].sh_type == SHT_PROGBITS
			// && s_shdr[all_sym[i]->st_shndx].sh_flags == (SHF_ALLOC | SHF_WRITE))
			// symbol = 'd';
		else if (stt_info == SHT_MIPS_DEBUG || s_shdr[all_sym[i]->st_shndx].sh_type == SHT_MIPS_DEBUG)
			symbol = 'n';
		else if (stt_info == STT_GNU_IFUNC)
			symbol = 'i';
		else if (s_shdr[all_sym[i]->st_shndx].sh_type == SHT_FINI_ARRAY\
			&& s_shdr[all_sym[i]->st_shndx].sh_flags == (SHF_ALLOC | SHF_WRITE))
			symbol = 't';
		else if (s_shdr[all_sym[i]->st_shndx].sh_type == SHT_INIT_ARRAY\
			&& s_shdr[all_sym[i]->st_shndx].sh_flags == (SHF_ALLOC | SHF_WRITE))
			symbol = 't';
		else if (s_shdr[all_sym[i]->st_shndx].sh_type == SHT_PROGBITS \
			&& s_shdr[all_sym[i]->st_shndx].sh_flags == (SHF_ALLOC | SHF_EXECINSTR))
			symbol = 't';
		else if (s_shdr[all_sym[i]->st_shndx].sh_type == SHT_DYNAMIC \
			|| (s_shdr[all_sym[i]->st_shndx].sh_type == SHT_PROGBITS \
			&& s_shdr[all_sym[i]->st_shndx].sh_flags == (SHF_ALLOC | SHF_WRITE)))
			symbol = 'd';
		else if (s_shdr[all_sym[i]->st_shndx].sh_type == SHT_NOBITS)
			symbol = 'b';
		// else if (ELF64_ST_TYPE(all_sym[i]->st_info) == STT_SECTION)
		// else if (s_ehdr[all_sym[i]->st_shndx].e_flags == PF_R)
		else if ((s_shdr[all_sym[i]->st_shndx].sh_flags & SHF_ALLOC) \
			&& !(s_shdr[all_sym[i]->st_shndx].sh_flags & SHF_WRITE))
			symbol = 'r';
		if (stb_info == STB_GLOBAL && symbol != 'i')
			symbol = ft_toupper(symbol);
		if (sym_val)
			printf("%08x %c %s\n", sym_val, symbol, name);
		else if (symbol == 'u' || symbol == 'U' || symbol == 'w' || symbol == 'W')
			printf("%8c %c %s\n", ' ', symbol, name);
		else
			printf("%08x %c %s\n", 0, symbol, name);
	}
}

void	nm_32(int fd, t_data *data)
{
	Elf32_Ehdr	*s_ehdr;//executable header struct
	Elf32_Shdr	*s_shdr;//section header struct
	Elf32_Sym	*s_sym; //symbols struct
	struct stat	buf;
	void		*toto;
	Elf32_Sym	**all_sym;

	int ret = fstat(fd, &buf);
	if (ret == -1)
		return ;
	toto = mmap(NULL, buf.st_size, PROT_READ, MAP_PRIVATE, fd, 0);//map les donnees recup dans le file
	if (toto == MAP_FAILED)
		return ;
	s_ehdr = (Elf32_Ehdr *)toto;
	s_shdr = (Elf32_Shdr *)(toto + s_ehdr->e_shoff);
	for (int i = 0; i < s_ehdr->e_shnum; ++i)//parser les sections
	{
		if (s_shdr[i].sh_type == SHT_SYMTAB)//type de section == table des symbols ?
		{
			int		size = s_shdr[i].sh_size / sizeof(Elf32_Sym);
			char	*str = (char *)(toto + s_shdr[s_shdr[i].sh_link].sh_offset);
			s_sym = malloc(sizeof(Elf32_Sym));
			if (!s_sym)
				return ;
			s_sym = (Elf32_Sym *)(toto + s_shdr[i].sh_offset);
			all_sym = malloc(sizeof(Elf32_Sym *) * size + 1);
			if (!all_sym)
				return ;
			for (int i = 0; i < size; ++i)
				all_sym[i] = &s_sym[i];
			sort_tab32(all_sym, size, str);
			print_32(all_sym, size, str, s_shdr);
		}
	}
	(void)data;
}


void	print_64(Elf64_Sym **all_sym, int size, char *str, Elf64_Shdr *s_shdr)
{
	for (int i = 0; i < size; ++i)
	{
		int		sym_val = all_sym[i]->st_value;
		char	*name = str+all_sym[i]->st_name;
		char	symbol = '?';
		int		stb_info = ELF64_ST_BIND(all_sym[i]->st_info);
		int		stt_info = ELF64_ST_TYPE(all_sym[i]->st_info);

		
		if (ft_strlen(name) < 1)
			continue;
		if (stt_info == STT_FILE)
			continue ;
		if (stb_info == STB_WEAK)
		{
			symbol = 'W';
			if (all_sym[i]->st_shndx == SHN_UNDEF)
				symbol = 'w';
		}
		else if (stb_info == STB_GNU_UNIQUE)
			symbol = 'u';
		else if (all_sym[i]->st_shndx == SHN_UNDEF)
			symbol = 'U';
		else if (all_sym[i]->st_shndx == SHN_ABS)
			symbol = 'a';
		else if (all_sym[i]->st_shndx == SHN_COMMON)
			symbol = 'c';
		else if (stb_info == STB_WEAK && stt_info == STT_OBJECT)
			symbol = 'v';
		else if (stt_info == STT_GNU_IFUNC)
			symbol = 'i';
		else if (s_shdr[all_sym[i]->st_shndx].sh_type == SHT_PROGBITS\
			&& s_shdr[all_sym[i]->st_shndx].sh_flags == (SHF_ALLOC | SHF_WRITE))
			symbol = 'd';
		else if (s_shdr[all_sym[i]->st_shndx].sh_type == SHT_FINI_ARRAY\
			&& s_shdr[all_sym[i]->st_shndx].sh_flags == (SHF_ALLOC | SHF_WRITE))
			symbol = 'd';
		else if (s_shdr[all_sym[i]->st_shndx].sh_type == SHT_INIT_ARRAY\
			&& s_shdr[all_sym[i]->st_shndx].sh_flags == (SHF_ALLOC | SHF_WRITE))
			symbol = 'd';
		else if (s_shdr[all_sym[i]->st_shndx].sh_type == SHT_PROGBITS \
			&& s_shdr[all_sym[i]->st_shndx].sh_flags == (SHF_ALLOC | SHF_EXECINSTR))
			symbol = 't';
		else if (s_shdr[all_sym[i]->st_shndx].sh_type == SHT_DYNAMIC \
			|| (s_shdr[all_sym[i]->st_shndx].sh_type == SHT_PROGBITS \
			&& s_shdr[all_sym[i]->st_shndx].sh_flags == (SHF_ALLOC | SHF_WRITE)))
			symbol = 'd';
		else if (s_shdr[all_sym[i]->st_shndx].sh_type == SHT_NOBITS)
			symbol = 'b';
		// else if (ELF64_ST_TYPE(all_sym[i]->st_info) == STT_SECTION)
		// else if (s_ehdr[all_sym[i]->st_shndx].e_flags == PF_R)
		else if ((s_shdr[all_sym[i]->st_shndx].sh_flags & SHF_ALLOC) \
			&& !(s_shdr[all_sym[i]->st_shndx].sh_flags & SHF_WRITE))
			symbol = 'r';
		if (stb_info == STB_GLOBAL && symbol != 'i')
			symbol = ft_toupper(symbol);
		if (sym_val)
			printf("%016x %c %s\n", sym_val, symbol, name);
		else if (symbol == 'u' || symbol == 'U' || symbol == 'w' || symbol == 'W')
			printf("%16c %c %s\n", ' ', symbol, name);
		else
			printf("%016x %c %s\n", 0, symbol, name);
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

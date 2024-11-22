/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldinaut <ldinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 17:59:43 by ldinaut           #+#    #+#             */
/*   Updated: 2024/11/22 17:40:19 by ldinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/nm.h"

void	print_32(Elf32_Sym **all_sym, int size, char *str, Elf32_Shdr *s_shdr, t_data *data, char *sections, Elf32_Shdr *text, Elf32_Ehdr *s_ehdr)
{
	if (text->sh_type == 1)
		return ;
	for (int i = 0; i < size; ++i)
	{
		int		sym_val = all_sym[i]->st_value;
		char	*name = str+all_sym[i]->st_name;
		char	symbol = '?';
		int		stb_info = ELF32_ST_BIND(all_sym[i]->st_info);
		int		stt_info = ELF32_ST_TYPE(all_sym[i]->st_info);

		if ((!name || ft_strlen(name) < 1) && !data->a)
			continue;
		if (stt_info == STT_FILE && !data->a)
			continue ;
		if (stb_info == STB_WEAK)
		{
			symbol = 'W';
			if (all_sym[i]->st_shndx == SHN_UNDEF)
				symbol = 'w';
		}
		if (data->a && all_sym[i]->st_shndx > 0 && all_sym[i]->st_shndx < s_ehdr->e_shnum)
		{
			// printf("%d et %d\n", s_shdr[all_sym[i]->st_shndx].sh_type == SHT_PROGBITS, s_shdr[all_sym[i]->st_shndx].sh_flags == (SHF_ALLOC | SHF_EXECINSTR));
			if (!(s_shdr[all_sym[i]->st_shndx].sh_type == SHT_PROGBITS 
				&& s_shdr[all_sym[i]->st_shndx].sh_flags == (SHF_ALLOC | SHF_EXECINSTR)) || stb_info != STB_GLOBAL)
			{
				char *section_name = &sections[s_shdr[all_sym[i]->st_shndx].sh_name];
				name = section_name;
			}
		}
		if (stb_info == STB_GNU_UNIQUE)
			symbol = 'u';
		else if (all_sym[i]->st_shndx == SHN_UNDEF)
			symbol = 'U';
		else if (all_sym[i]->st_shndx == SHN_ABS)
			symbol = 'a';
		else if (all_sym[i]->st_shndx == SHN_COMMON)
			symbol = 'c';
		else if (stb_info == STB_WEAK && stt_info == STT_OBJECT)
			symbol = 'v';
		else if (s_shdr[all_sym[i]->st_shndx].sh_type == SHT_NOTE \
			|| !(s_shdr[all_sym[i]->st_shndx].sh_flags & SHF_ALLOC))
			symbol = 'n';
		else if (stt_info == STT_GNU_IFUNC)
			symbol = 'i';
		else if (s_shdr[all_sym[i]->st_shndx].sh_type == SHT_PROGBITS\
			&& s_shdr[all_sym[i]->st_shndx].sh_flags == (SHF_ALLOC | SHF_WRITE))
			symbol = 'd';
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
		else if ((s_shdr[all_sym[i]->st_shndx].sh_flags & SHF_ALLOC) \
			&& !(s_shdr[all_sym[i]->st_shndx].sh_flags & SHF_WRITE))
			symbol = 'r';
		if (stb_info == STB_GLOBAL && symbol != 'i')
			symbol = ft_toupper(symbol);
		if (data->u && !(symbol == 'u' || symbol == 'U' || symbol == 'w'))
			continue ;
		if (data->g && stb_info == STB_LOCAL)
			continue ;
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
	void		*mmap_offset;
	Elf32_Sym	**all_sym;

	int ret = fstat(fd, &buf);
	if (ret == -1)
		return ;
	mmap_offset = mmap(NULL, buf.st_size, PROT_READ, MAP_PRIVATE, fd, 0);//map les donnees recup dans le file
	if (mmap_offset == MAP_FAILED)
		return ;
	s_ehdr = (Elf32_Ehdr *)mmap_offset;
	s_shdr = (Elf32_Shdr *)(mmap_offset + s_ehdr->e_shoff);
	char *sections = (char *)(mmap_offset + s_shdr[s_ehdr->e_shstrndx].sh_offset);
	for (int i = 0; i < s_ehdr->e_shnum; ++i)//parser les sections
	{
		Elf32_Shdr *text = &s_shdr[i];
		if (s_shdr[i].sh_type == SHT_SYMTAB || (data->a && s_shdr[i].sh_type == 1))//type de section == table des symbols ?
		{
			int		size = s_shdr[i].sh_size / sizeof(Elf32_Sym);
			char	*str = (char *)(mmap_offset + s_shdr[s_shdr[i].sh_link].sh_offset);
			s_sym = malloc(sizeof(Elf32_Sym));
			if (!s_sym)
				return ;
			s_sym = (Elf32_Sym *)(mmap_offset + s_shdr[i].sh_offset);
			all_sym = malloc(sizeof(Elf32_Sym *) * size + 1);
			if (!all_sym)
				return ;
			for (int i = 0; i < size; ++i)
				all_sym[i] = &s_sym[i];
			if (!data->p && s_shdr[i].sh_type != 1)
			{
				if (data->r)
					revsort_tab32(all_sym, size, str);
				else
					sort_tab32(all_sym, size, str);
			}
			print_32(all_sym, size, str, s_shdr, data, sections, text, s_ehdr);
		}
	}
}


void	print_64(Elf64_Sym **all_sym, int size, char *str, Elf64_Shdr *s_shdr, t_data *data, char *sections, Elf64_Shdr *text, Elf64_Ehdr *s_ehdr)
{
	if (text->sh_type == 1)
		return ;
	for (int i = 0; i < size; ++i)
	{
		int		sym_val = all_sym[i]->st_value;
		char	*name = str+all_sym[i]->st_name;
		char	symbol = '?';
		int		stb_info = ELF64_ST_BIND(all_sym[i]->st_info);
		int		stt_info = ELF64_ST_TYPE(all_sym[i]->st_info);

		if ((!name || ft_strlen(name) < 1) && !data->a)
			continue;
		if (stt_info == STT_FILE && !data->a)
			continue ;
		if (stb_info == STB_WEAK)
		{
			symbol = 'W';
			if (all_sym[i]->st_shndx == SHN_UNDEF)
				symbol = 'w';
		}
		if (data->a && all_sym[i]->st_shndx > 0 && all_sym[i]->st_shndx < s_ehdr->e_shnum)
		{
			// printf("%d et %d\n", s_shdr[all_sym[i]->st_shndx].sh_type == SHT_PROGBITS, s_shdr[all_sym[i]->st_shndx].sh_flags == (SHF_ALLOC | SHF_EXECINSTR));
			if (!(s_shdr[all_sym[i]->st_shndx].sh_type == SHT_PROGBITS 
				&& s_shdr[all_sym[i]->st_shndx].sh_flags == (SHF_ALLOC | SHF_EXECINSTR)) || stb_info != STB_GLOBAL)
			{
				char *section_name = &sections[s_shdr[all_sym[i]->st_shndx].sh_name];
				name = section_name;
			}
		}
		if (stb_info == STB_GNU_UNIQUE)
			symbol = 'u';
		else if (all_sym[i]->st_shndx == SHN_UNDEF)
			symbol = 'U';
		else if (all_sym[i]->st_shndx == SHN_ABS)
			symbol = 'a';
		else if (all_sym[i]->st_shndx == SHN_COMMON)
			symbol = 'c';
		else if (stb_info == STB_WEAK && stt_info == STT_OBJECT)
			symbol = 'v';
		else if (s_shdr[all_sym[i]->st_shndx].sh_type == SHT_NOTE \
			|| !(s_shdr[all_sym[i]->st_shndx].sh_flags & SHF_ALLOC))
			symbol = 'n';
		else if (stt_info == STT_GNU_IFUNC)
			symbol = 'i';
		else if (s_shdr[all_sym[i]->st_shndx].sh_type == SHT_PROGBITS\
			&& s_shdr[all_sym[i]->st_shndx].sh_flags == (SHF_ALLOC | SHF_WRITE))
			symbol = 'd';
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
		else if ((s_shdr[all_sym[i]->st_shndx].sh_flags & SHF_ALLOC) \
			&& !(s_shdr[all_sym[i]->st_shndx].sh_flags & SHF_WRITE))
			symbol = 'r';
		if (stb_info == STB_GLOBAL && symbol != 'i')
			symbol = ft_toupper(symbol);
		if (data->u && !(symbol == 'u' || symbol == 'U' || symbol == 'w'))
			continue ;
		if (data->g && stb_info == STB_LOCAL)
			continue ;
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
	void		*mmap_offset;
	Elf64_Sym	**all_sym;

	int ret = fstat(fd, &buf);
	if (ret == -1)
		return ;
	mmap_offset = mmap(NULL, buf.st_size, PROT_READ | PROT_WRITE, MAP_PRIVATE, fd, 0);//map les donnees recup dans le file
	if (mmap_offset == MAP_FAILED)
		return ;
	s_ehdr = (Elf64_Ehdr *)mmap_offset;
	s_shdr = (Elf64_Shdr *)(mmap_offset + s_ehdr->e_shoff);
	char *sections = (char *)(mmap_offset + s_shdr[s_ehdr->e_shstrndx].sh_offset);
	for (int i = 0; i < s_ehdr->e_shnum; ++i)//parser les sections
	{
		Elf64_Shdr *text = &s_shdr[i];
		if (s_shdr[i].sh_type == SHT_SYMTAB || (data->a && s_shdr[i].sh_type == 1))//type de section == table des symbols ?
		{
			int		size = s_shdr[i].sh_size / sizeof(Elf64_Sym);
			char	*str = (char *)(mmap_offset + s_shdr[s_shdr[i].sh_link].sh_offset);
			s_sym = malloc(sizeof(Elf64_Sym));
			if (!s_sym)
				return ;
			s_sym = (Elf64_Sym *)(mmap_offset + s_shdr[i].sh_offset);
			all_sym = malloc(sizeof(Elf64_Sym *) * size + 1);
			if (!all_sym)
				return ;
			for (int i = 0; i < size; ++i)
				all_sym[i] = &s_sym[i];
			if (!data->p && s_shdr[i].sh_type != 1)
			{
				if (data->r)
					revsort_tab64(all_sym, size, str);
				else
					sort_tab64(all_sym, size, str);
			}
			print_64(all_sym, size, str, s_shdr, data, sections, text, s_ehdr);
		}
	}
}

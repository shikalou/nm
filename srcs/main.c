/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldinaut <ldinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 17:43:29 by ldinaut           #+#    #+#             */
/*   Updated: 2024/11/08 16:55:58 by ldinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/nm.h"

int	check_elf(int fd)
{
	int			ret;
	void		*toto;
	Elf64_Ehdr	*sf;
	struct stat	__buf;

	ret = fstat(fd, &__buf); // pour recup la taille et whtvr(mais surtout la size)
	toto = mmap(NULL, __buf.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
	if (toto == MAP_FAILED)
		return (0);
	sf = (Elf64_Ehdr*)toto;
	ret = sf->e_ident[EI_CLASS];
	munmap(toto, __buf.st_size);
	return (ret);
}

int	main(int argc, char **argv)
{
	int		ac;
	int		nb_params;
	char	**av;
	t_data	*data;
	int		elf_t;

	av = argv + 1;
	ac = argc - 1;
	data = malloc(sizeof(t_data));
	if (!data)
		return (1);
	init_struct(data);
	nb_params = parse_params(ac, av, data);
	if (ac - nb_params == 0)
	{
		int fd = open("a.out", O_RDONLY);
		if (fd == -1)
		{
			fprintf(stderr, "nm: 'a.out': %s\n", strerror(errno));
			free_struct(data);
			return (1);
		}
		elf_t = check_elf(fd);
		if (elf_t == 1)
			nm_32(fd, data);
		else if (elf_t == 2)
			nm_64(fd, data);
		else
			fprintf(stderr, "ft_nm: a.out: file format not recognized\n");
		free_struct(data);
		return (0);
	}
	data->files = lst_init(ac, av);
	t_flst *head = data->files;
	while (head)
	{
		if (head->fd != -1)
		{
			elf_t = check_elf(head->fd);
			if (elf_t != 1 && elf_t != 2)
			{
				fprintf(stderr, "ft_nm: %s: file format not recognized\n", head->name);
				head = head->next;
				continue ;
			}
			if (ac - nb_params > 1)
				printf("\n%s:\n", head->name);
			if (elf_t == 1)
				nm_32(head->fd, data);
			else if (elf_t == 2)
				nm_64(head->fd, data);
		}
		else
			printf("nm: '%s': No such file\n", head->name);
		head = head->next;
	}
	free_struct(data);
	return (0);
}

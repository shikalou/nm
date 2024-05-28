/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldinaut <ldinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 19:13:43 by ldinaut           #+#    #+#             */
/*   Updated: 2024/05/28 16:31:29 by ldinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NM_H
#define NM_H

#include "../libft/libft.h"

#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <stdbool.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <elf.h>
#include <sys/mman.h>

typedef struct s_flst
{
	int				fd;
	char			*name;
	struct s_flst	*next;

} t_flst;

typedef struct s_data
{
	t_flst	*files;
	//bool	a;
	bool	g;
	bool	u;
	bool	r;
	bool	p;

} t_data;

/*nm trucs*/
void	print_32(int fd, t_data *data);
void	print_64(int fd, t_data *data);

/*PARSING*/
int	parse_params(int ac, char **av, t_data *data);

/*STRUCT UTILS*/
void	init_struct(t_data *data);
void	free_struct(t_data *data);

/*LIST UTILS*/
t_flst	*lst_init(t_data *data, int ac, char **av);
t_flst	*lstnew(int fd, char *name);
int		lstsize(t_flst *lst);
void	lstaddback(t_flst **alst, t_flst *new);
void	lstclear(t_flst **lst);

/*FREE FUNCTIONS*/
void	freetab(char **tab);

#endif

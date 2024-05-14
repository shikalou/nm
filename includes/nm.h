/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldinaut <ldinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 19:13:43 by ldinaut           #+#    #+#             */
/*   Updated: 2024/05/14 17:27:43 by ldinaut          ###   ########.fr       */
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

typedef struct s_flst
{
	int fd;
	char *name;
	struct s_flst *next;
} t_flst;

typedef struct s_data
{
	t_flst	files;
	//bool	a;
	bool	g;
	bool	u;
	bool	r;
	bool	p;

} t_data;

/*PARSING*/
char	**parse_params(int ac, char **av);

#endif

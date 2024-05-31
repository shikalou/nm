/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldinaut <ldinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 13:21:56 by ldinaut           #+#    #+#             */
/*   Updated: 2024/05/31 18:18:31 by ldinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/nm.h"

t_flst	*lst_init(int ac, char **av)
{
	t_flst	*begin;

	begin = lstnew(-1, NULL);

	for (int i = 0; i < ac; ++i)
	{
		if (av[i][0] != '-')
		{
			int fd = open(av[i], O_RDONLY);
			if (!begin->name)
			{
				free(begin);
				begin = lstnew(fd, ft_strdup(av[i]));
			}
			else
				lstaddback(&begin, lstnew(fd, ft_strdup(av[i])));
		}
	}
	return (begin);
}

int	lstsize(t_flst *lst)
{
	int	i;

	i = 0;
	while (lst)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}


void	lstclear(t_flst **lst)
{
	t_flst	*temp;
	t_flst	*next;

	if (!(*lst))
		return ;
	temp = *lst;
	while (temp)
	{
		free(temp->name);
		if (temp->fd > 2)
			close(temp->fd);
		next = temp->next;
		free(temp);
		temp = next;
	}
	*lst = NULL;
}

void	lstaddback(t_flst **alst, t_flst *new)
{
	t_flst	*temp;

	temp = *alst;
	if (!(*alst))
		*alst = new;
	else
	{
		while (temp->next)
			temp = temp->next;
		temp->next = new;
	}
}

t_flst	*lstnew(int fd, char *name)
{
	t_flst	*newlist;

	newlist = malloc(sizeof(t_flst));
	if (!newlist)
		return (NULL);
	newlist->fd = fd;
	newlist->name = name;
	newlist->next = NULL;
	return (newlist);
}

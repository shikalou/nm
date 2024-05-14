# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ldinaut <ldinaut@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/13 16:31:17 by ldinaut           #+#    #+#              #
#    Updated: 2024/05/14 17:41:11 by ldinaut          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	ft_nm

SRCS_FILES	=	main.c parsing.c

SRCS		=	$(addprefix srcs/, $(SRCS_FILES))

CC			=	cc

LIB			=	-Llibft -lft

CFLAGS		=	-Wall -Wextra -Werror -I./includes #-g3

OBJS_FILES	=	$(SRCS_FILES:%.c=%.o)

OBJS		=	$(addprefix objs/, $(OBJS_FILES))

DEP			=	$(OBJS:%.o=%.d)

all		:	$(NAME)

$(NAME)	:	$(OBJS)
	make -C libft
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIB)

clean	:
	make -C libft clean
	rm -rf $(OBJS) $(DEP)
	rm -rf objs/

fclean	:	clean
	make -C libft fclean
	rm -rf $(NAME)

re		:	fclean all

objs/%.o	: srcs/%.c includes/nm.h
	mkdir -p objs
	$(CC) $(CFLAGS) -MMD -o $@ -c $<

.PHONY: all clean fclean re

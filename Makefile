# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cde-moul <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/04/08 15:32:01 by cde-moul          #+#    #+#              #
#    Updated: 2019/06/24 16:18:24 by cde-moul         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			=	minishell

SRCSDIR			=	srcs

OBJSDIR			=	objs

SRCS			=	main.c \
					mini_cd.c \
					mini_env.c \
					mini_free.c \
					mini_read.c \
					mini_treat.c \
					mini_setenv.c \
					mini_getpath.c \
					mini_checkarg.c \
					mini_builtins.c \
					mini_cd_error.c

OBJS			=	$(addprefix $(OBJSDIR)/, $(SRCS:.c=.o))

CC				=	gcc -g

FLAG			=	-Wall -Wextra -Werror

INC				=	-I	libft/ -I includes/ -I libft/libft/

MY_LIB			=	libft/libft.a

HEADER			=	includes/minishell.h

LIB				=	-L libft -lft

RM				=	rm -rf

all				:	libft $(NAME)

$(NAME)			:	$(OBJS) $(MY_LIB)
					$(CC) $(FLAG) $(INC) $(OBJS)  -o $(NAME) $(LIB)

libft			:
					make -C libft/

$(OBJSDIR)/%.o	:	$(SRCSDIR)/%.c $(HEADER)
					mkdir -p $(OBJSDIR)
					$(CC) -c $(FLAG) $(INC) $< -o $@

clean			:
					$(RM) $(OBJS)
					make -C libft/ clean

fclean			:	clean
					$(RM) $(NAME)
					$(RM) $(OBJSDIR)
					make -C libft/ fclean

re				:
					make fclean
					make all

.PHONY			:	libft clean re fclean

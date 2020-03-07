# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cde-moul <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/04/08 15:32:01 by cde-moul          #+#    #+#              #
#    Updated: 2019/07/18 17:21:20 by cde-moul         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			=	minishell

SRCSDIR			=	srcs

OBJSDIR			=	objs

SRCS			=	main.c \
					mini_cd.c \
					mini_cd2.c \
					mini_env4.c \
					mini_env2.c \
					mini_env3.c \
					mini_free.c \
					mini_read.c \
					mini_treat.c \
					mini_prompt.c \
					mini_envbin.c \
					mini_setenv.c \
					mini_separg.c \
					mini_setenv2.c \
					mini_getpath.c \
					mini_envpath.c \
					mini_checkarg.c \
					mini_builtins.c \
					mini_unsetenv.c \
					mini_cd_error.c \
					mini_binaires.c \
					mini_checkdolls.c \
					mini_checkdolls2.c \
					mini_tirerror1.c \
					mini_checkarg2.c

OBJS			=	$(addprefix $(OBJSDIR)/, $(SRCS:.c=.o))

CC				=	gcc

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

# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ralves-g <ralves-g@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/26 16:26:20 by ralves-g          #+#    #+#              #
#    Updated: 2022/09/26 17:59:15 by ralves-g         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC			=	clang
CFLAGS		=	-Wall -Wextra -Werror -fsanitize=address -g
RM			=	rm -f

NAME		=	shell

INCLUDE		=	-I ./ -I ~/brew/opt/readline/include -lreadline 

SRCS_		=	\
				minishell.c \
				env.c \
				errors_and_frees.c \
				errors_and_frees2.c \
				testing_prints.c \
				path.c \
				signal_handle.c \
				\
				executor/executor.c \
				executor/executor_prep.c \
				executor/executor_prep2.c \
				\
				libs/lib.c \
				libs/lib2.c \
				libs/split_join.c \
				\
				parser/parse_pipes.c \
				parser/parser_utils.c \
				parser/parser.c \
				parser/quotes.c \
				parser/treat_dollar.c \
				parser/treat_dollar2.c \
				parser/treat_dollar3.c \
				parser/tree_creation.c \
				parser/backslash.c \
				\
				redirections/redirections.c \
				redirections/heredoc.c

SRCS		=	$(addprefix $(_SRC), $(SRCS_))

_OBJ		=
_SRC		=	./src/
_EXEC		=	executor/
_LIBS		=	libs/
_PARSER		=	parser/
# OBJS		=	$(patsubst $(_SRC)%.c, $(_OBJ)%.o, $(SRCS))
OBJS		=	$(patsubst %.c, %.o, $(SRCS))
all:		$(NAME)

$(_OBJ)%.o: $(_SRC)%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(_OBJ) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(INCLUDE)

#bonus:		$(SRCS_B) $(OBJS_B)
#			$(CC) $(CFLAGS) $(SRCS_B) -o $(NAME_B)
#			$(CC) $(CFLAGS) $(SRCS_B) -c

$(_OBJ):
	mkdir $@

clean:
	$(RM) -r $(OBJS)

fclean:	clean
	$(RM) $(NAME)

re:	fclean all

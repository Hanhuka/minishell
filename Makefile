# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ralves-g <ralves-g@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/26 16:26:20 by ralves-g          #+#    #+#              #
#    Updated: 2022/07/28 11:27:02 by ralves-g         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC			=	gcc
CFLAGS		=	-Wall -Wextra -Werror 
RM			=	rm -f

NAME		=	shell

INCLUDE		=	-I ./ 
#-I ~/brew/opt/readline/include -lreadline

SRCS_		=	\
				minishell.c

SRCS		=	$(addprefix $(_SRC), $(SRCS_))

_OBJ		=	./obj/
_SRC		= 	./src/
OBJS		=	$(patsubst $(_SRC)%.c, $(_OBJ)%.o, $(SRCS))

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
	$(RM) -r $(_OBJ)

fclean:	clean
	$(RM) $(NAME)

re:	fclean all

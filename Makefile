# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jdefayes <jdefayes@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/17 22:32:36 by jdefayes          #+#    #+#              #
#    Updated: 2023/05/06 13:09:45 by jdefayes         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

##########################################
##NAME
NAME	= pipex

##########################################
##SOURCES
SRC	=	main.c\
		pipex.c\
		utils.c\
		split.c\
		handle_errors.c\
		init.c\
		handle_process.c\
		handle_leaks.c\

FLAGS	= -Wall -Werror -Wextra -g
CC		= gcc
OBJ	= ${SRC:.c=.o}
RM		= rm -f

##########################################
##RULES
all: $(NAME)

.c.o:
	$(CC) $(FLAGS) -c $< -o $(<:.c=.o)

$(NAME): $(OBJ)
	$(CC) $(FLAGS) $(OBJ) -o $(NAME)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all re clean fclean .c.o

# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jdefayes <jdefayes@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/17 22:32:36 by jdefayes          #+#    #+#              #
#    Updated: 2023/05/07 11:42:57 by jdefayes         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

##########################################
##NAME
NAME	= pipex

##########################################
##SOURCES
SRC			=	main.c\
				pipex.c\
				utils.c\
				split.c\
				handle_errors.c\
				init.c\
				handle_process.c\
				handle_leaks.c\

BONUS		=	pipex_bonus.c\
				utils_bonus.c\
				split_bonus.c\
				handle_errors_bonus.c\
				init_bonus.c\
				handle_process_bonus.c\
				handle_leaks_bonus.c\

FLAGS		= -Wall -Werror -Wextra -g
CC			= gcc
OBJ			= ${SRC:.c=.o}
BONUS_OBJ	= ${BONUS:.c=.o}
RM			= rm -f

##########################################
##RULES
all: $(NAME)

#bonus: $(BONUS_OBJ) $(OBJS)
#	ar rcs $(NAME) $(OBJS) $(BONUS_OBJ)

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

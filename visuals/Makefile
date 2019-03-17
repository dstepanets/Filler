# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dstepane <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/03/16 12:29:38 by dstepane          #+#    #+#              #
#    Updated: 2019/03/16 12:29:41 by dstepane         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = visualizer
CC = gcc
FLAGS = -g -Wall -Wextra -Werror###debugging FLAG -g! Don't foreget libft too!!!!
HEAD = visuals.h
SRC = 	visuals.c \
		../purgatory.c 

OBJS = $(SRC:.c=.o)

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(FLAGS) $(OBJS) ../libft/libft.a -o $(NAME)
	@echo "\033[35m\033[43mFiller visualizer compiled.\033[0m\033[49m"
##	make clean

$(OBJS):
	@$(CC) $(FLAGS) -c $(SRC)
	@echo "\033[35mFiller visualizer object files compiled.\033[0m"
	@mv purgatory.o ../purgatory.o

clean:
	@rm -f $(OBJS)
	@echo "\033[31mFiller visualizer object files removed.\033[0m"

fclean: clean
	@rm -f $(NAME)
	@echo "\033[31mFiller visualizer executable removed.\033[0m"

re: fclean all

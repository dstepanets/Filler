# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dstepane <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/03/02 17:27:03 by dstepane          #+#    #+#              #
#    Updated: 2019/03/02 17:27:05 by dstepane         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = dstepane.filler
CC = gcc
FLAGS = -Wall -Wextra -Werror
HEAD = ./filler.h
SRC = 	main.c \
		parser.c \
		purgatory.c \
		heat_map.c \
		algorithm.c
OBJS = $(SRC:.c=.o)
LIBFT = libft/libft.a
VISUALS = visuals/visualizer

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(LIBFT) $(OBJS) $(VISUALS)
	@$(CC) $(FLAGS) $(OBJS) $(LIBFT) -o $(NAME)
	@echo "\033[32m\033[100mFiller executable compiled.\033[0m\033[49m"

$(LIBFT):
	@make -C libft

$(VISUALS):
	@make -C visuals

$(OBJS):
	@$(CC) $(FLAGS) -c $(SRC)
	@echo "\033[32mFiller object files compiled.\033[0m"

clean:
	@rm -f $(OBJS)
	@make clean -C libft
	@make clean -C visuals
	@echo "\033[31mFiller object files removed.\033[0m"

fclean: clean
	@rm -f $(NAME)
	@make fclean -C libft
	@make fclean -C visuals
	@echo "\033[31mFiller executable removed.\033[0m"

re: fclean all

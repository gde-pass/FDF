# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gde-pass <gde-pass@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/04/05 15:55:59 by gde-pass          #+#    #+#              #
#    Updated: 2018/04/05 16:23:30 by gde-pass         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fdf

FLAGS = -Werror -Wall -Wextra

FLAGSLIBX = -lmlx -framework OpenGL -framework AppKit

LIB = includes/libft/

INC = includes/fdf.h

LIBA = includes/libft/libft.a

SRC = src/main.c \
	  src/drawer.c \
	  src/parser.c \
	  src/checker.c \
	  src/signals.c \

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	@make -C $(LIB)
	@gcc -o $(NAME) $(LIBA) $(SRC) $(FLAGS) $(FLAGSLIBX)
	@make clean
	@echo "\033[92m[FDF	BUILD]\033[0m"

%.o: %.c
	@gcc  $(FLAGS) -o $@ -c $<

clean:
	@make -C $(LIB) clean
	@rm -f $(OBJ)

fclean: clean
	@make -C $(LIB) fclean
	@rm -f $(NAME)

re: fclean all

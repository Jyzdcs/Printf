# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kclaudan <kclaudan@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/15 16:10:04 by kclaudan          #+#    #+#              #
#    Updated: 2024/11/15 16:10:04 by kclaudan         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS = ./print.c ./hex_printer.c ./ft_printf.c
OBJ = $(SRCS:.c=.o)

CC = cc

FLAGS = -Werror -Wetra -Wall

AR = ar -rcs

NAME = libftprintf.a

$(NAME): $(OBJ)
	$(AR) $(NAME) $(OBJ)

all: $(NAME)

.c.o:
	$(CC) $(CFLAGS) -c $< -o ${<:.c=.o}

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all
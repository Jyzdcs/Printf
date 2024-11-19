SRCS = ./print.c ./hex_printer.c ./ft_printf.c
OBJ = $(SRCS:.c=.o)

CC = cc

FLAGS = -Werror -Wetra -Wall

AR = ar -rc

NAME = libftprintf.a

$(NAME): $(OBJ)
	$(AR) $(NAME) $(OBJ)

all: $(NAME)

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all
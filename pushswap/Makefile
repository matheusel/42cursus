NAME = push_swap

CC = cc

RM = rm -fr

FLAG = -Wall -Wextra -Werror

SRC = push_swap.c \
		source/

OBJS = $(SRC:.c=.o)

all: $(NAME)

.c.o:
	$(CC) $(FLAG) -c $< -o $@

$(NAME) : $(OBJS) libs/printf/libftprintf.a libs/libft/libft.a
	$(CC) $(FLAG) $(OBJS) libs/printf/libftprintf.a libs/libft/libft.a -o $(NAME)

libs/printf/libftprintf.a:
	make -C libs/printf

libs/libft/libft.a:
	make -C libs/libft

clean:
	make -C libs/printf fclean
	make -C libs/libft fclean
	$(RM) $(OBJS)

fclean: clean
	make -C libs/printf fclean
	make -C libs/libft fclean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
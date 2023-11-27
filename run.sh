cc -Wall -Wextra -Werror -D BUFF_SIZE=50 *.c ft_printf/libftprintf.a && valgrind --leak-check=full ./a.out

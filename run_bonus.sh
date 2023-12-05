cc -Wall -Wextra -Werror -D BUFF_SIZE=$1 get_next_line_bonus.c get_next_line_utils_bonus.c main.c -I ./ ft_printf/libftprintf.a && valgrind --leak-check=full ./a.out

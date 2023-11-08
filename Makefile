### COMPILATION ###
CC = gcc
CFLAGS = -Wall -Wextra -Werror

### INCLUDES ###
PROJECT = libftprintf.a
PROJECT_DIR = ./

### SOURCE FILES ###
SRC_FILE = ft_print_char.c ft_print_str.c ft_print_uint.c ft_print_int.c \
			ft_print_hexlow.c ft_print_hexup.c ft_print_addr.c ft_printf.c
BONUS_FILE =
### HEADER FILE ###
HEADER_DIR = ./
HEADER_FILE = ft_printf.h
## OBJECT FILE ###
OBJ_FILE = $(SRC_FILE:.c=.o)
BONUS_OBJ = $(BONUS_FILE:.c=.o)

### RULES ###
all : $(PROJECT)

$(PROJECT) : $(OBJ_FILE)
	ar rc $(PROJECT) $(OBJ_FILE)

%.o : %.c $(HEADER_FILE)
	$(CC) $(CFLAGS) -I $(HEADER_DIR) -c $< -o $@

bonus : $(OBJ_FIL) $(BONUS_OBJ)
	ar rc $(PROJECT) $(OBJ_FILE) $(BONUS_OBJ)

fclean : clean
	rm -f $(PROJECT)

#Suppresion des fichiers objet
clean :
	rm -f *.o

re : fclean all

so : 
	$(CC) -nostartfiles -fPIC $(CFLAGS) -c $(SRC_FILE) $(BONUS_FILE) -I $(HEADER_DIR)
	gcc -nostartfiles -shared -o libft.so $(OBJ_FILE) $(BONUS_OBJ)

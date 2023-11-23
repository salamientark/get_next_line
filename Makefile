### COMPILATION ###
CC = gcc
CFLAGS = -Wall -Wextra -Werror

### FT_PRINTF ###
FT_PRINTF = libftprintf.a
FT_PRINTF_DIR = ./ft_printf


MAIN = main.out
### SOURCE FILES ###
SRC_FILE = get_next_line.c get_next_line_utils.c \
			testing.c main.c
BONUS_FILE =
### HEADER FILE ###
INCLUDE_DIR = ./
INCLUDE_FILE = ft_printf.h
## OBJECT FILE ###
OBJ_FILE = $(SRC_FILE:.c=.o)
BONUS_OBJ = $(BONUS_FILE:.c=.o)

### RULES ###
all : $(MAIN)

$(MAIN) : $(OBJ_FILE) $(FT_PRINTF)
	$(CC) $(CFLAGS) $(OBJ_FILE) -I $(INCLUDE_DIR) $(FT_PRINTF_DIR)/$(FT_PRINTF) -o $(MAIN)

%.o : %.c $(INCLUDE_FILE)
	$(CC) $(CFLAGS) -I $(INCLUDE_DIR) -c $< -o $@

$(FT_PRINTF) :
	make -C $(FT_PRINTF_DIR)/

fclean : clean
	rm -f $(PROJECT)

#Suppresion des fichiers objet
clean :
	rm -f *.o

re : fclean all

so : 
	$(CC) -nostartfiles -fPIC $(CFLAGS) -c $(SRC_FILE) $(BONUS_FILE) -I $(INCLUDE_DIR)
	gcc -nostartfiles -shared -o libft.so $(OBJ_FILE) $(BONUS_OBJ)

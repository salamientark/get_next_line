### COMPILATION ###
CC = clang
CFLAGS = -Wall -Wextra -Werror

### INCLUDES ###
PROJECT = libftprintf.a
PROJECT_DIR = ./

### SOURCE FILES ###
SRC_FILE = print_c.c print_s.c print_u.c print_i.c \
			print_x.c print_xup.c print_p.c ft_printf.c \
			ft_printf_opt.c flags.c printf_utils.c

BONUS_FILE =
### HEADER FILE ###
HEADER_DIR = ./
#HEADER_FILE = ft_printf.h
## OBJECT FILE ###
OBJ_FILE = $(SRC_FILE:.c=.o)
BONUS_OBJ = $(BONUS_FILE:.c=.o)

### RULES ###
all : $(PROJECT)

$(PROJECT) : $(OBJ_FILE)
	ar rc $(PROJECT) $(OBJ_FILE)

%.o : %.c $(HEADER_FILE)
	$(CC) $(CFLAGS) -I $(HEADER_DIR) -c $< -o $@

bonus : $ all

fclean : clean
	rm -f $(PROJECT)

#Suppresion des fichiers objet
clean :
	rm -f *.o

re : fclean all
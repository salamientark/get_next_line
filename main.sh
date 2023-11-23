#!/bin/sh

make -C ft_printf/
cc -Wall -Wextra -Werror *.c -I ./ ft_printf/libftprintf.a

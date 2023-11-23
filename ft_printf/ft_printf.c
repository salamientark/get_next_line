/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaladro <dbaladro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 12:08:21 by dbaladro          #+#    #+#             */
/*   Updated: 2023/11/17 13:41:53 by dbaladro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

// void	printOptions(t_option opt)
// {
// 	printf(">>>>>   Option  <<<<<\n");
// 	printf("> Flags:\n");
// 	printf("\tpadding:  %d\n", opt.flags.rpadding);
// 	printf("\tsign:     %d\n", opt.flags.sign);
// 	printf("\tspace:    %d\n", opt.flags.space);
// 	printf("\thashtag:  %d\n", opt.flags.hashtag);
// 	printf("\tzero:     %d\n", opt.flags.zero);
// 	printf("\tset_prec: %d\n", opt.flags.set_precision);
// 	printf("> Width:     %d\n", opt.width);
// 	printf("> Precision: %d\n", opt.precision);
// 	printf("> Specifier: %c\n", opt.specifier);
// 	printf("Format len: %lu\n\n", opt.len);
// }

static int	ft_printf_format(const char *str, int *pos, va_list arg)
{
	t_option	opt;
	int			success;

	*pos += 1;
	opt = make_option(str + *pos);
	success = -1;
	if (opt.specifier == 'c')
		success = (print_char_opt(va_arg(arg, int), opt));
	if (opt.specifier == 's')
		success = print_str_opt(va_arg(arg, char *), opt);
	if (opt.specifier == 'd' || opt.specifier == 'i')
		success = print_int_opt(va_arg(arg, int), opt);
	if (opt.specifier == 'u')
		success = (print_uint_opt(va_arg(arg, unsigned int), opt));
	if (opt.specifier == 'x')
		success = (printf_xlow_opt(va_arg(arg, int), opt));
	if (opt.specifier == 'X')
		success = (print_xup_opt(va_arg(arg, int), opt));
	if (opt.specifier == 'p')
		success = (print_p_opt(va_arg(arg, void *), opt));
	if (opt.specifier == '%')
		success = (print_char('%'));
	*pos += (opt.len + 1);
	return (success);
}

int	ft_printf(const char *s, ...)
{
	va_list	ap;
	int		printed_char;
	int		success;
	char	*s_cp;
	int		pos;

	va_start(ap, s);
	printed_char = 0;
	s_cp = (char *)s;
	pos = 0;
	while (s_cp[pos])
	{
		if (s_cp[pos] == '%')
			success = ft_printf_format(s_cp, &pos, ap);
		else
		{
			success = print_char(s_cp[pos]);
			pos++;
		}
		if (success == -1)
			return (success);
		printed_char += success;
	}
	va_end(ap);
	return (printed_char);
}

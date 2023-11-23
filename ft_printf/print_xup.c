/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_xup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaladro <dbaladro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 14:46:44 by dbaladro          #+#    #+#             */
/*   Updated: 2023/11/18 18:21:23 by dbaladro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static t_bool	check_option_hexup(t_option opt)
{
	if (opt.flags.sign != 0)
		return (FALSE);
	if (opt.flags.space != 0)
		return (FALSE);
	if (opt.flags.rpadding != 0 && opt.flags.zero != 0)
		return (FALSE);
	return (TRUE);
}

static void	init_width_precision(int *width, int *precision, long n,
	t_option opt)
{
	int	n_len;

	n_len = nbr_base_len((long long) n, 16);
	*precision = opt.precision - n_len;
	if (*precision < 0)
		*precision = 0;
	*width = opt.width - (n_len + *precision);
	if (n != 0)
		*width = *width - (2 * opt.flags.hashtag);
	if (*width < 0)
		*width = 0;
}

static int	print_hexdup_r(unsigned int n)
{
	if (n)
	{
		if (n % 16 > 9)
			return (print_hexdup_r(n / 16) + print_char(n % 16 + 'A' - 10));
		else
			return (print_hexdup_r(n / 16) + print_char(n % 16 + '0'));
	}
	return (0);
}

static int	print_xup(int n)
{
	if (n == 0)
		return (print_char('0'));
	return (print_hexdup_r((unsigned int)n));
}

int	print_xup_opt(unsigned int n, t_option opt)
{
	int		padding;
	int		precision;
	int		printed_char;

	if (check_option_hexup(opt) == FALSE)
		return (-1);
	if (opt.flags.zero == 1 && opt.precision > 0)
		opt.flags.zero = 0;
	init_width_precision(& padding, &precision, n, opt);
	printed_char = padding + precision;
	if (opt.flags.rpadding == 0 && opt.flags.zero == 0)
		putnchar(' ', padding);
	if (opt.flags.hashtag == 1 && n != 0)
		printed_char += print_str("0X");
	if (opt.flags.rpadding == 0 && opt.flags.zero == 1)
		putnchar('0', padding);
	putnchar('0', precision);
	if (!(n == 0 && opt.flags.set_precision == 1 && opt.precision == 0
			&& opt.width == 0))
		printed_char += print_xup(n);
	if (opt.flags.rpadding == 1)
		putnchar(' ', padding);
	return (printed_char);
}

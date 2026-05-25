/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_hex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: milsonyujiaoki <dev-yuji@student.42.sp>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/21 10:43:41 by milsonyujiaoki    #+#    #+#             */
/*   Updated: 2026/05/21 10:44:19 by milsonyujiaoki   ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ft_printf.h"

static int	put_chars(char c, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		put_char_len(c);
		i++;
	}
	return (count);
}

// Calcula quantos dígitos o número hexadecimal vai ocupar
static int	get_hex_digits(unsigned int n)
{
	int	digits;

	if (n == 0)
		return (1);
	digits = 0;
	while (n > 0)
	{
		digits++;
		n /= 16;
	}
	return (digits);
}

// Imprime o número hexadecimal puro (sem retornos internos complexos)
static void	put_hex_pure(unsigned int n, const char *base)
{
	if (n >= 16)
		put_hex_pure(n / 16, base);
	put_char_len(base[n % 16]);
}

int	print_hex(t_format *fmt, va_list args)
{
	unsigned int	n;
	const char		*base;
	int				digits;
	int				zeros;
	int				total_len;
	int				count;

	n = va_arg(args, unsigned int);
	base = (fmt->specifier == SP_HEX_UP) ? "0123456789ABCDEF" : "0123456789abcdef";
	digits = get_hex_digits(n);
	if (fmt->precision == 0 && n == 0)
		digits = 0;
	zeros = 0;
	if (fmt->precision > digits)
		zeros = fmt->precision - digits;
	total_len = digits + zeros;
	count = 0;
	if (!fmt->left_align && fmt->width > total_len)
		count += put_chars(' ', fmt->width - total_len);
	if (zeros > 0)
		put_chars('0', zeros);
	if (digits > 0)
		put_hex_pure(n, base);
	if (fmt->left_align && fmt->width > total_len)
		count += put_chars(' ', fmt->width - total_len);
	return (count + total_len);
}

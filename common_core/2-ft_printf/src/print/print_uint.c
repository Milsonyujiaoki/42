/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_uint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: milsonyujiaoki <dev-yuji@student.42.sp>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/21 10:41:21 by milsonyujiaoki    #+#    #+#             */
/*   Updated: 2026/05/21 10:41:51 by milsonyujiaoki   ###   ########.fr       */
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

// Calcula quantos dígitos o número unsigned vai ocupar
static int	get_uint_digits(unsigned int n)
{
	int	digits;

	if (n == 0)
		return (1);
	digits = 0;
	while (n > 0)
	{
		digits++;
		n /= 10;
	}
	return (digits);
}

// Imprime o número puro sem recursão complexa no retorno
static void	put_uint_pure(unsigned int n)
{
	if (n >= 10)
		put_uint_pure(n / 10);
	put_char_len((n % 10) + '0');
}

int	print_uint(t_format *fmt, va_list args)
{
	unsigned int	n;
	int				digits;
	int				zeros;
	int				total_len;
	int				count;

	n = va_arg(args, unsigned int);
	digits = get_uint_digits(n);
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
		count += put_chars('0', zeros);
	if (digits > 0)
		put_uint_pure(n);
	if (fmt->left_align && fmt->width > total_len)
		count += put_chars(' ', fmt->width - total_len);
	return (count + total_len);
}

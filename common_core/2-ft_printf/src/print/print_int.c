/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_int.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: milsonyujiaoki <dev-yuji@student.42.sp>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/21 10:39:32 by milsonyujiaoki    #+#    #+#             */
/*   Updated: 2026/05/21 10:40:20 by milsonyujiaoki   ###   ########.fr       */
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

static unsigned int	get_abs_and_digits(int n, int *digits)
{
	unsigned int	num;
	unsigned int	temp;

	if (n < 0)
		num = (unsigned int)-n;
	else
		num = (unsigned int)n;
	*digits = 0;
	if (num == 0)
		*digits = 1;
	else
	{
		temp = num;
		while (temp > 0)
		{
			(*digits)++;
			temp /= 10;
		}
	}
	return (num);
}

static void	put_nbr_pure(unsigned int n)
{
	if (n >= 10)
		put_nbr_pure(n / 10);
	put_char_len((n % 10) + '0');
}

int	print_int(t_format *fmt, va_list args)
{
	int				n;
	unsigned int	num;
	int				digits;
	int				zeros;
	int				total_len;
	int				count;

	n = va_arg(args, int);
	num = get_abs_and_digits(n, &digits);
	if (fmt->precision == 0 && n == 0)
		digits = 0;
	zeros = 0;
	if (fmt->precision > digits)
		zeros = fmt->precision - digits;
	total_len = digits + zeros;
	if (n < 0)
		total_len++;
	count = 0;
	if (!fmt->left_align && fmt->width > total_len)
		count += put_chars(' ', fmt->width - total_len);
	if (n < 0)
		put_char_len('-');
	if (zeros > 0)
		put_chars('0', zeros);
	if (digits > 0)
		put_nbr_pure(num);
	if (fmt->left_align && fmt->width > total_len)
		count += put_chars(' ', fmt->width - total_len);
	return (count + total_len);
}

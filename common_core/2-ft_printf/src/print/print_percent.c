/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_percent.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: milsonyujiaoki <dev-yuji@student.42.sp>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/21 10:42:48 by milsonyujiaoki    #+#    #+#             */
/*   Updated: 2026/05/21 10:43:23 by milsonyujiaoki   ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ft_printf.h"

static int	put_spaces(int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		put_char_len(' ');
		i++;
	}
	return (count);
}

int	print_percent(t_format *fmt, va_list args)
{
	int	count;

	(void)args;
	count = 0;
	if (!fmt->left_align && fmt->width > 1)
		count += put_spaces(fmt->width - 1);
	put_char_len('%');
	count++;
	if (fmt->left_align && fmt->width > 1)
		count += put_spaces(fmt->width - 1);
	return (count);
}

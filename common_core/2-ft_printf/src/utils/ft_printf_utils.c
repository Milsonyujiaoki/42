/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: milsonyujiaoki <dev-yuji@student.42.sp>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/21 09:37:27 by milsonyujiaoki    #+#    #+#             */
/*   Updated: 2026/05/21 09:47:42 by milsonyujiaoki   ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ft_printf.h"
#include <unistd.h>

int	put_char_len(char c)
{
	return (write(1, &c, 1));
}

int	put_str_len(const char *str, int precision)
{
	int	len;

	if (!str)
		str = "(null)";
	len = 0;
	while (str[len] && (precision < 0 || len < precision))
	{
		len += put_char_len(str[len]);
	}
	return (len);
}

int	putnbr_base_len(uintptr_t n, const char *base)
{
	int	len;
	int	base_len;

	base_len = (int)ft_strlen(base);
	len = 0;
	if (n >= (uintptr_t)base_len)
		len += putnbr_base_len(n / base_len, base);
	len += put_char_len(base[n % base_len]);
	return (len);
}

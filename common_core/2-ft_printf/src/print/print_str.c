/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_str.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: milsonyujiaoki <dev-yuji@student.42.sp>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/21 10:38:41 by milsonyujiaoki    #+#    #+#             */
/*   Updated: 2026/05/21 10:38:43 by milsonyujiaoki   ###   ########.fr       */
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

int	print_str(t_format *fmt, va_list args)
{
	char *str;
	int len;
	int count;

	str = va_arg(args, char *);
	if (!str)
	{
		// Se foi passada precisão menor que 6, não imprime o "(null)"
		if (fmt->precision >= 0 && fmt->precision < 6)
			str = "";
		else
			str = "(null)";
	}
	// Calcula tamanho real da string
	len = 0;
	while (str[len])
		len++;
	// Se a precisão for válida e menor que a string, limita o tamanho
	if (fmt->precision >= 0 && fmt->precision < len)
		len = fmt->precision;
	count = 0;
	// Alinhamento à direita (padrão)
	if (!fmt->left_align && fmt->width > len)
		count += put_spaces(fmt->width - len);
	// Imprime os caracteres calculados
	put_str_len(str, len);
	count += len;
	// Alinhamento à esquerda (flag '-')
	if (fmt->left_align && fmt->width > len)
		count += put_spaces(fmt->width - len);
	return (count);
}

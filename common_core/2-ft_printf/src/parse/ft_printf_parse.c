/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_parse.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: milsonyujiaoki <dev-yuji@student.42.sp>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/21 09:44:56 by milsonyujiaoki    #+#    #+#             */
/*   Updated: 2026/05/21 10:33:13 by milsonyujiaoki   ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ft_printf.h"

void	par_prec(const char *fmt, int *i, t_format *format,
		va_list args)
{
	if (fmt[*i] == '.')
	{
		(*i)++;
		format->precision = 0;
		if (fmt[*i] == '*')
		{
			format->precision = va_arg(args, int);
			(*i)++;
		}
		else
		{
			while (ft_isdigit(fmt[*i]))
			{
				format->precision = format->precision * 10 + (fmt[*i] - '0');
				(*i)++;
			}
		}
	}
}

void	par_specifier(const char *fmt, int *i, t_format *format)
{
	if (ft_strchr("cspdiuxX%", fmt[*i]))
		format->specifier = fmt[(*i)++];
}

void	par_flags(const char *fmt, int *i, t_format *format)
{
	while (fmt[*i] == '0' || fmt[*i] == '-' || fmt[*i] == '+' || fmt[*i] == ' '
		|| fmt[*i] == '#')
	{
		if (fmt[*i] == '0')
			format->zero = 1;
		else if (fmt[*i] == '-')
			format->left_align = 1;
		else if (fmt[*i] == '+')
			format->plus = 1;
		else if (fmt[*i] == ' ')
			format->space = 1;
		else if (fmt[*i] == '#')
			format->hash = 1;
		(*i)++;
	}
}

void	par_width(const char *fmt, int *i, t_format *format, va_list args)
{
	if (fmt[*i] == '*')
	{
		format->width = va_arg(args, int);
		(*i)++;
	}
	else
	{
		while (ft_isdigit(fmt[*i]))
		{
			format->width = format->width * 10 + (fmt[*i] - '0');
			(*i)++;
		}
	}
}

int	handle_format(const char *fmt, int *i, va_list args)
{
	t_format	format;

	init_format(&format);
	par_flags(fmt, i, &format);
	par_width(fmt, i, &format, args);
	par_prec(fmt, i, &format, args);
	par_specifier(fmt, i, &format);
	return (dispatch(&format, args));
}

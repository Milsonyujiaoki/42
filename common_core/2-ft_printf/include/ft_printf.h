/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: milsonyujiaoki <dev-yuji@student.42.sp>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/21 10:04:05 by milsonyujiaoki    #+#    #+#             */
/*   Updated: 2026/05/21 10:42:14 by milsonyujiaoki   ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "../lib/libft.h"
# include <limits.h>
# include <stdarg.h>
# include <stddef.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_format
{
	char	specifier;
	int		width;
	int		precision;
	int		zero;
	int		left_align;
	int		plus;
	int		space;
	int		hash;
}			t_format;

typedef struct s_dispatch
{
	char	specifier;
	int		(*fn)(t_format *, va_list);
}			t_dispatch;

typedef enum e_specifier
{
	SP_CHAR = 'c',
	SP_STR = 's',
	SP_PTR = 'p',
	SP_DEC = 'd',
	SP_INT = 'i',
	SP_UINT = 'u',
	SP_HEX_LOW = 'x',
	SP_HEX_UP = 'X',
	SP_PERCENT = '%'
}			t_specifier;

/* core */
int			ft_printf(const char *fmt, ...);

/* conversions — internal */
int			print_char(t_format *fmt, va_list args);
int			print_str(t_format *fmt, va_list args);
int			print_int(t_format *fmt, va_list args);
int			print_uint(t_format *fmt, va_list args);
int			print_hex(t_format *fmt, va_list args);
int			print_ptr(t_format *fmt, va_list args);
int			print_percent(t_format *fmt, va_list args);

/* utils */

int			put_char_len(char c);
int			put_str_len(const char *str, int precision);
int			putnbr_base_len(uintptr_t n, const char *base);

/* FUNCTIONS */

int			dispatch(t_format *fmt, va_list args);

int			handle_format(const char *fmt, int *i, va_list args);

void		init_format(t_format *format);
void		par_prec(const char *fmt, int *i, t_format *format, va_list args);
void		par_specifier(const char *fmt, int *i, t_format *format);
void		par_flags(const char *fmt, int *i, t_format *format);
void		par_width(const char *fmt, int *i, t_format *format, va_list args);

#endif

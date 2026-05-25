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

// Calcula quantos caracteres o endereço hexadecimal vai ocupar (sem contar o "0x")
static int	get_addr_digits(unsigned long n)
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

// Imprime o endereço puramente em hexadecimal minúsculo
static void	put_addr_pure(unsigned long n)
{
	if (n >= 16)
		put_addr_pure(n / 16);
	put_char_len("0123456789abcdef"[n % 16]);
}

int	print_ptr(t_format *fmt, va_list args)
{
	unsigned long	addr;
	int				digits;
	int				total_len;
	int				count;

	addr = (unsigned long)va_arg(args, void *);
	
	// 1. Calcula o tamanho total que a impressão vai ocupar
	if (addr == 0)
		total_len = 5; // Tamanho de "(nil)"
	else
	{
		digits = get_addr_digits(addr);
		total_len = digits + 2; // Dígitos + tamanho do prefixo "0x"
	}

	count = 0;
	// 2. Largura à direita: Adiciona espaços ANTES se não houver alinhamento à esquerda
	if (!fmt->left_align && fmt->width > total_len)
		count += put_chars(' ', fmt->width - total_len);

	// 3. Imprime o conteúdo de fato
	if (addr == 0)
		put_str_len("(nil)", 5);
	else
	{
		put_str_len("0x", 2);
		put_addr_pure(addr);
	}

	// 4. Largura à esquerda: Adiciona espaços DEPOIS se a flag '-' estiver ativa
	if (fmt->left_align && fmt->width > total_len)
		count += put_chars(' ', fmt->width - total_len);

	return (count + total_len);
}
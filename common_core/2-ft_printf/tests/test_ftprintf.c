#include "../include/ft_printf.h"
#include <limits.h>
#include <stdio.h>

static int	g_pass = 0;
static int	g_fail = 0;

static void	check(const char *label, int got, int expected)
{
	/* Usamos o printf ORIGINAL aqui para não mascarar erros da ft_printf */
	if (got == expected)
	{
		printf("  [PASS] %-30s ret=%d\n", label, got);
		g_pass++;
	}
	else
	{
		printf("  [FAIL] %-30s got=%d expected=%d\n",
			label, got, expected);
		g_fail++;
	}
}

int	main(void)
{
	int	r1;
	int	r2;
	int	x;

	ft_printf("=== ft_printf vs printf ===\n\n");

	/* plain string */
	ft_printf("--- Plain String ---\n");
	r2 = printf("hello world\n");
	r1 = ft_printf("hello world\n");
	check("plain string", r1, r2);

	/* %% */
	ft_printf("\n--- Percent Sign (%%) ---\n");
	r2 = printf("100%%\n");
	r1 = ft_printf("100%%\n");
	check("%%", r1, r2);

	r2 = printf("%%%%\n");
	r1 = ft_printf("%%%%\n");
	check("%%%%", r1, r2);

	/* %c */
	ft_printf("\n--- Character (%%c) ---\n");
	r2 = printf("%c\n", 'A');
	r1 = ft_printf("%c\n", 'A');
	check("%c 'A'", r1, r2);

	r2 = printf("%c\n", '\0');
	r1 = ft_printf("%c\n", '\0');
	check("%c '\\0'", r1, r2);

	r2 = printf("%c%c%c\n", 'a', 'b', 'c');
	r1 = ft_printf("%c%c%c\n", 'a', 'b', 'c');
	check("%c multiple", r1, r2);

	/* %s */
	ft_printf("\n--- String (%%s) ---\n");
	r2 = printf("%s\n", "hello");
	r1 = ft_printf("%s\n", "hello");
	check("%s hello", r1, r2);

	r2 = printf("%s\n", "");
	r1 = ft_printf("%s\n", "");
	check("%s empty", r1, r2);

	r2 = printf("%s\n", (char *)NULL);
	r1 = ft_printf("%s\n", (char *)NULL);
	check("%s NULL", r1, r2);

	/* %d / %i */
	ft_printf("\n--- Signed Integer (%%d / %%i) ---\n");
	r2 = printf("%d\n", 42);
	r1 = ft_printf("%d\n", 42);
	check("%d positive", r1, r2);

	r2 = printf("%d\n", -42);
	r1 = ft_printf("%d\n", -42);
	check("%d negative", r1, r2);

	r2 = printf("%d\n", 0);
	r1 = ft_printf("%d\n", 0);
	check("%d zero", r1, r2);

	r2 = printf("%i\n", INT_MAX);
	r1 = ft_printf("%i\n", INT_MAX);
	check("%i INT_MAX", r1, r2);

	r2 = printf("%i\n", INT_MIN);
	r1 = ft_printf("%i\n", INT_MIN);
	check("%i INT_MIN", r1, r2);

	/* %u */
	ft_printf("\n--- Unsigned Integer (%%u) ---\n");
	r2 = printf("%u\n", UINT_MAX);
	r1 = ft_printf("%u\n", UINT_MAX);
	check("%u UINT_MAX", r1, r2);

	r2 = printf("%u\n", 0U);
	r1 = ft_printf("%u\n", 0U);
	check("%u zero", r1, r2);

	/* %x */
	ft_printf("\n--- Hexadecimal Lowercase (%%x) ---\n");
	r2 = printf("%x\n", 255);
	r1 = ft_printf("%x\n", 255);
	check("%x 255", r1, r2);

	r2 = printf("%x\n", 0);
	r1 = ft_printf("%x\n", 0);
	check("%x zero", r1, r2);

	r2 = printf("%x\n", UINT_MAX);
	r1 = ft_printf("%x\n", UINT_MAX);
	check("%x UINT_MAX", r1, r2);

	/* %X */
	ft_printf("\n--- Hexadecimal Uppercase (%%X) ---\n");
	r2 = printf("%X\n", 255);
	r1 = ft_printf("%X\n", 255);
	check("%X 255", r1, r2);

	/* %p */
	ft_printf("\n--- Pointer (%%p) ---\n");
	x = 42;
	r2 = printf("%p\n", (void *)&x);
	r1 = ft_printf("%p\n", (void *)&x);
	check("%p &x", r1, r2);

	r2 = printf("%p\n", (void *)NULL);
	r1 = ft_printf("%p\n", (void *)NULL);
	check("%p NULL", r1, r2);

	/* mixed */
	ft_printf("\n--- Mixed Specifiers ---\n");
	r2 = printf("n=%d s=%s c=%c\n", 7, "ok", '!');
	r1 = ft_printf("n=%d s=%s c=%c\n", 7, "ok", '!');
	check("mixed simple", r1, r2);

	r2 = printf("%c%s%d%u%x%X%p%%\n", 'A', "B", 1, 2U, 3, 4, (void *)&x);
	r1 = ft_printf("%c%s%d%u%x%X%p%%\n", 'A', "B", 1, 2U, 3, 4, (void *)&x);
	check("all specifiers", r1, r2);

	/* --- BÔNUS / FLAGS DE PRECISÃO E LARGURA --- */
	/* Se a sua ft_printf não exigir bônus, você pode remover esta seção */
	ft_printf("\n--- Bonus / Width & Precision ---\n");

	r2 = printf("%.5s\n", "aaaaa");
	r1 = ft_printf("%.5s\n", "aaaaa");
	check("precision string", r1, r2);

	r2 = printf("%.4s\n", (char *)NULL);
	r1 = ft_printf("%.4s\n", (char *)NULL);
	check("precision NULL string", r1, r2);

	r2 = printf("%.5d\n", -2372);
	r1 = ft_printf("%.5d\n", -2372);
	check("precision negative int", r1, r2);

	r2 = printf("%10x\n", 20);
	r1 = ft_printf("%10x\n", 20);
	check("width hex", r1, r2);

	r2 = printf("%-15p\n", (void *)NULL);
	r1 = ft_printf("%-15p\n", (void *)NULL);
	check("minus flag pointer NULL", r1, r2);

	r2 = printf("%*d\n", 10, 50);
	r1 = ft_printf("%*d\n", 10, 50);
	check("asterisk width", r1, r2);

	/* Final Summary */
	ft_printf("\n===========================================\n");
	ft_printf("=== RESULTADO: %d PASSED, %d FAILED ===\n", g_pass, g_fail);
	ft_printf("===========================================\n");

	return (g_fail != 0);
}
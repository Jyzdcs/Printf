/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kclaudan <kclaudan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 13:54:10 by kclaudan          #+#    #+#             */
/*   Updated: 2024/11/15 15:56:08 by kclaudan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

int	is_format_specifier(const char f)
{
	const char	*format_spe = "cspdiuxX%";
	
	while (*format_spe)
	{
		if (f == *format_spe)
			return 1;
		format_spe++;
	}
	return (0);

}

int	format_print(char f, va_list *args)
{
	if (f == 'c')
		ft_putchar((const char)va_arg(*args, int));
	else if (f == 's')
		return ft_putstr(va_arg(*args, const char*));
	else if (f == 'd' || f == 'i')
		return print_d(va_arg(*args, int), 1, 0);
	else if (f == 'p')
		return ft_putnbr_base((unsigned long)va_arg(*args, void*), "0123456789abcdef", 1);
	else if (f == 'u')
		return print_u(va_arg(*args, int));
	else if (f == 'x')
		return ft_putnbr_base((unsigned int)va_arg(*args, int), "0123456789abcdef", 0);
	else if (f == 'X')
		return ft_putnbr_base((unsigned int)va_arg(*args, int), "0123456789ABCDEF", 0);
	else if (f == '%')
		ft_putchar('%');
	return (1);
}

int		ft_printf(const char *format, ...)
{
	int				i;
	int				counter;
	char		format_letter;
	va_list		args;

	i = 0;
	counter = 0;
	va_start(args, format);
	while (format[i])
	{
		if (format[i] == '%' && is_format_specifier(format[i + 1]))
		{
			format_letter = format[i + 1];
			counter += format_print(format_letter, &args);
			i += 2;
		}
		else
		{
			ft_putchar(format[i]);
			counter++;
			i++;
		}
	}
	va_end(args);
	return (counter);
}
/*
int main(int ac, char **argv)
{
	(void)ac;
	(void)argv;
	//char *name = "kylian";
	int x = 42;
	int e = -42;

	int i = ft_printf("Bonjour %s, dwad %X-%x-%X\n", "kylian", -42, 32);
	ft_printf("%d\n", i);
	i = printf("Bonjour %s, dwad %X-%x-%X\n", "kylian", -42, );
	printf("%d\n", i);
	//ft_printf("Mon printf : Hexa minuscule : %x, string : %s, num : %d, hexa en maj : %X, adresse d'un ptr : %p\n", 12, "saperlipopete", 15, 255, &x);  // Utilisation de %p avec un pointeur sur x
	//printf("Mon printf : Hexa minuscule : %x, string : %s, num : %d, hexa en maj : %X, adresse d'un ptr : %p\n", 12, "saperlipopete", 15, 255, &x);  // Utilisation de %p avec un pointeur sur x
}
*/
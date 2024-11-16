/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kclaudan <kclaudan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 13:54:10 by kclaudan          #+#    #+#             */
/*   Updated: 2024/11/16 12:15:16 by kclaudan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	is_format_specifier(const char f)
{
	const char	*format_spe = "cspdiuxX%";

	while (*format_spe)
	{
		if (f == *format_spe)
			return (1);
		format_spe++;
	}
	return (0);
}

int	format_print(char f, va_list *args)
{
	if (f == 'c')
		ft_putchar((const char)va_arg(*args, int));
	else if (f == 's')
		return (ft_putstr(va_arg(*args, const char *)));
	else if (f == 'd' || f == 'i')
		return (print_d(va_arg(*args, int), 1, 1));
	else if (f == 'p')
		return (ft_putnbr_base((unsigned long)va_arg(*args, void *), 1, 0));
	else if (f == 'u')
		return (print_u(va_arg(*args, unsigned int)));
	else if (f == 'x')
		return (ft_putnbr_base((unsigned int)va_arg(*args, int), 0, 0));
	else if (f == 'X')
		return (ft_putnbr_base((unsigned int)va_arg(*args, int), 0, 1));
	else if (f == '%')
		ft_putchar('%');
	return (1);
}

int	ft_printf(const char *format, ...)
{
	int		i;
	int		counter;
	va_list	args;
	char	format_letter;

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

int main(int ac, char **argv)
{
	(void)ac;
	(void)argv;
	//char *name = "kylian";
	int x = 42;
	int e = -42;

	int i = ft_printf("Bonjour %s, jai %d mais jai aussi %x et %X et mon adresse est %p je suis sur a %% que %c peuvent win %i\n", "kylian", -42, -42, -42, &x, 'c', 16);
	ft_printf("%d\n", i);
	i = printf("Bonjour %s, jai %d mais jai aussi %x et %X et mon adresse est %p je suis sur a %% que %c peuvent win %i\n", "kylian", -42, -42, -42, &x, 'c', 16);
	printf("%d\n", i);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kclaudan <kclaudan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 13:54:10 by kclaudan          #+#    #+#             */
/*   Updated: 2024/11/19 21:11:37 by kclaudan         ###   ########.fr       */
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

int	format_print(char f, va_list *args, int *counter)
{
	if (f == 'c')
		ft_putchar((const char)va_arg(*args, int), counter);
	else if (f == 's')
		ft_putstr(va_arg(*args, const char *), counter);
	else if (f == 'd' || f == 'i')
		print_d(va_arg(*args, int), counter);
	else if (f == 'p')
		ft_putnbr_base((unsigned long)va_arg(*args, void *), 1, 0, counter);
	else if (f == 'u')
		print_u(va_arg(*args, unsigned int), counter);
	else if (f == 'x')
		ft_putnbr_base((unsigned int)va_arg(*args, int), 0, 0, counter);
	else if (f == 'X')
		ft_putnbr_base((unsigned int)va_arg(*args, int), 0, 1, counter);
	else if (f == '%')
		ft_putchar('%', counter);
	return (0);
}

int	ft_printf(const char *format, ...)
{
	int		i;
	int		counter;
	va_list	args;

	if (!format)
		return (-1);
	i = 0;
	counter = 0;
	va_start(args, format);
	while (format[i])
	{
		if (format[i] == '%' && is_format_specifier(format[i + 1]))
		{
			format_print(format[i + 1];, &args, &counter);
			i += 2;
		}
		else
		{
			ft_putchar(format[i], &counter);
			i++;
		}
	}
	va_end(args);
	return (counter);
}
/*
#include <limits.h>
int main(int ac, char **argv)
{
	(void)ac;
	(void)argv;
	int a = 1;
	int *x = &a;

	int i = ft_printf(" %x \n", 0);
	ft_printf("char lu1 : %d\n", i);
	i = printf(" %x \n", 0);
	ft_printf("char lu2 : %d\n", i);
}*/

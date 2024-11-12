/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kclaudan <kclaudan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 13:54:10 by kclaudan          #+#    #+#             */
/*   Updated: 2024/11/12 21:38:47 by kclaudan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

void	ft_putchar(const char c)
{
	write(1, &c, 1);
}

int		is_format_specifier(const char f)
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

void	ft_putstr(const char *str)
{
	while (*str)
		ft_putchar(*str++);
}

void	ft_putnbr_fd(int n, int fd)
{
	if (n < 0)
	{
		if (n == -2147483648)
		{
			ft_putstr("-2147483648");
			return ;
		}
		ft_putchar('-');
		ft_putnbr_fd(-n, fd);
		return ;
	}
	if (n > 9)
	{
		ft_putnbr_fd(n / 10, fd);
		ft_putchar(n % 10 + '0');
		return ;
	}
	ft_putchar(n + '0');
}

void	format_print(char f, va_list args)
{
    if (f == 'c')
        ft_putchar((const char)va_arg(args, int));
    else if (f == 's')
        ft_putstr(va_arg(args, char*));
	else if (f == 'd')
        ft_putnbr_fd(va_arg(args, int), 1);
    /*else if (f == 'p')
        print_pointer(va_arg(args, int));
    else if (f == 'i')
        print_integer(va_arg(args, int));
    else if (f == 'u')
        print_unsigned(va_arg(args, int));
    else if (f == 'x')
        print_hex_lower(va_arg(args, int));
    else if (f == 'X')
        print_hex_upper(va_arg(args, int));
    else if (f == '%')
        print_percent();*/
	else
		printf("ERROR PAS DE TYPE !!!\n");
}

int		ft_printf(const char *format, ...)
{
	int				i;
	char		format_letter;
	va_list		args;
	
	i = 0;
	va_start(args, format);
	while (format[i])
	{
		if (format[i] == '%' && is_format_specifier(format[i + 1]))
		{
			format_letter = format[i + 1];
			format_print(format_letter, args);
			i += 2;
		}
		else
		{
			ft_putchar(format[i]);
			i++;
		}
	}
}

int main(int ac, char **argv)
{
	char *name = "kylian";

	ft_printf("SALUT TLMD jai %ddwadad%s et je mappele %s\n", 16, name, "blabla");
}
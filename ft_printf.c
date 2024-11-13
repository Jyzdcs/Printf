/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kclaudan <kclaudan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 13:54:10 by kclaudan          #+#    #+#             */
/*   Updated: 2024/11/13 23:14:06 by kclaudan         ###   ########.fr       */
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

int	ft_len_str(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	ft_len_decimal(int nb)
{
	int	i;

	i = 0;
	while (nb > 0)
	{
		nb /= 10;
		i++;
	}
	return (i);
}

void	ft_putchar(const char c)
{
	write(1, &c, 1);
}

void	ft_putstr(const char *str)
{
	while (*str)
		ft_putchar(*str++);
}

void	print_u(unsigned int n, int fd)
{	
	if (n > 9)
	{
		print_u(n / 10, fd);
		ft_putchar(n % 10 + '0');
		return ;
	}
	ft_putchar(n + '0');
}

void	print_d(int n, int fd)
{
	if (n < 0)
	{
		if (n == -2147483648)
		{
			ft_putstr("-2147483648");
			return ;
		}
		ft_putchar('-');
		print_d(-n, fd);
		return ;
	}
	if (n > 9)
	{
		print_d(n / 10, fd);
		ft_putchar(n % 10 + '0');
		return ;
	}
	ft_putchar(n + '0');
}

void	ft_putchar_base(int nb, char *base)
{
	write(1, &base[nb], 1);
}

int	parsing_base(char *base)
{
	int	i;
	int	el;

	if (ft_len_str(base) <= 1)
		return (0);
	i = 0;
	while (base[i])
	{
		if ((9 <= base[i] && base[i] <= 13) || base[i] == ' ')
			return (0);
		else if (base[i] == '+' || base[i] == '-')
			return (0);
		el = i + 1;
		while (base[el])
		{
			if (base[i] == base[el++])
				return (0);
		}
		i++;
	}
	return (1);
}

void	print_n_zero(long long nbr, int base_len)
{
	int	nbr_of_zero;

	nbr_of_zero = 0;
	while (nbr)
	{
		nbr /= base_len;
		nbr_of_zero++;
	}
	nbr_of_zero = 16 - nbr_of_zero;
	while (nbr_of_zero)
	{
		ft_putchar('0');
		nbr_of_zero--;
	}
}

void	ft_putnbr_base(long long nbr, char *base, int r)
{
	int const	base_number = ft_len_str(base);

	if (r == 1)
		print_n_zero(nbr, base_number);
	if (nbr < 0 && parsing_base(base))
	{
		write(1, "-", 1);
		nbr = nbr * -1;
	}
	if (parsing_base(base) == 1)
	{
		if (nbr >= base_number)
		{
			ft_putnbr_base(nbr / base_number, base, 0);
			ft_putnbr_base(nbr % base_number, base, 0);
		}
		else
			ft_putchar_base(nbr, base);
	}
	else
		return ;
}

void	format_print(char f, va_list *args)
{
	if (f == 'c')
		ft_putchar((const char)va_arg(*args, int));
	else if (f == 's')
		ft_putstr(va_arg(*args, char*));
	else if (f == 'd' || f == 'i')
		print_d(va_arg(*args, int), 1);
	else if (f == 'p')
		ft_putnbr_base((long long)va_arg(*args, void*), "0123456789abcdef", 1);
	else if (f == 'u')
		print_u(va_arg(*args, int), 1);
	else if (f == 'x')
		ft_putnbr_base((unsigned char)va_arg(*args, int), "0123456789abcdef", 0);
	else if (f == 'X')
		ft_putnbr_base((unsigned char)va_arg(*args, int), "0123456789ABCDEF", 0);
	else if (f == '%')
		ft_putchar('%');
}

int	ft_len_address(long long address)
{
	int	counter;

	counter = 0;
	if (address == 0)
		return (1);
	while (address)
	{
		address /= 10;
		counter++;
	}
	return (counter + (16 - counter));
}

int	print_unsigned_len(unsigned int nb)
{
	int	counter;

	counter = 0;
	if (nb == 0)
		return (1);
	while (nb)
	{
		nb /= 10;
		counter++;
	}
	return (counter);
}

int	print_hex_len(int nb)
{
	int	counter;

	counter = 0;
	if (nb == 0)
		return (1);
	while (nb)
	{
		nb /= 16;
		counter++;
	}
	return (counter);
}

int	len_args(char f, va_list args)
{
	if (f == 'c' || f == '%')
		return (1);
	else if (f == 's')
		return (ft_len_str(va_arg(args, char*)));
	else if (f == 'd' || f == 'i')
		return (ft_len_decimal(va_arg(args, int)));
	else if (f == 'p')
		return (ft_len_address((long long)va_arg(args, void*)));
	else if (f == 'u')
		return (print_unsigned_len((unsigned char)va_arg(args, int)));
	else if (f == 'x' || f == 'X')
		return (print_hex_len(va_arg(args, int)));
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
			counter += len_args(format_letter, args);
			format_print(format_letter, &args);
			i += 2;
		}
		else
		{
			ft_putchar(format[i]);
			counter++;
			i++;
		}
	}
	return (counter);
}

int main(int ac, char **argv)
{
	char *name = "kylian";
	int x = 42;
	//ft_putnbr_base((long long)&x, "0123456789abcdef");
	int i = ft_printf("Mon printf (1) : Adresse de x : %x\n", 0);  // Utilisation de %p avec un pointeur sur x
	printf("return de i : %d\n", i);
	i = printf("Mon printf (0) : Adresse de x : %x\n", 0);  // Utilisation de %p avec un pointeur sur x
	printf("return de i : %d", i);
/*	int i = ft_printf("SALUT TLMD jai %d ans dwadad %s et je mappele %s\n", 15, name, "BLABLABLA", "dwdad");
	int j = printf("SALUT TLMD jai %d ans dwadad %s et je mappele %s\n", 15, name, "BLABLABLA", "dwdad");
	printf("%d\n", i);
	printf("%d\n", j);*/
}

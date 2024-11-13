/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kclaudan <kclaudan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 13:54:10 by kclaudan          #+#    #+#             */
/*   Updated: 2024/11/13 13:11:34 by kclaudan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

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

int	len_args(char f, va_list args)
{
	if (f == 'c')
		return (1);
	else if (f == 's')
		ft_len_str(va_arg(args, char*));
	else if (f == 'd')
		ft_len_decimal(va_arg(args, int));
	//else if (f == 'p')
	//	ft_len_address(va_arg(args, void*));
	/*else if (f == 'i')
		print_integer(va_arg(args, int));
	else if (f == 'u')
		print_unsigned(va_arg(args, int));
	else if (f == 'x')
		print_hex_lower(va_arg(args, int));
	else if (f == 'X')
		print_hex_upper(va_arg(args, int));
	else if (f == '%')
		print_percent();*/
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

void	ft_putnbr_base_min(unsigned int nbr, char *base, unsigned int const b)
{
	if (parsing_base(base) == 1)
	{
		if (nbr > b)
		{
			ft_putnbr_base_min(nbr / b, base, b);
			ft_putnbr_base_min(nbr % b, base, b);
		}
		else
			ft_putchar_base(nbr, base);
	}
}

void	ft_putnbr_base(long long nbr, char *base)
{
	int const	base_number = ft_len_str(base);

	if (nbr == -2147483648)
	{
		write(1, "-", 1);
		ft_putnbr_base_min(-nbr, base, base_number);
		return ;
	}
	else if (nbr < 0 && parsing_base(base))
	{
		write(1, "-", 1);
		nbr = nbr * -1;
	}
	if (parsing_base(base) == 1)
	{
		if (nbr >= base_number)
		{
			ft_putnbr_base(nbr / base_number, base);
			ft_putnbr_base(nbr % base_number, base);
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
	else if (f == 'd')
		ft_putnbr_fd(va_arg(*args, int), 1);
	else if (f == 'p')
		ft_putnbr_base((long long)va_arg(*args, void*), "0123456789abcdef");
	/*else if (f == 'i')
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
	ft_printf("Mon printf : Adresse de x : %p\n", (void*)&x);  // Utilisation de %p avec un pointeur sur x
	printf("Vrai printf : Adresse de x : %p", (void*)&x);
/*	int i = ft_printf("SALUT TLMD jai %d ans dwadad %s et je mappele %s\n", 15, name, "BLABLABLA", "dwdad");
	int j = printf("SALUT TLMD jai %d ans dwadad %s et je mappele %s\n", 15, name, "BLABLABLA", "dwdad");
	printf("%d\n", i);
	printf("%d\n", j);*/
}

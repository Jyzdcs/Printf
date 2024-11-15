/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hex_printer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kclaudan <kclaudan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 10:49:54 by kclaudan          #+#    #+#             */
/*   Updated: 2024/11/15 10:49:54 by kclaudan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

int	ft_putchar_base(int nb, char *base)
{
	write(1, &base[nb], 1);
	return (1);
}

int	ft_len_str(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	ft_print_0x()
{
	write(1, "0x", 2);
	return (2);
}

int	ft_putnbr_base(unsigned int nbr, char *base, int r)
{
	unsigned int const	base_number = ft_len_str(base);
	int		counter = 1;

	if (r == 1)
		counter += ft_print_0x();
	if (nbr >= base_number)
	{
		counter += ft_putnbr_base(nbr / base_number, base, 0);
		ft_putnbr_base(nbr % base_number, base, 0);
	}
	else
		ft_putchar_base(nbr, base);
	return (counter);
}

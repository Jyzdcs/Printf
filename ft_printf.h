/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kclaudan <kclaudan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 16:51:06 by kclaudan          #+#    #+#             */
/*   Updated: 2024/11/19 15:02:20 by kclaudan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <unistd.h>
# include <stdio.h>
# include <stdarg.h>

void	ft_putchar(const char c, int *counter);
void	ft_putstr(const char *str, int *counter);
int		format_print(char f, va_list *args, int *counter);
void	ft_putnbr_base(unsigned long nbr, int r, int maj, int *counter);
void	print_u(unsigned int n, int *counter);
void	print_d(int n, int *counter);
int		is_format_specifier(const char f);
int		ft_printf(const char *format, ...);

#endif
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnjoh-tc <lnjoh-tc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 11:48:51 by lnjoh-tc          #+#    #+#             */
/*   Updated: 2023/11/30 13:13:43 by lnjoh-tc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	traitement(va_list args, const char cspdiuxx)
{
	int	count_char;

	count_char = 0;
	if (cspdiuxx == 'c')
		count_char += ft_format_character(va_arg(args, int));
	if (cspdiuxx == 's')
		count_char += ft_format_string(va_arg(args, char *));
	if (cspdiuxx == 'p')
		count_char += ft_format_pointer(va_arg(args, unsigned long long));
	if (cspdiuxx == 'd' || cspdiuxx == 'i')
		count_char += ft_format_decimal(va_arg(args, int));
	if (cspdiuxx == 'u')
		count_char += ft_format_u(va_arg(args, unsigned int));
	if (cspdiuxx == 'x')
		count_char += ft_format_hex_low(va_arg(args, unsigned long long));
	if (cspdiuxx == 'X')
		count_char += ft_format_hex_upp(va_arg(args, unsigned long long));
	if (cspdiuxx == '%')
	{
		write(1, "%", 1);
		return (1);
	}
	return (count_char);
}

int	ft_printf(const char *format, ...)
{
	int		i;
	int		count_char;	
	va_list	args;

	va_start (args, format);
	i = 0;
	count_char = 0;
	while (format[i])
	{
		if (format[i] == '%')
		{
			i++;
			count_char += traitement(args, format[i]);
		}
		else
		{
			count_char += write (1, &format[i], 1);
		}
		i++;
	}
	va_end (args);
	return (count_char);
}

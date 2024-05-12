/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_format_pointer.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnjoh-tc <lnjoh-tc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 20:06:57 by lnjoh-tc          #+#    #+#             */
/*   Updated: 2023/11/30 12:50:39 by lnjoh-tc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_putchar(char c)
{
	write (1, &c, 1);
	return (1);
}

static int	ft_putchar_two(char c)
{
	(void)c;
	write (1, "(nil)", 5);
	return (5);
}

static int	ft_hex_len(unsigned long num)
{
	long	len;

	len = 0;
	while (num != 0)
	{
		len++;
		num = num / 16;
	}
	return (len);
}

static void	ft_print_hex(unsigned long num)
{
	if (num >= 16)
	{
		ft_print_hex(num / 16);
		ft_print_hex(num % 16);
	}
	else
	{
		if (num <= 9)
			ft_putchar(num + '0');
		else
		{
			ft_putchar(num - 10 + 'a');
		}
	}
}

int	ft_format_pointer(unsigned long long ptr)
{
	int	count;

	count = 0;
	if (ptr == 0)
	{
		return (count += ft_putchar_two('c'));
	}
	else
	{
		count = count + ft_putchar('0');
		count = count + ft_putchar('x');
		ft_print_hex (ptr);
		return (count + ft_hex_len (ptr));
	}
	return (count);
}

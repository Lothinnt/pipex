/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_format_hex_low.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnjoh-tc <lnjoh-tc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 00:46:01 by lnjoh-tc          #+#    #+#             */
/*   Updated: 2023/11/30 13:14:49 by lnjoh-tc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_putchar(char c)
{
	write (1, &c, 1);
	return (1);
}

static int	ft_hex_len(unsigned int num)
{
	int	len;

	len = 0;
	while (num != 0)
	{
		len++;
		num = num / 16;
	}
	return (len);
}

static void	ft_print_hex(unsigned int num)
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

int	ft_format_hex_low(unsigned int n)
{
	if (n == 0)
		return (write(1, "0", 1));
	else
		ft_print_hex(n);
	return (ft_hex_len(n));
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnjoh-tc <lnjoh-tc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 17:42:05 by lnjoh-tc          #+#    #+#             */
/*   Updated: 2023/11/30 12:48:39 by lnjoh-tc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>
# include <stdlib.h>
# include <limits.h>

int	ft_printf(const char *format, ...);
int	ft_format_character(int c);
int	ft_format_string(char *str);
int	ft_format_pointer(unsigned long long ptr);
int	ft_format_decimal(int n);
int	ft_format_u(unsigned int n);
int	ft_format_hex_upp(unsigned int n);
int	ft_format_hex_low(unsigned int n);

#endif
